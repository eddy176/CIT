#ifndef _XYOBJECT_H_
#define _XYOBJECT_H_

namespace ai
{
  namespace XY
  {
    class Object : public ai::Agent::Object
    {
    public:
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location);
      virtual bool Near(const ai::Agent::Location *location, int radius);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);
    protected:
    private:
    };
  }
}

#endif /* _XYOBJECT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
