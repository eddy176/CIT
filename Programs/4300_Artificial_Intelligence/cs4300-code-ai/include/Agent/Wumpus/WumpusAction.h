#ifndef _WUMPUSACTION_H_
#define _WUMPUSACTION_H_

namespace ai
{
  namespace Wumpus
  {
    class Action : public ai::XY::Action
    {
    public:
      enum ActionEnum { GRAB = 1, SHOOT, TURN_RIGHT, TURN_LEFT, FORWARD, QUIT, YELL, NOOP };
      virtual bool TextDisplay(std::ostream & os) const;
      virtual bool ToMessage(ai::Agent::Message &omsg) const;
      virtual bool FromMessage(const ai::Agent::Message &imsg);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(const std::string &keyprefix, ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg);
    protected:
    private:
    };
  }
}

#endif /* _WUMPUSACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
