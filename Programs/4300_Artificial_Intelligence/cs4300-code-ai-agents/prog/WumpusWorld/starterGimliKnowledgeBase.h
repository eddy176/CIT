#ifndef _STARTERGIMLIKNOWLEDGEBASE_H_
#define _STARTERGIMLIKNOWLEDGEBASE_H_

#include <ai_pl.h>

namespace starter
{
  class GimliKnowledgeBase : public ai::PL::KnowledgeBase
  {
  public:
    GimliKnowledgeBase();
    virtual ~GimliKnowledgeBase();
    void SetSize(int width_in, int height_in);

    bool AskGold(int x_in, int y_in);
    bool AskNoPit(int x_in, int y_in);
    bool AskPit(int x_in, int y_in);
    bool AskNoWumpus(int x_in, int y_in);
    bool AskWumpus(int x_in, int y_in);
    bool AskNotSafe(int x_in, int y_in);
    bool AskSafe(int x_in, int y_in);
    bool AskVisited(int x_in, int y_in);
    bool AskAimedAtWumpus(int x_in, int y_in, int direction_in);
    bool AskWumpusAlive();
    bool AskBreeze(int x_in, int y_in);
    bool AskStench(int x_in, int y_in);
    bool AskB1(int x_in, int y_in);
    bool AskB2(int x_in, int y_in);
    void TellB2Rules();
    void TellShot();
    void TellShotRules();




    void TellNoGlitter(int x_in, int y_in);
    void TellGlitter(int x_in, int y_in);
    void TellNoBreeze(int x_in, int y_in);
    void TellBreeze(int x_in, int y_in);
    void TellNoStench(int x_in, int y_in);
    void TellStench(int x_in, int y_in);
    void TellNoPit(int x_in, int y_in);
    void TellWumpusDead();
    void TellNoWumpus(int x_in, int y_in);
    void TellWumpus(int x_in, int y_in);
    void TellVisited(int x_in, int y_in);
    void TellGlitterRules();
    void TellBreezeRules();
    void TellStenchRules();
    void TellSafeRules();
    void TellB1Rules();
    void TellSafe(int x_in, int y_in);


    
  protected:
    int width;
    int height;
  private:
  };
};

#endif /* _STARTERGIMLIKNOWLEDGEBASE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
