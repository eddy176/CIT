#include "RectangleProblem.h"
#include "RectangleState.h"
#include "RectangleAction.h"
#include "RectangleAppData.h"
#include <sstream>

namespace ai {
  namespace rectangle {

    Problem::Problem( ai::Search::State *initial_state_in ) 
      : ai::Search::Problem( initial_state_in ) {
      // empty
    }

    Problem::~Problem( ) {
      // empty
    }

    bool Problem::GoalTest( const ai::Search::State * const state_in ) const {

      const State * const state = dynamic_cast< const State * const >( state_in );

      return state->getModel( ).IsSolved( );
    }

    std::vector<ai::Search::Action *> Problem::Actions( const ai::Search::State * const state_in ) {
      const State * const rs1 = dynamic_cast<const State * const>(state_in);
      std::vector<ai::Search::Action *> actions;
      Model model( rs1->getModel( ) );
      
      unsigned int i;
      int r, f;
      int x, y;
      
      /* Consider all placements of the first unplaced piece */
      for(i = 0; i < model.GetNumPieces(); i++) {
        if(model.GetPiece( i ).placed) {
          continue;
        }
        for(r = 0; r < model.GetPiece( i ).max_rotation; r++) {
          for(f = 0; f < model.GetPiece( i ).max_flip; f++) {
            for(x = 0; x < model.GetWidth(); x++) {
              for(y = 0; y < model.GetHeight(); y++) {
                // only use action if place will actually place
                Model tmp_model( model );
                Move  move( i, r, f, x, y );
                if( tmp_model.ApplyMove( move ) ) {
                  actions.push_back( new Action( move ) );
                }
              }
            }
          }
        }
        // only use the first piece that hasn't been placed yet.
        break;
      }

      return actions;
    }

    ai::Search::State *Problem::Result( const ai::Search::State * const state_in, const ai::Search::Action * const action_in ) {
      const State * const state = dynamic_cast< const State * const >( state_in );
      const Action * const action = dynamic_cast< const Action * const >( action_in );

      Model model = state->getModel( );
      if( !model.ApplyMove( action->getMove( ) ) ) {
        std::stringstream ss;
        ss << "Unexpected result from ApplyMove in Problem::Result()";
        throw Exception( ss.str( ) );
      }
      return new State( model );
    }
    
    double Problem::StepCost( const ai::Search::State  * const state1_in,
                              const ai::Search::Action * const action_in,
                              const ai::Search::State  * const state2_in ) const {
      const Action * const action = dynamic_cast< const Action * const >( action_in );
      return action->getMove( ).getCost( );
    }
    
  }
}
