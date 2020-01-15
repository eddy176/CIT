#include <ai_scavenger.h>
#include <cmath>
#include <cstdio>

static int l_debug = 0;

namespace ai
{
  namespace Scavenger
  {
    Agent::Agent()
      : m_base_location(0),
        m_hopper_volume_used(0)
    {
    }

    Agent::Agent(ai::Agent::Socket *sock_in)
      : ai::Agent::Agent(sock_in),
        m_base_location(0),
        m_hopper_volume_used(0),
        m_base_id(0),
        have_look(false),
        have_examine(false),
        have_deposit(false),
        have_pickup(false),
        quit_time_step(-1),
        last_time_step(-1),
        index(0),
        m_last_action(0)
    {
    }

    Agent::~Agent()
    {
      if(m_base_location)
        {
          delete m_base_location;
          m_base_location = 0;
        }
      if(m_last_action)
        {
          delete m_last_action;
          m_last_action = 0;
        }
    }

    void Agent::Initialize()
    {
      Environment *env = dynamic_cast<Environment *>(environment);
      charge     = env->GetMaxCharge();
      hit_points = env->GetMaxHitPoints();
    }

    void Agent::SetBaseLocation(Location *location_in)
    {
      m_base_location = location_in;
    }

    Location * Agent::GetBaseLocation()
    {
      return m_base_location;
    }

    ai::Agent::Percept *Agent::GetPercept(const ai::Agent::Location *location_in)
    {
      Environment *env = dynamic_cast<Environment *>(environment);
      const Location *location   = dynamic_cast<const Location *>(location_in);
      if(m_base_location == 0)
        {
          DBGP_E(LOG_STREAM(std::cerr) << "m_base_location is 0" << std::endl);
        }

      char charge_str[16];
      sprintf(charge_str, "%.2f", charge);
      char hp_str[16];
      sprintf(hp_str, "%.2f", hit_points);

      char x_loc_str[16];
      char y_loc_str[16];
      char z_loc_str[16];
      sprintf(x_loc_str, "%.2f", location->GetX()-m_base_location->GetX());
      sprintf(y_loc_str, "%.2f", location->GetY()-m_base_location->GetY());
      sprintf(z_loc_str, "%.2f", location->GetElevation()-m_base_location->GetElevation());

      ai::Agent::Percept *p = new ai::Agent::Percept;

      ai::Agent::PerceptAtom p_CHARGE("CHARGE", charge_str);
      ai::Agent::PerceptAtom p_HP("HP", hp_str);
      ai::Agent::PerceptAtom p_X_LOC("X_LOC", x_loc_str);
      ai::Agent::PerceptAtom p_Y_LOC("Y_LOC", y_loc_str);
      ai::Agent::PerceptAtom p_Z_LOC("Z_LOC", z_loc_str);

      p->JoinAtom(p_CHARGE);
      p->JoinAtom(p_HP);
      p->JoinAtom(p_X_LOC);
      p->JoinAtom(p_Y_LOC);
      p->JoinAtom(p_Z_LOC);

      if(have_look)
        {
          char look_str[64];
          sprintf(look_str, "%s", look.c_str());
          ai::Agent::PerceptAtom p_LOOK("LOOK", look_str);
          p->JoinAtom(p_LOOK);
          have_look = false;
        }

      if(have_examine)
        {
          char examine_str[64];
          sprintf(examine_str, "%s", examine.c_str());
          ai::Agent::PerceptAtom p_EXAMINE("EXAMINE", examine_str);
          p->JoinAtom(p_EXAMINE);
          have_examine = false;
        }

      if(have_deposit)
        {
          if(env->GetObjectLearning())
            {
              ai::Agent::PerceptAtom p_DEPOSIT("DEPOSIT_VALUE", deposit_string);
              p->JoinAtom(p_DEPOSIT);
            }
          have_deposit = false;
        }

      if(have_pickup)
        {
          ai::Agent::PerceptAtom p_PICKUP("PICKUP", pickup_string);
          p->JoinAtom(p_PICKUP);
          have_pickup = false;
          pickup_string = "";
        }

      /* put all hopper items into percept */
      for(auto hit = hopper.begin(); hit != hopper.end(); hit++)
        {
          const std::string &id_str = environment->GetObject(hit->second)->GetIdString();
          p->JoinAtom(ai::Agent::PerceptAtom("HOPPER_" + id_str, id_str));
        }

      return p;
    }

