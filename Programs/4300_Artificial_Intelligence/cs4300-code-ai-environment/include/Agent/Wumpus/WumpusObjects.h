#ifndef _WUMPUSOBJECTS_H_
#define _WUMPUSOBJECTS_H_

namespace ai
{
  namespace Wumpus
  {
    class GoldObject : public ai::XY::Object
    {
    public:
      GoldObject();
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location);
      virtual bool Near(const ai::Agent::Location *location, int distance);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);
    protected:
    private:
    };

    class PitObject : public ai::XY::Object
    {
    public:
      PitObject();
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location);
      virtual bool Near(const ai::Agent::Location *location, int distance);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);
    protected:
    private:
    };

    class WumpusObject : public ai::XY::Object
    {
    public:
      WumpusObject();
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location);
      virtual bool Near(const ai::Agent::Location *location, int distance);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);
      virtual void Kill();
      virtual bool IsAlive() const;
    protected:
      bool alive;
      bool scream;
    private:
    };

    class TardisObject : public ai::XY::Object
    {
    public:
      TardisObject();
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location);
      virtual bool Near(const ai::Agent::Location *location, int distance);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);
    protected:
    private:
    };
  }
}

#endif /* _WUMPUSOBJECTS_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
