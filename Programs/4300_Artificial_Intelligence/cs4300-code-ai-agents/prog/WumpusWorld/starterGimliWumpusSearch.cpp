#include "starterGimliWumpusSearch.h"
#include <ai_wumpus.h>
#include <ai_pl.h>
#include <cstdio>

namespace starter
{
  // ACTION
  GimliWumpusAction::GimliWumpusAction(int action_code_in)
  {
    w_action = new ai::Wumpus::Action;
    w_action->SetCode(action_code_in);
  }
  GimliWumpusAction::~GimliWumpusAction()
  {
    delete w_action;
  }
  int GimliWumpusAction::GetActionCode() const
  {
    return w_action->GetCode();
  }

  // STATE
  bool GimliWumpusState::IsEqual(const ai::Search::State * const state_in) const
  {
    const GimliWumpusState * const rhs = dynamic_cast<const GimliWumpusState * const>(state_in);
    return (x == rhs->x) && (y == rhs->y) &&
      (direction == rhs->direction) && (shot == rhs->shot);
  }

  bool GimliWumpusState::IsLessThan(const ai::Search::State * const state_in) const
  {
    const GimliWumpusState * const rhs = dynamic_cast<const GimliWumpusState * const>(state_in);
    if( x < rhs->x ) { return true; }
    else if( x > rhs->x ) { return false; }
    else {
      if( y < rhs->y ) { return true; }
      else if( y > rhs->y ) { return false; }
      else {
        if( direction < rhs->direction ) { return true; }
        else if( direction > rhs->direction ) { return false; }
        else {
          if( shot < rhs->shot ) { return true; }
          else if( shot > rhs->shot ) { return false; }
          else {
            return false;
          }
        }
      }
    }
  }

  // PROBLEM
  GimliWumpusProblem::GimliWumpusProblem(GimliWumpusState *initial_state_in,
                                         GimliKnowledgeBase *kb_in,
                                         int width_in, int height_in,
                                         bool shoot_wumpus_in) 
    : ai::Search::Problem(initial_state_in)
  {
    kb = kb_in;
    width = width_in;
    height = height_in;
    shoot_wumpus = shoot_wumpus_in;
  }
    
  GimliWumpusProblem::~GimliWumpusProblem()
  {
    // nothing
  }
  
  bool   GimliWumpusProblem::GoalTest(const ai::Search::State * const state_in) const
  {
    const GimliWumpusState * const state = dynamic_cast<const GimliWumpusState * const>(state_in);
    bool rval;

    /* normal mode, state is safe, unvisited location */
    /* hunt mode, state is facing wumpus, and arrow released */
    if(shoot_wumpus == false)
      {
        rval = kb->AskSafe(state->x, state->y);
        rval = rval && (!kb->AskVisited(state->x, state->y));
      }
    else
      {
        rval = (kb->AskAimedAtWumpus(state->x, state->y, state->direction) && (state->shot == 1));
      }
      
    return rval;
  }
    
  std::vector<ai::Search::Action *> GimliWumpusProblem::Actions( const ai::Search::State * const state_in ) {
    const GimliWumpusState * const state = dynamic_cast<const GimliWumpusState * const>(state_in);
    std::vector<ai::Search::Action *> actions;

    /* hunt mode: if facing wumpus, then shoot */
    if(shoot_wumpus && kb->AskAimedAtWumpus(state->x, state->y, state->direction))
      {
        GimliWumpusAction *action  = new GimliWumpusAction(ai::Wumpus::Action::SHOOT);
        actions.push_back(action);
      }
    /* normal mode OR hunt mode and not facing wumpus:
     *  if forward is on the board and safe, then move forward
     *  always turn left
     *  always turn right*/
    else
      {
        int x         = state->x;
        int y         = state->y;
        int direction = state->direction;
	  
        if     (direction == 0)    { x += 1; }
        else if(direction == 90)   { y += 1; }
        else if(direction == 180)  { x -= 1; }
        else if(direction == 270)  { y -= 1; }
        else                       { std::cerr << "Unexpected direction: " << direction << std::endl; }
        if(x >= 1 && x <= width && y >= 1 && y <= height)
          {
            bool rval = kb->AskSafe(x, y);
            if(rval)
              {
                GimliWumpusAction *action  = new GimliWumpusAction(ai::Wumpus::Action::FORWARD);
                actions.push_back(action);
              }
          }
        if(true)
          {
            GimliWumpusAction *action  = new GimliWumpusAction(ai::Wumpus::Action::TURN_LEFT);
            actions.push_back(action);
          }
        if(true)
          {
            GimliWumpusAction *action  = new GimliWumpusAction(ai::Wumpus::Action::TURN_RIGHT);
            actions.push_back(action);
          }
      }
    return actions;
  }

  ai::Search::State *GimliWumpusProblem::Result( const ai::Search::State * const state_in, const ai::Search::Action * const action_in ) {
    const GimliWumpusState * const state = dynamic_cast<const GimliWumpusState * const>(state_in);
    const GimliWumpusAction * const action = dynamic_cast<const GimliWumpusAction * const>(action_in);
    GimliWumpusState  *state_2 = new GimliWumpusState;
    switch(action->GetActionCode()) {
    case ai::Wumpus::Action::SHOOT:
      state_2->x         = state->x;
      state_2->y         = state->y;
      state_2->direction = state->direction;
      state_2->shot      = 1;
      break;
    case ai::Wumpus::Action::FORWARD: 
      {
        int x         = state->x;
        int y         = state->y;
        int direction = state->direction;
        if     (direction == 0)    { x += 1; }
        else if(direction == 90)   { y += 1; }
        else if(direction == 180)  { x -= 1; }
        else if(direction == 270)  { y -= 1; }
        else                       { std::cerr << "Unexpected direction: " << direction << std::endl; }
        state_2->x         = x;
        state_2->y         = y;
        state_2->direction = direction;
        state_2->shot      = 0;
      }
      break;
    case ai::Wumpus::Action::TURN_LEFT:
      state_2->x         = state->x;
      state_2->y         = state->y;
      state_2->direction = state->direction;
      state_2->shot      = 0;
      state_2->direction += 90;
      state_2->direction %= 360;
      break;
    case ai::Wumpus::Action::TURN_RIGHT:
      state_2->x         = state->x;
      state_2->y         = state->y;
      state_2->direction = state->direction;
      state_2->shot      = 0;
      state_2->direction += 270;
      state_2->direction %= 360;
      break;
    default:
      std::cerr << "Bad Action" << std::endl;
      break;
    }
    return state_2;
  }

  double GimliWumpusProblem::StepCost(const ai::Search::State  * const state1_in,
                                      const ai::Search::Action * const action_in,
                                      const ai::Search::State  * const state2_in) const
  {
    (void) state1_in;
    (void) state2_in;
    const GimliWumpusAction * const action = dynamic_cast<const GimliWumpusAction * const>(action_in);
    double cost = 1.0;
    switch(action->GetActionCode())
      {
      case ai::Wumpus::Action::SHOOT:      cost = 10.0; break;
      case ai::Wumpus::Action::FORWARD:    cost =  1.0; break;
      case ai::Wumpus::Action::TURN_LEFT:  cost =  1.0; break;
      case ai::Wumpus::Action::TURN_RIGHT: cost =  1.0; break;
      default: std::cerr << "Unexpected WumpusAction type: " << action->GetActionCode() << std::endl; break;
      }
    return cost;
  }
}