    ai::Agent::Action * Agent::MessageToAction(const ai::Agent::Message &imsg) const
    {
      Action *action = new Action();
      if(!action->FromMessage(imsg))
        {
          delete action;
          action = 0;
        }
      return action;
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool Agent::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::Agent::Agent::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }

      Location *sl = dynamic_cast<Location *>(location);
      if(sl)
        {
          ADD_TO_MSG("OBJECT_HAS_SCAVLOCATION " << m_object_id, true, omsg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVLOCATION_X " << m_object_id, sl->x, omsg, old_msg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVLOCATION_Y " << m_object_id, sl->y, omsg, old_msg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVLOCATION_ELEVATION " << m_object_id, sl->elevation, omsg, old_msg);
        }
      else
        {
          ADD_TO_MSG("OBJECT_HAS_SCAVLOCATION " << m_object_id, false, omsg);
        }
      sl = dynamic_cast<Location *>(m_base_location);
      if(sl)
        {
          ADD_TO_MSG("OBJECT_HAS_SCAVBLOCATION " << m_object_id, true, omsg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVBLOCATION_X " << m_object_id, sl->x, omsg, old_msg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVBLOCATION_Y " << m_object_id, sl->y, omsg, old_msg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVBLOCATION_ELEVATION " << m_object_id, sl->elevation, omsg, old_msg);
        }
      else
        {
          ADD_TO_MSG("OBJECT_HAS_SCAVBLOCATION " << m_object_id, false, omsg);
        }

      //
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_CHARGE " << m_object_id, charge, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_HIT_POINTS " << m_object_id, hit_points, omsg, old_msg);
      ADD_MAP_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_HOPPER " << m_object_id, hopper, omsg, old_msg);
      ADD_MAP_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_VISITED_CELLS " << m_object_id, visited_cells, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_BASE_ID " << m_object_id, m_base_id, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_HAVE_LOOK " << m_object_id, have_look, omsg, old_msg);
      if(have_look)
        {
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_LOOK " << m_object_id, look, omsg, old_msg);
        }
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_HAVE_EXAMINE " << m_object_id, have_examine, omsg, old_msg);
      if(have_examine)
        {
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_EXAMINE " << m_object_id, examine, omsg, old_msg);
        }
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_HAVE_DEPOSIT " << m_object_id, have_deposit, omsg, old_msg);
      if(have_deposit)
        {
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_DEPOSIT " << m_object_id, deposit_string, omsg, old_msg);
        }
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_HAVE_PICKUP " << m_object_id, have_pickup, omsg, old_msg);
      if(have_pickup)
        {
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_PICKUP " << m_object_id, pickup_string, omsg, old_msg);
        }
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_QUIT_TIME " << m_object_id, quit_time_step, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_LAST_TIME " << m_object_id, last_time_step, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVAGENT_INDEX " << m_object_id, index, omsg, old_msg);
      if(m_last_action)
        {
          std::stringstream ss;
          ss << "OBJECT_SCAVAGENT" << m_object_id;
          std::string keyprefix = ss.str();
          if(!m_last_action->AddToMessageIfChanged(keyprefix, omsg, old_msg))
            {
              DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
            }
        }
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool Agent::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::Agent::Agent::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      bool has_slocation = false;
      SET_FROM_MSG("OBJECT_HAS_SCAVLOCATION " << m_object_id, has_slocation, imsg);
      if(has_slocation)
        {
          Location *sl = dynamic_cast<Location *>(location);
          if(!sl)
            {
              if(location) { delete location; location = 0; }
              location = sl = new Location;
            }
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVLOCATION_X " << m_object_id, sl->x, imsg);
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVLOCATION_Y " << m_object_id, sl->y, imsg);
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVLOCATION_ELEVATION " << m_object_id, sl->elevation, imsg);
        }
      bool has_blocation = false;
      SET_FROM_MSG("OBJECT_HAS_SCAVBLOCATION " << m_object_id, has_blocation, imsg);
      if(has_slocation)
        {
          Location *sl = dynamic_cast<Location *>(m_base_location);
          if(!sl)
            {
              if(m_base_location) { delete m_base_location; m_base_location = 0; }
              m_base_location = sl = new Location;
            }
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVBLOCATION_X " << m_object_id, sl->x, imsg);
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVBLOCATION_Y " << m_object_id, sl->y, imsg);
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVBLOCATION_ELEVATION " << m_object_id, sl->elevation, imsg);
        }

      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_CHARGE " << m_object_id, charge, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_HIT_POINTS " << m_object_id, hit_points, imsg);
      SET_MAP_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_HOPPER " << m_object_id, hopper, unsigned int, imsg);
      SET_MAP_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_VISITED_CELLS " << m_object_id, visited_cells, Location, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_BASE_ID " << m_object_id, m_base_id, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_HAVE_LOOK " << m_object_id, have_look, imsg);
      if(have_look)
        {
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_LOOK " << m_object_id, look, imsg);
        }
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_HAVE_EXAMINE " << m_object_id, have_examine, imsg);
      if(have_examine)
        {
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_EXAMINE " << m_object_id, examine, imsg);
        }
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_HAVE_DEPOSIT " << m_object_id, have_deposit, imsg);
      if(have_deposit)
        {
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_DEPOSIT " << m_object_id, deposit_string, imsg);
        }
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_HAVE_PICKUP " << m_object_id, have_pickup, imsg);
      if(have_pickup)
        {
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_PICKUP " << m_object_id, pickup_string, imsg);
        }
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_QUIT_TIME " << m_object_id, quit_time_step, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_LAST_TIME " << m_object_id, last_time_step, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVAGENT_INDEX " << m_object_id, index, imsg);
      {
        if(!m_last_action)
          {
            m_last_action = new Action();
          }
        std::stringstream ss;
        ss << "OBJECT_SCAVAGENT" << m_object_id;
        std::string keyprefix = ss.str();
        if(!m_last_action->SetFromMessageIfExists(keyprefix, imsg))
          {
            DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          }
      }
      return true;
    }

