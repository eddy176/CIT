#include "MazeProblem.h"
#include "MazeState.h"
#include "MazeAction.h"
#include "MazeModel.h"
#include <ai_search.h>
#include <cmath>
namespace cgl
{
  namespace Maze
  {
    Problem::Problem(ai::Search::State *initial_state_in, Model *model_in)
      : ai::Search::Problem(initial_state_in),
        model(model_in),
        goal_state(0)
    {
      /* empty */
    }
    Problem::~Problem()
    {
      if(this->model)
        {
          delete this->model;
          this->model = 0;
        }
      if(this->goal_state)
        {
          delete this->goal_state;
          this->goal_state = 0;
        }
    }

    std::vector<ai::Search::Action *> Problem::Actions(const ai::Search::State * const state_in)
    {
      const State * const state = dynamic_cast<const State * const>(state_in);
      std::vector<ai::Search::Action *> actions;
        
      /* consider each of 4 directions
       * this is in order LEFT, RIGHT, UP, DOWN
       * which matches the order in the Action class enum.
       * this is important for the SetType() method call below.
       */
      int dx[4] = { -1, 1,  0, 0 };
      int dy[4] = {  0, 0, -1, 1 };
      int i;
      int new_x, new_y;
      int type;
      for(i = 0; i < 4; i++)
        {
          new_x = state->GetX() + dx[i];
          new_y = state->GetY() + dy[i];
          type = this->model->GetMazeCell(new_x, new_y);
          if(type == Model::T_EMPTY || type == Model::T_START || type == Model::T_GOAL)
            {
              Action *new_action = new Action();
              new_action->SetType(((int)Action::A_LEFT) + i);
              actions.push_back(new_action);
            }
        }
      return actions;
    }
      
    ai::Search::State *Problem::Result(const ai::Search::State * const state_in, const ai::Search::Action * const action_in)
    {
      const State * const state = dynamic_cast<const State * const>(state_in);
      const Action * const action = dynamic_cast<const Action * const>(action_in);
        
      /* consider each of 4 directions
       * this is in order LEFT, RIGHT, UP, DOWN
       * which matches the order in the Action class enum.
       * this is important for the SetType() method call below.
       */
      int dx[4] = { -1, 1,  0, 0 };
      int dy[4] = {  0, 0, -1, 1 };
      int i = action->GetType() - ((int)Action::A_LEFT);
      int new_x = state->GetX() + dx[i];
      int new_y = state->GetY() + dy[i];
      State  *new_state  = new State(*state);
      new_state->SetX(new_x);
      new_state->SetY(new_y);
      return new_state;
    }
      
    bool   Problem::GoalTest(const ai::Search::State * const state_in) const
    {
      const State * const state = dynamic_cast<const State * const>(state_in);
      return *(this->goal_state) == *state;
    }
      
    double Problem::StepCost(const ai::Search::State  * const state1_in,
                             const ai::Search::Action * const action_in,
                             const ai::Search::State  * const state2_in) const
    {
      const State  * const state1 = dynamic_cast<const State * const>(state1_in);
      const Action * const action = dynamic_cast<const Action * const>(action_in);
      const State  * const state2 = dynamic_cast<const State * const>(state2_in);

      /* temporarily fool compiler to think we are using these variables */
      state1->GetX();
      action->GetType();
      state2->GetX();
      /* all actions cost 1 */
      return 1.0;
    }
      
    double Problem::Heuristic(const ai::Search::State  * const state_in) const
    { /* No hints */
      return 0.0;
    }
      
    bool Problem::SetGoal(State *goal_state_in)
    {
      this->goal_state = goal_state_in;
      return true;
    }
  }
}
