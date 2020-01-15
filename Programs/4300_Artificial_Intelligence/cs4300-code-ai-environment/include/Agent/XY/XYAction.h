#ifndef _XYACTION_H_
#define _XYACTION_H_

namespace ai
{
  namespace XY
  {
    class Action : public ai::Agent::Action
    {
    public:
      enum ActionEnum { TURN_RIGHT = 1, TURN_LEFT, FORWARD };
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

#endif /* _XYACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