    bool Agent::Move ( const Cell &from,
                       const CellInterface &iface,
                       const Cell &to,
                       int time_step_in )
    {
      this->last_time_step = time_step_in;
      Environment *env = dynamic_cast<Environment *>(environment);

      if(!IsAlive())
        {
          if(l_debug > 1)
            {
              std::cout << "Agent is not alive" << std::endl;
            }
          return false;
        }
      if(charge <= 0.)
        {
          if(l_debug > 1)
            {
              std::cout << "Agent is out of charge" << std::endl;
            }
          return false;
        }
      double dx = from.GetLocation().GetX() - to.GetLocation().GetX();
      double dy = from.GetLocation().GetY() - to.GetLocation().GetY();
      double dz = from.GetLocation().GetElevation() - to.GetLocation().GetElevation();
      double dist = std::sqrt(dx*dx + dy*dy);

      /* new_charge = old_charge
       *              - interface penalty
       *              - horizontal travel cost
       *              - vertical travel cost */
      charge     -= iface.GetEnergyCost();
      charge     -= dist * env->GetHChargePerMeter();
      if(!iface.IsFall()) /* No fair jumping off of cliffs to recharge! */
        {
          charge     += dz   * env->GetVChargePerMeter(); /* The += provides energy
                                                           * generation on downhill
                                                           * slopes */
        }
      TakeDamage(iface.GetDamage());
      if(charge < .0) { alive = false; }

      if(iface.IsFall() && (dz > 0))
        {
          TakeDamage(dz*env->GetFallDamagePerMeter());
        }

      if(!iface.Traversable())
        {
          if(l_debug > 1)
            {
              std::cout << "Interface is not traversable" << std::endl;
              std::cout << iface.GetString() << std::endl;
            }
          return false;
        }

      Location *sl = dynamic_cast<Location *>(location);

      sl->Set(to.GetLocation().GetX(),
              to.GetLocation().GetY(),
              to.GetLocation().GetElevation());

      visited_cells[from.GetLocation()] = 1;
      visited_cells[to.GetLocation()] = 1;

      return true;
    }

    bool Agent::Look( const std::string &look_in, int time_step_in )
    {
      this->last_time_step = time_step_in;
      Environment *env = dynamic_cast<Environment *>(environment);
      charge     -= env->GetLookCharge();
      if(charge < .0) { alive = false; }

      look = look_in;
      have_look = true;
      return true;
    }

    bool Agent::Recharge ( int time_step_in )
    {
      this->last_time_step = time_step_in;
      Environment *env = dynamic_cast<Environment *>(environment);

      charge += env->GetRechargePerTurn();
      if(charge > env->GetMaxCharge())
        {
          charge = env->GetMaxCharge();
        }
      return true;
    }

