#ifndef _SCAVENGERENVIRONMENT_H_
#define _SCAVENGERENVIRONMENT_H_

namespace ai
{
  namespace Scavenger
  {
    class Environment: public ai::Agent::Environment
    {
      friend class EnvironmentDisplay;
      friend class EnvironmentDisplay3D;    // 3D Display
      friend class EnvironmentModel;        // 3D Display EnvironmentModel
    public:
      Environment();
      Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in,
                  const std::string &world_filename_in);
      /*
       * Deletes all Cells in the cells collection.
       */
      ~Environment();

      virtual bool ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action);
      virtual void CalculatePerformance(ai::Agent::Agent *agent);
      virtual ai::Agent::Percept *GetPercept(ai::Agent::Agent *agent);
      virtual void Step();
      virtual void Run(const int n_steps);
      virtual void AddAgent(ai::Agent::Agent *agent, ai::Agent::Location *location);
      virtual ai::Agent::Location *DefaultLocation() const;
      /*
       * Handle messages with the client.
       */
      virtual bool GetUpdateMessage(ai::Agent::Message &omsg);
      virtual bool UpdateFromMessage(ai::Agent::Message &imsg);

      bool SetFullyObservable(const bool value_in);
      bool SetObjectLearning(const bool value_in);
      bool SetMaxCharge(const double value_in);
      bool SetRechargePerTurn(const double value_in);
      bool SetMaxHitPoints(const double value_in);
      bool SetMaxBinVolume(const double value_in);
      bool SetMaxArmMass(const double value_in);
      bool SetLiftDamage(const double value_in);
      bool SetFallDamagePerMeter(const double value_in);
      bool SetRechargeDamage(const double value_in);
      bool SetRechargeCharge(const double value_in);
      bool SetVChargePerMeter(const double value_in);
      bool SetHChargePerMeter(const double value_in);
      bool SetLookCharge(const double value_in);
      bool SetPickupCharge(const double value_in);
      bool SetDropCharge(const double value_in);
      bool SetDepositCharge(const double value_in);
      bool SetExamineCharge(const double value_in);
      bool SetSkipObjectCount(const unsigned int value_in);
      bool SetMaxObjectCount(const unsigned int value_in);

      bool   GetFullyObservable() const;
      bool   GetObjectLearning() const;
      double GetMaxCharge() const;
      double GetRechargePerTurn() const;
      double GetMaxHitPoints() const;
      double GetMaxBinVolume() const;
      double GetMaxArmMass() const;
      double GetLiftDamage() const;
      double GetFallDamagePerMeter() const;
      double GetRechargeDamage() const;
      double GetRechargeCharge() const;
      double GetVChargePerMeter() const;
      double GetHChargePerMeter() const;
      double GetLookCharge() const;
      double GetPickupCharge() const;
      double GetDropCharge() const;
      double GetDepositCharge() const;
      double GetExamineCharge() const;
      unsigned int GetSkipObjectCount() const;
      unsigned int GetMaxObjectCount() const;

      bool   MakeEnoughBases(int num_agents);

      void check_cells(const std::string &msg);
    protected:
      void TextDisplay(std::ostream &os) const;

      bool ReadFile();

      bool MoveAgent(Agent *sw_agent, int action_code);
      bool LookAgent(Agent *sw_agent, Location::Direction direction);
      bool RechargeAgent(Agent *sw_agent);
      bool PickupObject(Agent *sw_agent, const std::string &objec_id_in);
      bool DropObject(Agent *sw_agent, const std::string &objec_id_in);
      bool DepositObject(Agent *sw_agent, const std::string &objec_id_in);
      bool ExamineObject(Agent *sw_agent, const std::string &objec_id_in);
      bool QuitAgent(Agent *sw_agent);

      std::string world_filename;

      std::map<unsigned int, Base *>         bases;
      std::map<Location, Cell*>              cells;
      std::map<unsigned int, Cell*>          cells_by_id;
      std::map<std::string, CellInterface *> cell_interfaces;
      unsigned int                           goal_cell_id; // only used in fully observable

      int time_step; // The current time step, starting at 0


      bool   fully_observable;
      bool   object_learning;
      double max_charge;
      double recharge_per_turn;
      double max_hit_points;
      double max_bin_volume;
      double max_arm_mass;
      double lift_damage;
      double fall_damage_per_meter;
      double recharge_damage; // trying to recharge at opponent's base
      double recharge_charge; // trying to recharge when not at own base
      double v_charge_per_meter;
      double h_charge_per_meter;
      double look_charge;
      double pickup_charge;
      double drop_charge;
      double deposit_charge;
      double examine_charge;
      unsigned int skip_object_count;
      unsigned int max_object_count;

    private:
    };

  }
}

#endif /* _SCAVENGERENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
