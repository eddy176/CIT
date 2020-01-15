#ifndef _SCAVENGERAGENT_H_
#define _SCAVENGERAGENT_H_

namespace ai
{
  namespace Scavenger
  {
    class Cell;

    class Agent: public ai::Agent::Agent
    {
    public:
      Agent();
      Agent(ai::Agent::Socket *sock_in);
      virtual ~Agent();
      void Initialize();
      void SetBaseLocation(Location *location_in);
      Location * GetBaseLocation();

      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);
      virtual ai::Agent::Action * MessageToAction(const ai::Agent::Message &imsg) const;
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);

      bool Move (const Cell &from, const CellInterface &iface, const Cell &to, int time_step_in);
      bool Look( const std::string &look_in, int time_step_in );
      bool Recharge ( int time_step_in );
      bool Pickup ( ai::Scavenger::Object * object, int time_step_in );
      bool Drop ( ai::Scavenger::Object * object, int time_step_in );
      bool Deposit ( ai::Scavenger::Object * object, int time_step_in );
      bool Examine( const std::string &examine_in, int time_step_in );
      bool Quit ( int time_step_in );
      std::map<unsigned int, unsigned int> & GetHopper (  );
      ai::Scavenger::Object * GetObject(const unsigned int object_id_in);

      void TakeDamage( double hit_points_lost );
      void DrainCharge( double charge_lost );

      void SetBase( unsigned int base_id_in );
      unsigned int GetBase( );
      int  GetQuitTimeStep() const;
      int  GetLastTimeStep() const;

      double GetCharge() const;
      double GetHitPoints() const;
      int    GetNumVisitedCells() const;

      void   SetIndex( int index_in );
      int    GetIndex() const;

      void  SetAction( Action * action );
      Action * GetAction();
    protected:
      Location *m_base_location;
      double charge;
      double hit_points;

      double m_hopper_volume_used;
      std::map<unsigned int, unsigned int> hopper;

      std::map<Location, int>          visited_cells;

      unsigned int m_base_id;

      /* for looking at horizon interfaces */
      bool        have_look;
      std::string look;

      /* for examining at objects */
      bool        have_examine;
      std::string examine;

      /* for learning feedback on object value */
      bool        have_deposit;
      std::string deposit_string;

      /* for pickup results */
      bool        have_pickup;
      std::string pickup_string;

      /* The time step when the agent decided to stop */
      int quit_time_step;

      /* The last time step when the agent executed a command */
      int last_time_step;

      /* Agent's uniq index */
      int    index;

      /* Agent's last action */
      Action *m_last_action;
    private:
    };
  }
}

#endif /* _SCAVENGERAGENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
