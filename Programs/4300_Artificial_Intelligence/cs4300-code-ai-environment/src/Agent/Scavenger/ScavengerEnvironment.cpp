#include <ai_scavenger.h>
#include <fstream>

#ifdef WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000);
#else
#include <unistd.h>
#endif
#ifdef GetObject /* some windows #define thanks sloppy coders */
#undef GetObject
#endif

static int l_debug = 0;

namespace ai
{
  namespace Scavenger
  {
    Environment::Environment()
    {
    }

    Environment::Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in,
                             const std::string &world_filename_in)
      : ai::Agent::Environment(rand_in, displays_in),
        world_filename(world_filename_in),
        time_step(0)
    {
      goal_cell_id          = -1;
      fully_observable      = false;
      object_learning       = false;
      max_charge            = 100.;
      recharge_per_turn     =  25.;
      max_hit_points        = 100.;
      max_bin_volume        = 100.;
      max_arm_mass          =  25.;
      lift_damage           =   5.;
      fall_damage_per_meter =   0.5;
      recharge_damage       =   5.;
      recharge_charge       =   1.;
      v_charge_per_meter    =   0.001;
      h_charge_per_meter    =   0.001;
      look_charge           =   0.25;
      pickup_charge         =   0.25;
      drop_charge           =   0.25;
      deposit_charge        =   0.25;
      examine_charge        =   0.25;
      skip_object_count     =   0;
      max_object_count      = 100000;
      ReadFile();
    }

    Environment::~Environment()
    {
      std::map<Location, Cell *>::iterator it;
      for(it = cells.begin(); it != cells.end(); it++)
        {
          delete it->second;
          it->second = 0;
        }

      std::map<std::string, CellInterface *>::iterator ci_it;
      for(ci_it = cell_interfaces.begin(); ci_it != cell_interfaces.end(); ci_it++)
        {
          delete ci_it->second;
          ci_it->second = 0;
        }
    }

    bool Environment::ApplyAction(ai::Agent::Agent *agent_in, ai::Agent::Action *action)
    {
      ai::Scavenger::Agent *agent = dynamic_cast<ai::Scavenger::Agent *>(agent_in);
      if(l_debug > 1)
        {
          std::cout << "ApplyAction " << agent->GetName() << " ";
          action->TextDisplay(std::cout);
          std::cout << std::endl;
        }
      if(!agent->IsAlive())
        {
          if(l_debug > 1)
            {
              std::cout << "Agent is not alive" << std::endl;
            }
          return false;
        }
      Action *sw_action = dynamic_cast<Action *>(action);
      Agent  *sw_agent  = dynamic_cast<Agent *>(agent);

      sw_agent->SetAction( sw_action );

      switch(sw_action->GetCode())
        {
        case Action::GO_NORTH:
        case Action::GO_SOUTH:
        case Action::GO_EAST:
        case Action::GO_WEST:
          return MoveAgent(sw_agent, sw_action->GetCode());
          break;
        case Action::LOOK:
          return LookAgent(sw_agent, sw_action->GetDirection());
          break;
        case Action::RECHARGE:
          return RechargeAgent(sw_agent);
          break;
        case Action::PICKUP:
          return PickupObject(sw_agent, sw_action->GetObjectId());
          break;
        case Action::DROP:
          return DropObject(sw_agent, sw_action->GetObjectId());
          break;
        case Action::DEPOSIT:
          return DepositObject(sw_agent, sw_action->GetObjectId());
          break;
        case Action::EXAMINE:
          return ExamineObject(sw_agent, sw_action->GetObjectId());
          break;
        case Action::QUIT:
          return QuitAgent(sw_agent);
          break;
        case Action::NOOP:
          break;
        default:
          std::cerr << "Unknown action code: " << sw_action->GetCode() << std::endl;
          return false;
        }

      return true;
    }

    void Environment::CalculatePerformance(ai::Agent::Agent *agent_in)
    {
      ai::Scavenger::Agent *agent = dynamic_cast<ai::Scavenger::Agent *>(agent_in);
      /* The performance here is the total of the value of all items deposited at the base. */
      agent->SetPerformance(0);
      auto bit = bases.find(agent->GetBase());
      if(bit != bases.end() && bit->second)
        {
          agent->AddPerformance((int)bit->second->GetHopperValue(skip_object_count, max_object_count));
        }
      else
        {
          DBGP_E(LOG_STREAM(std::cerr) << "No base found for agent's base_id: " << agent->GetBase() << std::endl);
        }
      return;
    }

