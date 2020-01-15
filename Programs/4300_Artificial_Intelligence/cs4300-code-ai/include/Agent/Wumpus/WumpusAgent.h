#ifndef _WUMPUSAGENT_H_
#define _WUMPUSAGENT_H_

namespace ai
{
  namespace Wumpus
  {
    class Agent : public ai::XY::Agent
    {
    public:
      Agent();
      Agent(ai::Agent::Socket * sock_in);
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location);
      virtual ai::Agent::Action * MessageToAction(const ai::Agent::Message &imsg) const;
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);
      virtual void Shoot();
      virtual void Grab();
      virtual void Yell();
      virtual void UnYell();
      int          ArrowCount();
      int          GoldCount();
      bool         GetYellLast();
    protected:
      int arrows;
      int gold;
      int yell_last;
    private:
    };
  }
}

#endif /* _WUMPUSAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
