#ifndef _STARTERGIMLIWUMPUSSEARCH_H_
#define _STARTERGIMLIWUMPUSSEARCH_H_

#include <ai_pl.h>
#include <ai_search.h>
#include <ai_wumpus.h>
#include "starterGimliKnowledgeBase.h"

namespace starter
{
  class GimliWumpusAction : public ai::Search::Action
  {
  public:
    GimliWumpusAction(int action_code_in);
    virtual ~GimliWumpusAction();
    int GetActionCode() const;
  protected:
    ai::Wumpus::Action *w_action;
  private:
  };
  
  class GimliWumpusState : public ai::Search::State
  {
  public:
    virtual bool IsEqual(const ai::Search::State * const state_in) const;
    virtual bool IsLessThan(const ai::Search::State * const state_in) const;
    
    int x;
    int y;
    int direction;
    int shot;
  protected:
  private:
  };
  
  class GimliWumpusProblem : public ai::Search::Problem
  {
  public:
    GimliWumpusProblem(GimliWumpusState *initial_state_in,
                       GimliKnowledgeBase *kb_in,
                       int width_in, int height_in,
                       bool shoot_wumpus_in = false);
    virtual ~GimliWumpusProblem();
    virtual bool   GoalTest(const ai::Search::State * const state_in) const;
    virtual std::vector<ai::Search::Action *> Actions( const ai::Search::State * const state_in );
    virtual ai::Search::State *Result( const ai::Search::State * const state_in, const ai::Search::Action * const action_in );
    virtual double StepCost(const ai::Search::State  * const state1_in,
                            const ai::Search::Action * const action_in,
                            const ai::Search::State  * const state2_in) const;
      

  protected:
    GimliKnowledgeBase *kb;
    int width;
    int height;
    bool shoot_wumpus;
  private:
  };
};

#endif /* _STARTERGIMLIWUMPUSSEARCH_H_ */

/* Local Variables: */
/* mode:c++         */
/* End:             */