    ai::Agent::Percept *Environment::GetPercept(ai::Agent::Agent *agent_in)
    {
      ai::Scavenger::Agent *agent = dynamic_cast<ai::Scavenger::Agent *>(agent_in);
      ai::Agent::Percept *percept = ai::Agent::Environment::GetPercept(agent);
      /*
       * Environment specific percepts go here
       */
      for(auto bit = bases.begin(); bit != bases.end(); bit++)
        {
          ai::Agent::Percept *p = bit->second->GetPercept(agent->GetLocation());
          percept->Join(p);
          delete p;
        }

      if(fully_observable)
        {
          ai::Scavenger::Base  *base = bases[agent->GetBase()];
          Location b_location = cells_by_id[base->GetCell()]->GetLocation();
          double x = b_location.GetX();
          double y = b_location.GetY();
          double z = b_location.GetElevation();

          std::map<Location, Cell *>::const_iterator it;
          for(it = cells.begin(); it != cells.end(); it++)
            {
              char key_str[256];
              char value_str[256];
              sprintf(key_str, "CELL_%d", it->second->GetId());

              sprintf(value_str, "%f,%f,%f,%s,%s,%s,%s",
                      it->second->GetLocation().GetX()-x,
                      it->second->GetLocation().GetY()-y,
                      it->second->GetLocation().GetElevation()-z,
                      it->second->GetInterface(Location::NORTH).GetTitle().c_str(),
                      it->second->GetInterface(Location::SOUTH).GetTitle().c_str(),
                      it->second->GetInterface(Location::EAST).GetTitle().c_str(),
                      it->second->GetInterface(Location::WEST).GetTitle().c_str());
              ai::Agent::PerceptAtom pa(key_str, value_str);
              percept->JoinAtom(pa);
            }
          {
            char value_str[256];
            std::sprintf(value_str,
                         "%f,%f,%f",
                         cells_by_id[goal_cell_id]->GetLocation().GetX()-x,
                         cells_by_id[goal_cell_id]->GetLocation().GetY()-y,
                         cells_by_id[goal_cell_id]->GetLocation().GetElevation()-z);
            ai::Agent::PerceptAtom pa("GOAL_LOC", value_str);
            percept->JoinAtom(pa);
          }
        }

      return percept;
    }

    void Environment::Step()
    {
      /* randomize order of agents */
      size_t i;
      for(i = 0; i < agents_order.size(); i++)
        {
          size_t j = (size_t)(this->random_number.Rand() * agents_order.size());
          j %= agents_order.size();
          unsigned int t = agents_order[i];
          agents_order[i] = agents_order[j];
          agents_order[j] = t;
        }

      for(i = 0; i < agents_order.size(); i++)
        {
          if(!agents[agents_order[i]]->IsAlive())
            {
              continue;
            }
          Agent  *sw_agent  = dynamic_cast<Agent *>(agents[agents_order[i]]);

          /* build percepts */
          ai::Agent::Percept *percept = GetPercept(sw_agent);

          /* ask for action */
          ai::Agent::Action  *action  = sw_agent->Program(percept);
          delete percept;

          /* apply the action */
          if(action)
            {
              if(!ApplyAction(sw_agent, action))
                {
                  DBGP_E(LOG_STREAM(std::cerr) << "Error with ApplyAction" << std::endl);
                }
              delete action;
            }

          for(unsigned int j = 0; j < agents_order.size(); j++)
            {
              CalculatePerformance(agents[agents_order[j]]);
            }

          UpdateDisplays();
        }

      //UpdateDisplays(); // Extra Update Display call...may or may not need
    }

    void Environment::Run(const int n_steps)
    {
      size_t i;
      for(i = 0; i < agents_order.size(); i++)
        {
          agents[agents_order[i]]->SetPerformance(0);
        }
      UpdateDisplays();
      if(delay)
        {
          sleep(delay);
        }
      for(time_step = 0; time_step < n_steps; time_step++)
        {
          unsigned int alive_agents = 0;
          for(i = 0; i < agents_order.size(); i++)
            {
              if(agents[agents_order[i]]->IsAlive())
                {
                  alive_agents ++;
                }
            }
          if(alive_agents > 0)
            {
              Step();
              if(delay)
                {
                  sleep(delay);
                }
            }
        }
    }

