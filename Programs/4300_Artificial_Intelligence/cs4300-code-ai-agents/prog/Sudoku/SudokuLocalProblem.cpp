#include "SudokuLocalProblem.h"
namespace example {
  namespace Sudoku {

    LocalProblem::LocalProblem( const Board& starting_board )
      : mStartingBoard( starting_board ) {
      // Empty
    }

    LocalProblem::~LocalProblem( ) {
      // Empty
    }
    
    bool LocalProblem::GoodEnough( const ai::LocalSearch::State * const state_in ) {
      const LocalState * const s0 = dynamic_cast< const LocalState * const >( state_in );
      // If the state's value is > -1.0, it must be 0 conflicts.  Avoid == 0.0 with float types
      return ( s0->Value( ) > -1.0 );
      
    }
    
    /* 
     * Copy the starting board, and randomly fill the empty locations for random state
     */
    ai::LocalSearch::State *LocalProblem::RandomState() const {
      LocalState *state = new LocalState( mStartingBoard );
      state->getModel( ).FillBoxes( );
      return state;
    }

    /*
     * Find best neighbor of current state
     */
    ai::LocalSearch::State *LocalProblem::BestNeighbor(const ai::LocalSearch::State * const state_in, int& neighbors_generated) const {
      neighbors_generated = 0;
      const LocalState * const s0 = dynamic_cast< const LocalState * const >( state_in );
      Board best_neighbor_board;
      s0->getModel( ).BestNeighbor( best_neighbor_board, neighbors_generated );
      
      LocalState *state = new LocalState( best_neighbor_board );
      return state;
    }

    /*
     * Find a randomly selected neighbor of current state
     */
    ai::LocalSearch::State *LocalProblem::RandomNeighbor(const ai::LocalSearch::State * const state_in) const {
      const LocalState * const s0 = dynamic_cast< const LocalState * const >( state_in );
      Board random_neighbor_board;
      s0->getModel( ).RandomNeighbor( random_neighbor_board );
      
      LocalState *state = new LocalState( random_neighbor_board );
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
