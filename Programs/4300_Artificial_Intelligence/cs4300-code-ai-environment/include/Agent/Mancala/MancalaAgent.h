#ifndef _MANCALAAGENT_H_
#define _MANCALAAGENT_H_
namespace ai
{
  namespace Mancala
  {
    class Agent : public ai::Agent::Agent
    {
    public:
      Agent();
      Agent(ai::Agent::Socket * sock_in);
      virtual ~Agent();
      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);
      virtual ai::Agent::Action * MessageToAction(const ai::Agent::Message &imsg) const;
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);

      /*
       * set the player's number.  This number should be 1-2
       */
      bool SetPlayerNumber(int n_in);

      /*
       * get the player's number.
       */
      int GetPlayerNumber() const;

      /*
       * Duration is used internally by Environment to track the
       * number of seconds the player is using to think.
       */
      void SetDuration(double duration_in);
      double GetDuration() const;
    protected:
      int player_number;
      double duration;

    private:
    };
  }
}
#endif /* _MANCALAAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