    void Environment::AddAgent(ai::Agent::Agent *agent, ai::Agent::Location *location)
    {
      Agent  *sw_agent  = dynamic_cast<Agent *>(agent);
      bool found_base = false;
      for(auto bit = bases.begin(); bit != bases.end(); bit++)
        {
          if(bit->second->GetAgent() == 0)
            {
              Location *l_ptr = new Location();
              (*l_ptr) = cells_by_id[bit->second->GetCell()]->GetLocation();
              location = l_ptr;
              Location *bl_ptr = new Location(*l_ptr);
              ai::Agent::Environment::AddAgent(agent, location);
              bit->second->SetAgent(sw_agent->GetIdNum());
              sw_agent->SetBase(bit->second->GetIdNum());
              sw_agent->SetBaseLocation(bl_ptr);
              int index = (int) agents.size() - 1;
              sw_agent->SetIndex(index);
              found_base = true;
              break;
            }
        }
      if(!found_base)
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Unable to find base for agent." << std::endl);
        }
      sw_agent->Initialize(); // now that it knows about the environment
    }

    ai::Agent::Location *Environment::DefaultLocation() const
    {
      return 0;
    }

    bool Environment::GetUpdateMessage(ai::Agent::Message &omsg)
    {
      if(!ai::Agent::Environment::GetUpdateMessage(omsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to get parent class data." << std::endl);
          return false;
        }

      ADD_TO_MSG_IF_CHANGED("WORLD_FILENAME", world_filename, omsg, mLastMessage);
      ADD_MAP_TO_POINTER_TO_MSG_IF_CHANGED("BASES", bases, omsg, mLastMessage);
      /* Don't do cells.  The cells will be passed via cells_by_id, then
       * cells will be reconstructed from them on the other side. */
      ADD_MAP_TO_POINTER_TO_MSG_IF_CHANGED("CELLS_BY_ID", cells_by_id, omsg, mLastMessage);
      //ADD_TO_MSG_IF_CHANGED("CELL_INTERFACES", cell_interfaces, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("GOAL_CELL_ID", goal_cell_id, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("FULLY_OBSERVABLE", fully_observable, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("OBJECT_LEARNING", object_learning, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("MAX_CHARGE", max_charge, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("RECHARGE_PER_TURN", recharge_per_turn, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("MAX_HIT_POINTS", max_hit_points, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("MAX_BIN_VOLUME", max_bin_volume, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("MAX_ARM_MASS", max_arm_mass, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("LIFT_DAMAGE", lift_damage, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("FALL_DAMAGE_PER_METER", fall_damage_per_meter, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("RECHARGE_DAMAGE", recharge_damage, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("RECHARGE_CHARGE", recharge_charge, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("V_CHARGE_PER_METER", v_charge_per_meter, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("H_CHARGE_PER_METER", h_charge_per_meter, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("LOOK_CHARGE", look_charge, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("PICKUP_CHARGE", pickup_charge, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("DROP_CHARGE", drop_charge, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("DESPOSIT_CHARGE", deposit_charge, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("EXAMINE_CHARGE", examine_charge, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("SKIP_OBJECT_COUNT", skip_object_count, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("MAX_OBJECT_COUNT", max_object_count, omsg, mLastMessage);

      return true;
    }

    bool Environment::UpdateFromMessage(ai::Agent::Message &imsg)
    {
      MSG_MAKE_AGENTS_EXIST(imsg);
      // FIXME: Need to make sure objects exist.
      //MSG_MAKE_OBJECTS_EXIST(imsg);

      if(!ai::Agent::Environment::UpdateFromMessage(imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to update parent class." << std::endl);
          return false;
        }

      SET_FROM_MSG_IF_EXISTS("WORLD_FILENAME", world_filename, imsg);
      SET_MAP_TO_POINTER_FROM_MSG_IF_EXISTS("BASES", bases, unsigned int, Base, imsg);
      // cells is reconstructed from cells_by_id.
      SET_MAP_TO_POINTER_FROM_MSG_IF_EXISTS("CELLS_BY_ID", cells_by_id, unsigned int, Cell, imsg);
      do
        {
          for(auto cit = cells_by_id.begin(); cit != cells_by_id.end(); cit++)
            {
              if(cit->second)
                {
                  cells[cit->second->GetLocation()] = cit->second;
                }
              else
                {
                  DBGP_MSG(LOG_STREAM(std::cerr) << "Cell Id " << cit->first << " has pointer: " << cit->second << std::endl);
                }
            }
        } while(0);
      //SET_FROM_MSG_IF_EXISTS("CELL_INTERFACES", cell_interfaces, imsg);
      SET_FROM_MSG_IF_EXISTS("GOAL_CELL_ID", goal_cell_id, imsg);
      SET_FROM_MSG_IF_EXISTS("FULLY_OBSERVABLE", fully_observable, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_LEARNING", object_learning, imsg);
      SET_FROM_MSG_IF_EXISTS("MAX_CHARGE", max_charge, imsg);
      SET_FROM_MSG_IF_EXISTS("RECHARGE_PER_TURN", recharge_per_turn, imsg);
      SET_FROM_MSG_IF_EXISTS("MAX_HIT_POINTS", max_hit_points, imsg);
      SET_FROM_MSG_IF_EXISTS("MAX_BIN_VOLUME", max_bin_volume, imsg);
      SET_FROM_MSG_IF_EXISTS("MAX_ARM_MASS", max_arm_mass, imsg);
      SET_FROM_MSG_IF_EXISTS("LIFT_DAMAGE", lift_damage, imsg);
      SET_FROM_MSG_IF_EXISTS("FALL_DAMAGE_PER_METER", fall_damage_per_meter, imsg);
      SET_FROM_MSG_IF_EXISTS("RECHARGE_DAMAGE", recharge_damage, imsg);
      SET_FROM_MSG_IF_EXISTS("RECHARGE_CHARGE", recharge_charge, imsg);
      SET_FROM_MSG_IF_EXISTS("V_CHARGE_PER_METER", v_charge_per_meter, imsg);
      SET_FROM_MSG_IF_EXISTS("H_CHARGE_PER_METER", h_charge_per_meter, imsg);
      SET_FROM_MSG_IF_EXISTS("LOOK_CHARGE", look_charge, imsg);
      SET_FROM_MSG_IF_EXISTS("PICKUP_CHARGE", pickup_charge, imsg);
      SET_FROM_MSG_IF_EXISTS("DROP_CHARGE", drop_charge, imsg);
      SET_FROM_MSG_IF_EXISTS("DESPOSIT_CHARGE", deposit_charge, imsg);
      SET_FROM_MSG_IF_EXISTS("EXAMINE_CHARGE", examine_charge, imsg);
      SET_FROM_MSG_IF_EXISTS("SKIP_OBJECT_COUNT", skip_object_count, imsg);
      SET_FROM_MSG_IF_EXISTS("MAX_OBJECT_COUNT", max_object_count, imsg);

      return true;
    }

    bool Environment::SetFullyObservable(const bool value_in)
    {
      fully_observable = value_in;
      return true;
    }

    bool Environment::SetObjectLearning(const bool value_in)
    {
      object_learning = value_in;
      return true;
    }

    bool Environment::SetMaxCharge(const double value_in)
    {
      max_charge = value_in;
      return true;
    }

    bool Environment::SetRechargePerTurn(const double value_in)
    {
      recharge_per_turn = value_in;
      return true;
    }

    bool Environment::SetMaxHitPoints(const double value_in)
    {
      max_hit_points = value_in;
      return true;
    }

    bool Environment::SetMaxBinVolume(const double value_in)
    {
      max_bin_volume = value_in;
      return true;
    }

    bool Environment::SetMaxArmMass(const double value_in)
    {
      max_arm_mass = value_in;
      return true;
    }

    bool Environment::SetLiftDamage(const double value_in)
    {
      lift_damage = value_in;
      return true;
    }

    bool Environment::SetFallDamagePerMeter(const double value_in)
    {
      fall_damage_per_meter = value_in;
      return true;
    }

    bool Environment::SetRechargeDamage(const double value_in)
    {
      recharge_damage = value_in;
      return true;
    }

    bool Environment::SetRechargeCharge(const double value_in)
    {
      recharge_charge = value_in;
      return true;
    }

    bool Environment::SetVChargePerMeter(const double value_in)
    {
      v_charge_per_meter = value_in;
      return true;
    }

    bool Environment::SetHChargePerMeter(const double value_in)
    {
      h_charge_per_meter = value_in;
      return true;
    }
    bool Environment::SetLookCharge(const double value_in)
    {
      look_charge = value_in;
      return true;
    }
    bool Environment::SetPickupCharge(const double value_in)
    {
      pickup_charge = value_in;
      return true;
    }
    bool Environment::SetDropCharge(const double value_in)
    {
      drop_charge = value_in;
      return true;
    }
    bool Environment::SetDepositCharge(const double value_in)
    {
      deposit_charge = value_in;
      return true;
    }
    bool Environment::SetExamineCharge(const double value_in)
    {
      examine_charge = value_in;
      return true;
    }
    bool Environment::SetSkipObjectCount(const unsigned int value_in)
    {
      skip_object_count = value_in;
      return true;
    }
    bool Environment::SetMaxObjectCount(const unsigned int value_in)
    {
      max_object_count = value_in;
      return true;
    }


    bool Environment::GetFullyObservable() const
    {
      return fully_observable;
    }

    bool Environment::GetObjectLearning() const
    {
      return object_learning;
    }

    double Environment::GetMaxCharge() const
    {
      return max_charge;
    }

    double Environment::GetRechargePerTurn() const
    {
      return recharge_per_turn;
    }

    double Environment::GetMaxHitPoints() const
    {
      return max_hit_points;
    }

    double Environment::GetMaxBinVolume() const
    {
      return max_bin_volume;
    }

    double Environment::GetMaxArmMass() const
    {
      return max_arm_mass;
    }

    double Environment::GetLiftDamage() const
    {
      return lift_damage;
    }

    double Environment::GetFallDamagePerMeter() const
    {
      return fall_damage_per_meter;
    }

    double Environment::GetRechargeDamage() const
    {
      return recharge_damage;
    }

    double Environment::GetRechargeCharge() const
    {
      return recharge_charge;
    }

    double Environment::GetVChargePerMeter() const
    {
      return v_charge_per_meter;
    }

    double Environment::GetHChargePerMeter() const
    {
      return h_charge_per_meter;
    }
    double Environment::GetLookCharge() const
    {
      return look_charge;
    }
    double Environment::GetPickupCharge() const
    {
      return pickup_charge;
    }
    double Environment::GetDropCharge() const
    {
      return drop_charge;
    }
    double Environment::GetDepositCharge() const
    {
      return deposit_charge;
    }
    double Environment::GetExamineCharge() const
    {
      return examine_charge;
    }
    unsigned int Environment::GetSkipObjectCount() const
    {
      return skip_object_count;
    }

    unsigned int Environment::GetMaxObjectCount() const
    {
      return max_object_count;
    }

    bool   Environment::MakeEnoughBases(int num_agents)
    {
      int tries = 0;
      while((int) bases.size() < num_agents && tries < num_agents*2)
        {
          unsigned int j = (unsigned int)(random_number.Rand() * cells_by_id.size());
          unsigned int k = 0;
          std::map<unsigned int, Cell*>::iterator it = cells_by_id.begin();
          while(k < j)
            {
              it++;
              k++;
            }
          if(it != this->cells_by_id.end())
            {
              /* Make sure this cell doesn't already contain a base */
              if(it->second->GetBases().size() == 0)
                {
                  ai::Scavenger::Location *tloc = new ai::Scavenger::Location(it->second->GetLocation());
                  Base *b = new Base(0, it->second->GetId());
                  b->SetLocation(tloc);
                  b->SetEnvironment(this);
                  bases[b->GetIdNum()] = b;
                  it->second->AddBase(b->GetIdNum());
                }
            }
        }
      return (int)this->bases.size() >= num_agents;
    }

    void Environment::TextDisplay(std::ostream &os) const
    {
      std::map<Location, Cell *>::const_iterator it;
      for(it = cells.begin(); it != cells.end(); it++)
        {
          os << it->first.GetString() << std::endl;
          os << it->second->GetString() << std::endl;
        }
    }

    bool Environment::ReadFile()
    {
      std::ifstream fin(world_filename.c_str());
      if(!fin)
        {
          std::cerr << "Unable to open Scavenger world file: " << world_filename << std::endl;
          return false;
        }

      char line[1024];

      while(!fin.eof())
        {
          fin.getline(line, 1024);
          if(!fin.eof())
            {
              if(strncmp(line, "Cell:", 5) == 0)
                {
                  Cell *c = new Cell(line);
                  cells[c->GetLocation()] = c;
                  cells_by_id[c->GetId()] = c;
                  if(goal_cell_id == (unsigned int)-1)
                    {
                      goal_cell_id = c->GetId();
                    }
                }
              else if(strncmp(line, "Interface:", 10) == 0)
                {
                  CellInterface *ci = new CellInterface(line);
                  cell_interfaces[ci->GetTitle()] = ci;
                  //std::cout << ci->GetString() << std::endl;
                }
              else if(strncmp(line, "Base:", 5) == 0)
                {
                  unsigned int cell_id;
                  Base::ParseString(line, cell_id);
                  Base *b = new Base(0, cell_id);
                  Location *tloc = new Location(cells_by_id[cell_id]->GetLocation());
                  b->SetLocation(tloc);
                  b->SetEnvironment(this);
                  bases[b->GetIdNum()] = b;
                }
              else if(strncmp(line, "Object:", 7) == 0)
                {
                  unsigned int cell_id;
                  Object *obj = new Object(line, cell_id);
                  cells_by_id[cell_id]->AddObject(obj->GetIdNum());
                  Location *loc = new Location(cells_by_id[cell_id]->GetLocation());
                  AddObject(obj, loc);
                }
              else if(strncmp(line, "Goal:", 5) == 0)
                {
                  std::sscanf(line,
                              "Goal: %d",
                              &goal_cell_id);
                }
            }
        }

      fin.close();

      /* Define interfaces */
      CellInterface tmp_interface;
      CellInterface *ci;
      std::map<Location, Cell *>::const_iterator it;
      int d;
      Cell *tmp_cell;

      for(it = cells.begin(); it != cells.end(); it++)
        {
          for(d = Location::NORTH; d <= Location::WEST; d++)
            {
              tmp_interface = it->second->GetInterface((Location::Direction)d);
              ci = cell_interfaces[tmp_interface.GetTitle()];

              if(ci)
                {
                  tmp_interface = *ci;
                }
              else
                {
                  std::cout << "Unknown interface type " << tmp_interface.GetTitle() << std::endl;
                }
              it->second->SetInterface((Location::Direction)d,
                                       tmp_interface);
            }
        }

      /* Put bases in their cells for fast lookup */
      for(auto base_it = bases.begin(); base_it != bases.end(); base_it++)
        {
          tmp_cell = cells_by_id[base_it->second->GetCell()];
          tmp_cell->AddBase(base_it->second->GetIdNum());

          ai::Scavenger::Location *tloc = new ai::Scavenger::Location(tmp_cell->GetLocation());
          base_it->second->SetLocation(tloc);
        }

      return true;
    }

    bool Environment::MoveAgent(Agent *sw_agent, int action_code)
    {
      Location *location = dynamic_cast<Location *>(sw_agent->GetLocation());
      if(!location)
        {
          if(l_debug > 1)
            {
              std::cout << "MoveAgent: bad location" << std::endl;
            }
          return false;
        }

      Cell *curr_cell    = cells[*location];

      if(!curr_cell)
        {
          if(l_debug > 1)
            {
              std::cout << "MoveAgent: bad cell" << std::endl;
            }
          return false;
        }

      Location::Direction dir;

      switch(action_code)
        {
        case Action::GO_NORTH:
          dir = Location::NORTH;
          break;
        case Action::GO_SOUTH:
          dir = Location::SOUTH;
          break;
        case Action::GO_EAST:
          dir = Location::EAST;
          break;
        case Action::GO_WEST:
          dir = Location::WEST;
          break;
        default:
          std::cerr << "MoveAgent: bad action code: " << action_code << std::endl;
          return false;
        }

      Cell          *next_cell    = cells_by_id[curr_cell->GetNeighborId(dir)];
      CellInterface  c_interface    = curr_cell->GetInterface(dir);

      if(!next_cell)
        {
          next_cell = curr_cell;
        }
      if(sw_agent->Move(*curr_cell, c_interface, *next_cell, time_step))
        {
          next_cell->SetVisited(1<<sw_agent->GetIndex());
          return true;
        }
      return false;
    }

    bool Environment::LookAgent(Agent *sw_agent, Location::Direction direction)
    {
      Location *location = dynamic_cast<Location *>(sw_agent->GetLocation());
      if(!location)
        {
          return false;
        }

      Cell *curr_cell    = cells[*location];

      if(!curr_cell)
        {
          return false;
        }

      CellInterface  c_interface    = curr_cell->GetInterface(direction);

      sw_agent->Look(c_interface.GetTitle(), time_step);

      return true;
    }

    bool Environment::RechargeAgent(Agent *sw_agent)
    {
      Location *location = dynamic_cast<Location *>(sw_agent->GetLocation());
      if(!location)
        {
          return false;
        }

      Cell *curr_cell    = cells[*location];

      if(!curr_cell)
        {
          return false;
        }

      std::map<unsigned int, unsigned int> &b = curr_cell->GetBases();
      auto bit = b.find(sw_agent->GetBase());
      bool base_here = bit != b.end();

      if(base_here)
        {
          sw_agent->Recharge(time_step);
        }
      else if(b.size() > 0)
        { // tried to recharge at someone else's base
          sw_agent->TakeDamage(GetRechargeDamage());
          sw_agent->DrainCharge(GetRechargeCharge());
        }
      else
        { // tried to recharge at no base
          sw_agent->DrainCharge(GetRechargeCharge());
        }

      return true;
    }

    bool Environment::PickupObject(Agent *sw_agent, const std::string &object_id_in)
    {
      Location *location = dynamic_cast<Location *>(sw_agent->GetLocation());
      if(!location)
        {
          return false;
        }

      Cell *curr_cell    = cells[*location];
      if(!curr_cell)
        {
          return false;
        }

      Object *obj = dynamic_cast<Object *>(objects[ai::Agent::Object::GetIdNum(object_id_in)]);

      /* Pickup catches NULL objects, removes charge and returns false */
      if(sw_agent->Pickup(obj, time_step))
        {
          curr_cell->RemoveObject(obj->GetIdNum());
          obj->SetLocation(0); // now in the bin
        }

      return true;
    }

    bool Environment::DropObject(Agent *sw_agent, const std::string &object_id_in)
    {
      Location *location = dynamic_cast<Location *>(sw_agent->GetLocation());
      if(!location)
        {
          return false;
        }

      Cell *curr_cell    = cells[*location];
      if(!curr_cell)
        {
          return false;
        }

      Object *obj = dynamic_cast<Object *>(objects[ai::Agent::Object::GetIdNum(object_id_in)]);

      if(obj)
        {
          if(sw_agent->Drop(obj, time_step))
            {
              curr_cell->AddObject(obj->GetIdNum());
              Location * l = new Location(*location);
              obj->SetLocation(l);
            }
        }

      return true;
    }

    bool Environment::DepositObject(Agent *sw_agent, const std::string &object_id_in)
    {
      Location *location = dynamic_cast<Location *>(sw_agent->GetLocation());
      if(!location)
        {
          return false;
        }

      Cell *curr_cell    = cells[*location];
      if(!curr_cell)
        {
          return false;
        }

      std::map<unsigned int, unsigned int> &b = curr_cell->GetBases();
      auto bit = b.find(sw_agent->GetBase());
      bool base_here = bit != b.end();

      if(!base_here)
        {
          return false;
        }

      Object *obj = dynamic_cast<Object *>(objects[ai::Agent::Object::GetIdNum(object_id_in)]);

      if(obj)
        {
          if(sw_agent->Deposit(obj, time_step))
            {
              bases[sw_agent->GetBase()]->AddObject(obj);
              obj->SetLocation(0); // now in the base
            }
        }

      return true;
    }

    bool Environment::ExamineObject(Agent *sw_agent, const std::string &object_id_in)
    {
      Location *location = dynamic_cast<Location *>(sw_agent->GetLocation());
      if(!location)
        {
          return false;
        }

      Cell *curr_cell    = cells[*location];
      if(!curr_cell)
        {
          return false;
        }

      Object *obj = dynamic_cast<Object *>(objects[ai::Agent::Object::GetIdNum(object_id_in)]);

      if(obj)
        {
          sw_agent->Examine(obj->GetExamineString(), time_step);
        }

      return true;
    }

    bool Environment::QuitAgent(Agent *sw_agent)
    {
      sw_agent->Quit(time_step);

      return true;
    }

    void Environment::check_cells(const std::string &msg)
    {
      std::map<Location, Cell *>::iterator it;
      for(it = cells.begin(); it != cells.end(); it++)
        {
          if(it->second == 0)
            {
              std::cerr << msg << " bad pointer" << std::endl;
              continue;
            }
        }
    }

  }
}
