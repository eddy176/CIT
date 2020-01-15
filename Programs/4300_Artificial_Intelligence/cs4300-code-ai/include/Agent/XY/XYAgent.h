#ifndef _XYAGENT_H_
#define _XYAGENT_H_

namespace ai
{
  namespace XY
  {
    class Agent : public ai::Agent::Agent
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
      virtual void TurnRight();
      virtual void TurnLeft();
      virtual void Forward(int width_in, int height_in);
      int     GetDirection();
    protected:
      bool bump;
      int  direction;
    private:
    };
  }
}

#endif /* _XYAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