    bool Agent::Pickup ( ai::Scavenger::Object * object, int time_step_in  )
    {
      this->last_time_step = time_step_in;
      Environment *env = dynamic_cast<Environment *>(environment);
      charge     -= env->GetPickupCharge();
      if(charge < .0) { alive = false; }

      have_pickup = true;
      if(!object)
        {
          pickup_string = "None";
          return false;
        }

      if(object->GetMass() > env->GetMaxArmMass())
        {
          TakeDamage(env->GetLiftDamage());
          pickup_string = "Massive";
          return false;
        }

      /* calculate volume currently used by hopper items */
      if((m_hopper_volume_used + object->GetVolume()) > env->GetMaxBinVolume())
        {
          pickup_string = "Full";
          return false;
        }
      m_hopper_volume_used += object->GetVolume();
      hopper[object->GetIdNum()] = object->GetIdNum();
      pickup_string = object->GetPickupString();
      return true;
    }

    bool Agent::Drop ( ai::Scavenger::Object * object, int time_step_in  )
    {
      this->last_time_step = time_step_in;
      Environment *env = dynamic_cast<Environment *>(environment);
      charge     -= env->GetDropCharge();
      if(charge < .0) { alive = false; }

      /* remove object from hopper */
      auto hit = hopper.find(object->GetIdNum());
      if(hit == hopper.end())
        {
          return false;
        }
      hopper.erase(hit);
      m_hopper_volume_used -= object->GetVolume();

      return true;
    }


    bool Agent::Deposit ( ai::Scavenger::Object * object, int time_step_in  )
    {
      this->last_time_step = time_step_in;
      Environment *env = dynamic_cast<Environment *>(environment);
      charge     -= env->GetDepositCharge();
      if(charge < .0) { alive = false; }

      /* remove object from hopper */
      auto hit = hopper.find(object->GetIdNum());
      if(hit == hopper.end())
        {
          return false;
        }
      hopper.erase(hit);
      m_hopper_volume_used -= object->GetVolume();

      have_deposit = true;
      deposit_string = object->GetDepositString();
      return true;
    }

    bool Agent::Examine( const std::string &examine_in, int time_step_in  )
    {
      this->last_time_step = time_step_in;
      Environment *env = dynamic_cast<Environment *>(environment);
      charge     -= env->GetExamineCharge();
      if(charge < .0) { alive = false; }

      examine = examine_in;
      have_examine = true;
      return true;
    }

    bool Agent::Quit ( int time_step_in )
    {
      quit_time_step = time_step_in;
      alive = false;
      return true;
    }

    std::map<unsigned int, unsigned int> & Agent::GetHopper (  )
    {
      return hopper;
    }

    ai::Scavenger::Object * Agent::GetObject(const unsigned int object_id_in)
    {
      auto hit = hopper.find(object_id_in);
      if(hit != hopper.end())
        {
          return dynamic_cast<ai::Scavenger::Object *>(environment->GetObject(object_id_in));
        }
      return 0;
    }

    void Agent::TakeDamage( double hit_points_lost )
    {
      hit_points -= hit_points_lost;
      if(hit_points <= .0)
        {
          alive = false;
        }
    }

    void Agent::DrainCharge( double charge_lost )
    {
      charge -= charge_lost;
      if(charge < .0)
        {
          alive = false;
        }
    }


    void Agent::SetBase( unsigned int base_id_in )
    {
      m_base_id = base_id_in;
    }

    unsigned int Agent::GetBase( )
    {
      return m_base_id;
    }

    int  Agent::GetQuitTimeStep() const
    {
      return quit_time_step;
    }

    int  Agent::GetLastTimeStep() const
    {
      return last_time_step;
    }

    double Agent::GetCharge() const
    {
      return charge;
    }
    double Agent::GetHitPoints() const
    {
      return hit_points;
    }

    int    Agent::GetNumVisitedCells() const
    {
      return (int)visited_cells.size();
    }

    void   Agent::SetIndex( int index_in )
    {
      index = index_in;
    }

    int    Agent::GetIndex() const
    {
      return index;
    }

    void Agent::SetAction( Action * action )
    {
      if( m_last_action )
        {
          delete m_last_action;
          m_last_action = NULL;
        }
      if( action )
        {
          m_last_action = new Action( *action );
        }
    }

    Action * Agent::GetAction()
    {
      return m_last_action;
    }

  }
}
