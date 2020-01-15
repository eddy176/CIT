#ifndef _VERTEXCOVERMODEL_H_
#define _VERTEXCOVERMODEL_H_

#include <vector>
#include <map>
#include <set>
#include <iostream>

namespace example {
  namespace VertexCover {

    /* 
     * A graph is needed to store the vertices and edges
     */
    class Graph {
    public:
      Graph( const int vertex_count );
      virtual ~Graph( );
      virtual bool addEdge( const int u, const int v, const int weight ) = 0;
      virtual int getEdge( const int u, const int v ) const = 0;
      virtual int getVertexCount( ) const;
    protected:
      int mVertexCount;
    private:
    };

    class GraphAdjacencyMatrix: public Graph {
    public:
      GraphAdjacencyMatrix( const int vertex_count );
      virtual ~GraphAdjacencyMatrix( );
      virtual bool addEdge( const int u, const int v, const int weight );
      virtual int getEdge( const int u, const int v ) const;
      
    protected:
      int calculateIndex( const int u, const int v ) const;
      std::vector< int > mEdges;

    private:
    };

    class GraphAdjacencyList: public Graph {
    public:
      GraphAdjacencyList( const int vertex_count );
      virtual ~GraphAdjacencyList( );
      virtual bool addEdge( const int u, const int v, const int weight );
      virtual int getEdge( const int u, const int v ) const;
      
    protected:
      std::vector< std::map< int, int > > mEdges;

    private:
    };

    /* 
     * The model uses a graph to store the vertices and edges.
     * Specialty methods are created specific to the Vertex Cover problem.
     */

    class Model {
    public:
      enum GraphType { GT_MATRIX, GT_LIST };

      Model( );
      Model( const GraphType& graph_type );
      Model( const Model& src );
      ~Model( );
      Model& operator=( const Model& rhs );
      
      bool readGraph( std::istream& is );
      bool createGraph( const int vertex_count );

      bool addVertex( const int u );
      bool removeVertex( const int u );
      int checkVertex( const int u ) const;

      int getEdge( const int u, const int v ) const;
      int getCoverCount( const int u, const int v ) const;
      int getVertexCount( ) const;
      int getRandomUnusedVertex( ) const;
      int getRandomUsedVertex( ) const;

      int getTotalEdges( ) const;
      int getCoveredEdges( ) const;
      int getUncoveredEdges( ) const;
      int getCoverSize( ) const;

      double getValue( ) const;

      std::ostream& Display( std::ostream& os ) const;

    protected:
      Graph *mGraph; // the graph to cover
      Graph *mCover; // any non-zero weight edge in this graph is covered
      std::vector< int > mCoverSet; /* vertices in the cover.  
                                     * vertex is index, non-zero if in set.
                                     */
      std::set< int > mUnusedVertex; /* vertices that are not currently used */
      std::set< int > mUsedVertex;   /* vertices that are currently used */
      
      GraphType mGraphType;
      int mTotalEdges;
      int mCoveredEdges;
      int mCoverSize;
      
    private:
    };
    
  }
}

std::ostream& operator<<( std::ostream& os, const example::VertexCover::Model& model );

#endif /* _VERTEXCOVERMODEL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
