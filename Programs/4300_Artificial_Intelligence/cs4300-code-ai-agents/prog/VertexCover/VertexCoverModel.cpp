#include "VertexCoverModel.h"
#include <algorithm>
#include <iostream>

namespace example {
  namespace VertexCover {

    /*
     */
    Graph::Graph( const int vertex_count ) 
      : mVertexCount( vertex_count ) {
    }

    Graph::~Graph( ) {
    }

    int Graph::getVertexCount( ) const {
      return mVertexCount;
    }

    
    /*
     * For an undirected graph, only half of the matrix needs to be stored,
     * because the edge (u,v) is the same as the edge (v,u).
     * If we want to allow for self edges, then we also need to cover the diagonal.
     * 
     * Assume that vertices are specified by 0 <= u,v < n where n is the number
     * of vertices. We need n slots in the first row of the matrix, n-1 in the
     * second, etc.  The total number of edges is SUM(i=n..1) { i } = (n * (n+1) ) / 2.
     *
     * The index for edge (u,v) is calculated as:
     * // assume u <= v
     * if u == 0: v
     * if u == 1: mVertexCount + v - 1
     * if u == 2: mVertexCount + mVertexCount-1 + v - 2
     * if u == 3: mVertexCount + mVertexCount-1 + mVertexCount-2 + v - 3
     * if u == k: k*mVertexCount - SUM(i=0..k){i} + v
     *            k*mVertexCount - ((k*(k+1))/2) + v
     *
     */
    GraphAdjacencyMatrix::GraphAdjacencyMatrix( const int vertex_count )
      : Graph( vertex_count ) {
      mEdges.resize( (vertex_count * (vertex_count + 1) ) / 2 );
      std::fill( mEdges.begin( ), mEdges.end( ), 0 );
    }

    GraphAdjacencyMatrix::~GraphAdjacencyMatrix( ) {
      // empty
    }
    
    bool GraphAdjacencyMatrix::addEdge( const int u, const int v, const int weight ) {
      int i = calculateIndex( u, v );
      mEdges[ i ] = weight; 
      return true;
    }
    
    int GraphAdjacencyMatrix::getEdge( const int u, const int v ) const {
      int i = calculateIndex( u, v );
      return mEdges[ i ];
    }

    int GraphAdjacencyMatrix::calculateIndex( const int u, const int v ) const {
      if( u > v ) {
        // insure that u <= v
        return calculateIndex( v, u );
      }
      
      return u * mVertexCount - ( (u*(u+1)) / 2 ) + v;
    }


    /*
     * For an undirected graph, only half of the edges need to be stored.
     * We choose to store the value for u <= v.
     */
    GraphAdjacencyList::GraphAdjacencyList( const int vertex_count )
      : Graph( vertex_count ), mEdges( vertex_count ) {
      // empty
    }

    GraphAdjacencyList::~GraphAdjacencyList( ) {
      // empty
    }
    
    bool GraphAdjacencyList::addEdge( const int u, const int v, const int weight ) {
      if( u > v ) {
        return addEdge( v, u, weight );
      } 
      if( weight != 0 ) {
        mEdges[ u ][ v ] = weight;
      } else {
        std::map< int, int >::iterator it = mEdges[ u ].find( v );
        if( it != mEdges[ u ].end( ) ) {
          mEdges[ u ].erase( it );
        }
      }
      return true;
    }

    int GraphAdjacencyList::getEdge( const int u, const int v ) const {
      if( u > v ) {
        return getEdge( v, u );
      }
      
      int result = 0;
      std::map< int, int >::const_iterator it = mEdges[ u ].find( v );
      if( it != mEdges[ u ].end( ) ) {
        result = mEdges[ u ].at( v ); // use .at() instead of [] due to const constraint.
      }
      
      return result;
    }


    /*
     */
    Model::Model( ) 
      : mGraph( 0 ), mCover( 0 ), mCoverSet( 0 ), mGraphType( GT_MATRIX ),
        mTotalEdges( 0 ), mCoveredEdges( 0 ), mCoverSize( 0 ) {
    }
    
    Model::Model( const GraphType& graph_type )
      : mGraph( 0 ), mCover( 0 ), mCoverSet( 0 ), mGraphType( graph_type ),
        mTotalEdges( 0 ), mCoveredEdges( 0 ), mCoverSize( 0 ) {
    }

    Model::Model( const Model& src )
      : mGraph( 0 ), mCover( 0 ), mCoverSet( 0 ), mGraphType( GT_MATRIX ),
        mTotalEdges( 0 ), mCoveredEdges( 0 ), mCoverSize( 0 ) {
      *this = src;
    }

    Model::~Model( ) {
      if( mGraph ) {
        delete mGraph;
        mGraph = 0;
      }
      if( mCover ) {
        delete mCover;
        mCover = 0;
      }
    }

    Model& Model::operator=( const Model& rhs ) {
      mGraphType = rhs.mGraphType;
      createGraph( rhs.getVertexCount( ) );
      int u, v, w;
      for( u = 0; u < rhs.getVertexCount( ); u++ ) {
        for( v = u; v < rhs.getVertexCount( ); v++ ) {
          w = rhs.getEdge( u, v );
          if( w ) {
            mGraph->addEdge( u, v, w );
            mTotalEdges++;
          }
        }
      }

      for( u = 0; u < rhs.getVertexCount( ); u++ ) {
        if( rhs.checkVertex( u ) ) {
          addVertex( u );
        }
      }
      
      return *this;
    }

