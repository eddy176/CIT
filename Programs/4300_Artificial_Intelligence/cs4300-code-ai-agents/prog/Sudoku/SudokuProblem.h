#ifndef _SUDOKUPROBLEM_H_
#define _SUDOKUPROBLEM_H_

#include "ai_search.h"
#include "SudokuAction.h"
#include "SudokuState.h"

namespace example {
  namespace Sudoku {

    class Problem : public ai::Search::Problem {
    public:
      Problem( ai::Search::State *initial_state_in );
      virtual ~Problem( );

      virtual bool GoalTest( const ai::Search::State * const state_in ) const;
      virtual std::vector<ai::Search::Action *> Actions( const ai::Search::State * const state_in );
      virtual ai::Search::State *Result( const ai::Search::State * const state_in, const ai::Search::Action * const action_in );

      virtual double StepCost( const ai::Search::State  * const state1_in,
                               const ai::Search::Action * const action_in,
                               const ai::Search::State  * const state2_in ) const;

      virtual double Heuristic(const ai::Search::State  * const state_in) const;

    protected:
      
    private:
      
    };

  }
}

#endif /* _SUDOKUPROBLEM_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
