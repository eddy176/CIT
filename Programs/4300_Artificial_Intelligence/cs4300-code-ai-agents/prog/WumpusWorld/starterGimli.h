#ifndef _STARTERGIMLI_H_
#define _STARTERGIMLI_H_

#include <ai_wumpus.h>
#include <ai_pl.h>
#include <queue>
#include "starterGimliKnowledgeBase.h"

namespace starter
{
  class Gimli : public ai::Agent::AgentProgram
  {
  public:
    Gimli(ai::Agent::Options *opts);
    ~Gimli();
    virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
  
  protected:
    ai::Agent::Action * ChooseAction();

    void ManagePercepts(const ai::Agent::Percept * percept);
    void ManageWidthHeight(const ai::Agent::Percept * percept);
    void ManageLocation(const ai::Agent::Percept * percept);
    void ManageGlitter(const ai::Agent::Percept * percept);
    void ManageBreeze(const ai::Agent::Percept * percept);
    void ManageStench(const ai::Agent::Percept * percept);
    void ManageScream(const ai::Agent::Percept * percept);
    
    bool ForwardIsSafe();
    bool SearchForAction(bool shoot_wumpus);
    bool FindNearestUnvisitedSafe();
    bool ShootWumpus();
    bool WumpusNearStart();
    bool BreezesBlockPathNorth();
    bool BreezesBlockPathSouth();
    bool BreezesBlockPathEast();
    bool BreezesBlockPathWest();
    bool ProbabilityCheck();


    
    /* data */
    GimliKnowledgeBase kb;

    // current status
    int x;           // 1 to width
    int y;           // 1 to height
    int direction;   // what direction 0, 90, 180, 270 (East, North, West, South)
    
    int last_action; // what was the last action sent?
    int gold;        // how much gold am i carrying?
    int arrows;      // how many arrows am i carrying?

    // cavern size
    int width;
    int height;

    // pit probability
    double pit_probability;
    
    // scheduled actions
    std::queue<int> plan; // The int's are action codes
  private:
  };
};

#endif /* _STARTERGIMLI_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
