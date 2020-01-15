#include "VertexCoverLocalProblem.h"

namespace example {
  namespace VertexCover {

    LocalProblem::LocalProblem( const Model& starting_model, const int max_try_count )
      : mStartingModel( starting_model ), mTryCount( 0 ), mMaxTryCount( max_try_count ) {
      // Empty
    }

    LocalProblem::~LocalProblem( ) {
      // Empty
    }
    
    bool LocalProblem::GoodEnough( const ai::LocalSearch::State * const state_in ) {
      const LocalState * const s0 = dynamic_cast< const LocalState * const >( state_in );
      mTryCount ++;
      return ( ( s0->getModel( ).getUncoveredEdges( ) == 0 &&
                 s0->getModel( ).getVertexCount( ) == 1 ) ||
               ( mTryCount > mMaxTryCount ) );
    }
    
    /* 
     * Copy the starting model, which has the graph, and randomly select a set of vertices
     */
    ai::LocalSearch::State *LocalProblem::RandomState() const {
      LocalState *state = new LocalState( mStartingModel );
      int u;
      for( u = 0; u < state->getModel( ).getVertexCount( ); u++ ) {
        if( std::rand( ) % 100 > 50 ) {
          state->getModel( ).addVertex( u );
        }
      }
      return state;
    }

    /*
     * Find best neighbor of current state
     */
    ai::LocalSearch::State *LocalProblem::BestNeighbor(const ai::LocalSearch::State * const state_in, int& neighbors_generated) const {
      neighbors_generated = 0;
      const LocalState * const s0 = dynamic_cast< const LocalState * const >( state_in );
      Model m = s0->getModel( );
      Model mmax = m;
      int u;
      // consider adding a vertex
      for( u = 0; u < m.getVertexCount( ); u++ ) {
        if( !m.checkVertex( u ) ) {
          Model &tmp = m;
          neighbors_generated++;
          tmp.addVertex( u );
          if( tmp.getValue( ) > mmax.getValue( ) ) {
            mmax = tmp;
          }
          tmp.removeVertex( u );
        }
      }
      
      // consider removing a vertex
      for( u = 0; u < m.getVertexCount( ); u++ ) {
        if( m.checkVertex( u ) ) {
          Model& tmp = m;
          neighbors_generated++;
          tmp.removeVertex( u );
          if( tmp.getValue( ) > mmax.getValue( ) ) {
            mmax = tmp;
          }
          tmp.addVertex( u );
        }
      }

      LocalState *state = new LocalState( mmax );
      return state;
    }

    /*
     * Find a randomly selected neighbor of current state
     */
    ai::LocalSearch::State *LocalProblem::RandomNeighbor(const ai::LocalSearch::State * const state_in) const {
      const LocalState * const s0 = dynamic_cast< const LocalState * const >( state_in );
      bool add_ok = s0->getModel( ).getVertexCount( ) > s0->getModel( ).getCoverSize( );
      bool remove_ok = s0->getModel( ).getCoverSize( ) > 0;
      if( add_ok && remove_ok ) {
        if( std::rand( ) % 2 == 0 ) {
          remove_ok = false;
        } else {
          add_ok = false;
        }
      }

      Model m = s0->getModel( );

      if( add_ok ) {
        int u = s0->getModel( ).getRandomUnusedVertex( );
        m.addVertex( u );
      } else if( remove_ok ) {
        int u = s0->getModel( ).getRandomUsedVertex( );
        m.removeVertex( u );
      } else {
      }

      LocalState *state = new LocalState( m );
      return state;
      
    }

    ai::LocalSearch::State *LocalProblem::ChildState(const ai::LocalSearch::State * const state1_in, const ai::LocalSearch::State * const state2_in, double mix_point) const {
      const LocalState * const s1 = dynamic_cast< const LocalState * const >( state1_in );
      /*
      */
      LocalState *state = new LocalState( s1->getModel( ) );
      return state;
    }
    
    
  }
}