    // assume the stream contains exactly one graph with the following format:
    // vertex_count
    // u v weight
    // u v weight
    // ...
    // Where vertex_count is an integer > 0
    //       u,v are integers in the range 0 to vertex_count - 1
    //       weight is an integer
    bool Model::readGraph( std::istream& is ) {
      
      int vertex_count, u, v, weight;
      
      is >> vertex_count;
      createGraph( vertex_count );

      while( is >> u >> v >> weight && ( u >= 0 && v >= 0 && weight >= 0 ) ) {
        mGraph->addEdge( u, v, weight );
        // mCover->addEdge( u, v, 0 ); // not needed
        mTotalEdges++;
      }
      
      return true;
    }

    bool Model::createGraph( const int vertex_count ) {
      
      if( mGraph ) {
        delete mGraph;
        mGraph = 0;
      }
      if( mCover ) {
        delete mCover;
        mCover = 0;
      }
      
      switch( mGraphType ) {
      case GT_MATRIX:
        mGraph = new GraphAdjacencyMatrix( vertex_count );
        mCover = new GraphAdjacencyMatrix( vertex_count );
        break;
      case GT_LIST:
        mGraph = new GraphAdjacencyList( vertex_count );
        mCover = new GraphAdjacencyList( vertex_count );
        break;
      default:
        return false;
        break;
      }

      mCoverSet.resize( vertex_count );
      std::fill( mCoverSet.begin( ), mCoverSet.end( ), 0 );

      mUnusedVertex.clear( );
      int u;
      for( u = 0; u < vertex_count; u++ ) {
        mUnusedVertex.insert( u );
      }
      mUsedVertex.clear( );

      mTotalEdges = 0;
      mCoveredEdges = 0;
      mCoverSize = 0;

      return true;
    }

    bool Model::addVertex( const int u ) {
      if( mCoverSet[ u ] ) {
        // already set
        return true;
      }
      
      // mark all edges incident on this vertex
      int v;
      int count;
      for( v = 0; v < mGraph->getVertexCount( ); v++ ) {
        if( mGraph->getEdge( u, v ) ) {
          count = mCover->getEdge( u, v );
          mCover->addEdge( u, v, count + 1 );
          if( count == 0 ) {
            mCoveredEdges++;
          }
        }
      }
      mCoverSet[ u ] = 1;
      mCoverSize++;
      mUnusedVertex.erase( u );
      mUsedVertex.insert( u );
      
      return true;
    }

    bool Model::removeVertex( const int u ) {
      if( !mCoverSet[ u ] ) {
        // already unset
        return true;
      }
      
      // unmark all edges incident on this vertex
      int v;
      int count;
      for( v = 0; v < mGraph->getVertexCount( ); v++ ) {
        if( mGraph->getEdge( u, v ) ) {
          count = mCover->getEdge( u, v );
          mCover->addEdge( u, v, count - 1 );
          if( count == 1 ) {
            mCoveredEdges--;
          }
        }
      }
      mCoverSet[ u ] = 0;
      mCoverSize--;
      mUnusedVertex.insert( u );
      mUsedVertex.erase( u );
      
      return true;
    }

    int Model::checkVertex( const int u ) const {
      return mCoverSet[ u ];
    }


    int Model::getEdge( const int u, const int v ) const {
      return mGraph->getEdge( u, v );
    }

    int Model::getCoverCount( const int u, const int v ) const {
      return mCover->getEdge( u, v );
    }

    int Model::getVertexCount( ) const {
      if( mGraph ) {
        return mGraph->getVertexCount( );
      } else {
        return 0;
      }
    }

    int Model::getRandomUnusedVertex( ) const {
      int u;
      if( mUnusedVertex.size( ) > 0 ) {
        int i;
        int r = std::rand( ) % mUnusedVertex.size( );
        std::set< int >::const_iterator it = mUnusedVertex.begin( );
        for( i = 0; i < r; i++ ) {
          it++;
        }
        u = *(it);
      } else {
        u = -1;
      }
      return u;
    }

    int Model::getRandomUsedVertex( ) const {
      int u;
      if( mUsedVertex.size( ) > 0 ) {
        int i;
        int r = std::rand( ) % mUsedVertex.size( );
        std::set< int >::const_iterator it = mUsedVertex.begin( );
        for( i = 0; i < r; i++ ) {
          it++;
        }
        u = *(it);
      } else {
        u = -1;
      }
      return u;
    }

    int Model::getTotalEdges( ) const {
      return mTotalEdges;
    }

    int Model::getCoveredEdges( ) const {
      return mCoveredEdges;
    }

    int Model::getUncoveredEdges( ) const {
      return mTotalEdges - mCoveredEdges;
    }

    int Model::getCoverSize( ) const {
      return mCoverSize;
    }

    double Model::getValue( ) const {
      double v;
      if( getUncoveredEdges( ) == 0 ) {
        v = getCoverSize( );
      } else {
        v = getVertexCount( ) + getUncoveredEdges( );
      }
      return -v;
    }

    std::ostream& Model::Display( std::ostream& os ) const {
      int u, v, w, c;
      os << getCoveredEdges( ) << " of " << getTotalEdges( ) << " edges covered by " << getCoverSize( ) << " vertices." << std::endl;
      os << "Value: " << getValue( ) << std::endl;
      
      for( u = 0; u < mGraph->getVertexCount( ); u++ ) {
        for( v = u; v < mGraph->getVertexCount( ); v++ ) {
          w = getEdge( u, v );
          c = getCoverCount( u, v );
          if( w > 0 ) {
            if( c == 0 ) {
              os << "*";
            }
            os << "("; 
            if( checkVertex( u ) ) {
              os << "&";
            }
            os << u << ",";
            if( checkVertex( v ) ) {
              os << "&";
            }
            os << v << ") w: " << w << " c: " << c << std::endl;
          }
        }
      }
      return os;
    }

  }
}

std::ostream& operator<<( std::ostream& os, const example::VertexCover::Model& model ) {
  return model.Display( os );
}
