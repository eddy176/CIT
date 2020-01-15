#include "SudokuProblem.h"

namespace example {
  namespace Sudoku {
    
    Problem::Problem( ai::Search::State *initial_state_in )
      : ai::Search::Problem( initial_state_in ) {
    }
    
    Problem::~Problem( ) {
    }

    bool Problem::GoalTest( const ai::Search::State * const state_in ) const {
      const State * const state = dynamic_cast< const State * const >( state_in );
      return state->getModel( ).IsSolved( );
    }

    std::vector<ai::Search::Action *> Problem::Actions( const ai::Search::State * const state_in ) {
      const State * const state = dynamic_cast< const State * const >( state_in );
      std::vector<ai::Search::Action *> actions;
      int row, col;
      std::vector< int > values;
      unsigned int i;

      if( state->getModel( ).FindFirstWildcard( row, col ) ) {
        if( state->getModel( ).FindAvailableValues( row, col, values ) ) {
          for( i = 0; i < values.size( ); i++ ) {
            actions.push_back( new Action( row, col, values[ i ] ) );
          }
        }
      }
      
      return actions;
    }

    ai::Search::State *Problem::Result( const ai::Search::State * const state_in, const ai::Search::Action * const action_in ) {
      const State * const state = dynamic_cast< const State * const >( state_in );
      const Action * const action = dynamic_cast< const Action * const >( action_in );
      State *state2 = new State( *state );
      state2->getModel( ).SetValue( action->getRow( ), action->getColumn( ), action->getValue( ) );
      return state2;
    }

    double Problem::StepCost( const ai::Search::State  * const state1_in,
                              const ai::Search::Action * const action_in,
                              const ai::Search::State  * const state2_in ) const {
      return 1.0;
    }

    double Problem::Heuristic(const ai::Search::State  * const state_in) const {
      return 0.0;
    }
      
  }
}
