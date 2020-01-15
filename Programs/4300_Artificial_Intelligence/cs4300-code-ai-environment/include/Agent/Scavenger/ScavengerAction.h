#ifndef _SCAVENGERACTION_H_
#define _SCAVENGERACTION_H_

namespace ai
{
  namespace Scavenger
  {
    class Location;

    class Action: public ai::Agent::Action
    {
    public:
      Action();
      virtual ~Action();

      virtual bool TextDisplay(std::ostream &os) const;
      virtual bool ToMessage(ai::Agent::Message &omsg) const;
      virtual bool FromMessage(const ai::Agent::Message &imsg);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(const std::string &keyprefix, ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg);
      
      std::string GetObjectId (  );
      bool SetObjectId ( const std::string & object_id_in );

      Location::Direction GetDirection() const;
      bool SetDirection(Location::Direction direction_in);

      enum ActionEnum
        {
          /* Movement actions */
          GO_NORTH,
          GO_SOUTH,
          GO_EAST,
          GO_WEST,
          /* Look at the horizon in one direction */
          LOOK,

          /* others */
          RECHARGE,
          PICKUP,  /* Attempt to put an object in the bin */
          DROP,    /* Attempt to remove an object from the bin */
          DEPOSIT, /* Attempt to put an object from the bin to the base */
          EXAMINE, /* Examine the details of object */
          QUIT,    /* Stop playing */
          NOOP,    /* Do nothing this turn */

          /* */
          NONE
        };

    protected:
      std::string object_id;
      Location::Direction direction;

    private:
    };
  }
}

#endif /* _SCAVENGERACTION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
