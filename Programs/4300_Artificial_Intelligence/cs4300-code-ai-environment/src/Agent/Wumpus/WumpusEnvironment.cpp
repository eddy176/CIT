#include <typeinfo>
#include <ai_wumpus.h>
#include <sstream>

namespace ai
{
  namespace Wumpus
  {
    Environment::Environment()
    {
    }

    Environment::Environment(const ai::Agent::RandomNumber &rand_in,
                             int width_in, int height_in, double pit_probability_in, 
                             int nirvana_in, int drwho_in,
                             std::vector<ai::Agent::Socket *> *displays_in)
      : ai::XY::Environment(rand_in, width_in, height_in, displays_in)
    {
      pit_probability = pit_probability_in;
      nirvana = nirvana_in;
      drwho = drwho_in;
      /* tracking data */
      visited.resize(width*height);

      /* Wumpus */
      int i;
      int wumpus_x;
      int wumpus_y;
      // Rand() is up to but not including 1.
      i = 1 + (int) (random_number.Rand() * ((width * height)-1));
      if(i < 1) { i = 1; }
      if(i >= width*height) { i = width*height-1; }
      wumpus_x = i % width;
      wumpus_y = i / width;

      WumpusObject      *w     = new WumpusObject;
      ai::XY::Location  *w_loc = new ai::XY::Location;
      w_loc->Set(wumpus_x, wumpus_y);
      this->AddObject(w, w_loc);

      /* Dr. Who */
      if(drwho)
        {
          int i;
          int tardis_x;
          int tardis_y;
          i = 1 + (int) (random_number.Rand() * ((width * height) - 1));
          if(i < 1) { i = 1; }
          if(i >= width*height) { i = width*height-1; }
          tardis_x = i % width;
          tardis_y = i / width;

          TardisObject      *t     = new TardisObject;
          ai::XY::Location  *t_loc = new ai::XY::Location;
          t_loc->Set(tardis_x, tardis_y);
          this->AddObject(t, t_loc);
        }

      /* Pits */
      int x,y;
      for(x = 0; x < width; x++)
        {
          for(y = 0; y < height; y++)
            {
              if(x == 0 && y == 0)
                {
                  visited[x+y*width] = true;
                  continue;
                }
              visited[x+y*width] = false;
              if(wumpus_x == x && wumpus_y == y)
                {
                  continue;
                }
              if(random_number.Rand() < pit_probability)
                {
                  PitObject         *p     = new PitObject;
                  ai::XY::Location  *p_loc = new ai::XY::Location;
                  p_loc->Set(x,y);
                  this->AddObject(p, p_loc);
                }
            }
        }
      /* Gold */
      i = 1 + (int) (random_number.Rand() * ((width * height) - 1));
      if(i < 1) { i = 1; }
      if(i >= width*height) { i = width*height-1; }
      x = i % width;
      y = i / width;

      GoldObject        *g     = new GoldObject;
      ai::XY::Location  *g_loc = new ai::XY::Location;
      g_loc->Set(x,y);
      this->AddObject(g, g_loc);
    }

    Environment::~Environment()
    {
    }

    bool Environment::ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action)
    {
      if(!agent->IsAlive())
        {
          return false;
        }

      Action *wm_action = dynamic_cast<Action *>(action);
      Agent  *wm_agent  = dynamic_cast<Agent *>(agent);
      switch(wm_action->GetCode())
        {
        case Action::GRAB:
          if(GrabGold(dynamic_cast<ai::XY::Location *>(agent->GetLocation())))
            {
              wm_agent->Grab();
              agent->AddPerformance(1000); // +1000 for gold
            }
          agent->AddPerformance(-1); // -1 for action
          wm_agent->UnYell();
          break;
        case Action::SHOOT:
          if(wm_agent->ArrowCount() > 0)
            {
              ShootArrow(dynamic_cast<ai::XY::Location *>(agent->GetLocation()),
                         wm_agent->GetDirection());
              wm_agent->Shoot();
            }
          agent->AddPerformance(-10); // - 10 for shoot arrow
          wm_agent->UnYell();
          break;
        case Action::TURN_RIGHT:
          wm_agent->TurnRight();
          agent->AddPerformance(-1); // - 1 for action
          wm_agent->UnYell();
          break;
        case Action::TURN_LEFT:
          wm_agent->TurnLeft();
          agent->AddPerformance(-1); // - 1 for action
          wm_agent->UnYell();
          break;
        case Action::FORWARD:
          wm_agent->Forward(width, height);
          Visit((dynamic_cast<ai::XY::Location *>(agent->GetLocation()))->GetX(),
                (dynamic_cast<ai::XY::Location *>(agent->GetLocation()))->GetY());
          agent->AddPerformance(-1); // - 1 for action
          if(InPit(wm_agent) || EatenByWumpus(wm_agent))
            {
              wm_agent->Kill();
              if(!nirvana || InPit(wm_agent))
                {
                  wm_agent->AddPerformance(-1000); // - 1000 for death
                }
              else // nirvana && EatenByWumpus
                {
                  if(wm_agent->GetYellLast())
                    {
                      wm_agent->AddPerformance(10000); //  10000 for being eaten
                    }
                }
            }
          wm_agent->UnYell();
          break;
        case Action::QUIT:
          wm_agent->Kill(); // no point penalty, just quit
          wm_agent->UnYell();
          break;
        case Action::YELL:
          wm_agent->AddPerformance(-1000);
          wm_agent->Yell();
          break;
        case Action::NOOP:
          wm_agent->UnYell();
          break;
        default:
          wm_agent->UnYell();
          return false;
        }
      return true;
    }

    void Environment::CalculatePerformance(ai::Agent::Agent *agent)
    { // no change  Performace assigned by action.
    }

    // eliminate duplicate percepts.  no fair telling if there are 2 breezes.
    ai::Agent::Percept *Environment::GetPercept(ai::Agent::Agent *agent)
    {
      ai::Agent::Percept *percept = ai::XY::Environment::GetPercept(agent);
      ai::Agent::Percept *p2      = new ai::Agent::Percept;

      std::stringstream ss;
      ss << pit_probability;
      ai::Agent::PerceptAtom p_PP("PIT-PROBABILITY", ss.str());
      percept->JoinAtom(p_PP);
      
      unsigned int i;
      for(i = 0; i < percept->NumAtom(); i++)
        {
          ai::Agent::PerceptAtom a = percept->GetAtom(i);
          if(p2->GetAtom(a.GetName()).GetName() != a.GetName())
            {
              p2->JoinAtom(a);
            }
        }

      delete percept;
      return p2;
    }


    bool Environment::GrabGold(ai::XY::Location *xy_loc)
    {
      for(auto oit = objects.begin(); oit != objects.end(); oit++)
        {
          ai::XY::Location *loc = dynamic_cast<ai::XY::Location *>(oit->second->GetLocation());

          if((loc->GetX() == xy_loc->GetX()) &&
             (loc->GetY() == xy_loc->GetY()) &&
             (dynamic_cast<GoldObject*>(oit->second) != 0))
            {
              delete oit->second;
              objects.erase(oit);
              return true;
            }
        }
      return false;
    }

    void Environment::ShootArrow(ai::XY::Location *xy_loc, int direction)
    {
      for(auto oit = objects.begin(); oit != objects.end(); oit++)
        {
          ai::XY::Location *loc = dynamic_cast<ai::XY::Location *>(oit->second->GetLocation());
          WumpusObject *obj = dynamic_cast<WumpusObject *>(oit->second);
          if(obj)
            {
              switch(direction)
                {
                case 0:
                  if((xy_loc->GetY() == loc->GetY()) &&
                     (xy_loc->GetX() < loc->GetX()))
                    {
                      obj->Kill();
                    }
                  break;
                case 180:
                  if((xy_loc->GetY() == loc->GetY()) &&
                     (xy_loc->GetX() > loc->GetX()))
                    {
                      obj->Kill();
                    }
                  break;
                case 90:
                  if((xy_loc->GetX() == loc->GetX()) &&
                     (xy_loc->GetY() < loc->GetY()))
                    {
                      obj->Kill();
                    }
                  break;
                case 270:
                  if((xy_loc->GetX() == loc->GetX()) &&
                     (xy_loc->GetY() > loc->GetY()))
                    {
                      obj->Kill();
                    }
                  break;
                }
            }
        }
    }

    void Environment::Visit(int x, int y)
    {
      visited[x+y*width] = true;
    }
    bool Environment::IsVisited(int x, int y) const
    {
      return visited[x+y*width];
    }

    void Environment::AddAgent(ai::Agent::Agent *agent_in)
    {
      ai::XY::Location   *location  = new ai::XY::Location;
      location->Set(0,0);
      ai::Agent::Environment::AddAgent(agent_in, location);
    }

    bool Environment::GetUpdateMessage(ai::Agent::Message &omsg)
    {
      if(!ai::XY::Environment::GetUpdateMessage(omsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to get parent class data." << std::endl);
          return false;
        }

      /*
       * Wumpus::Environment data
       */
      ADD_TO_MSG_IF_CHANGED("VISITED_SIZE", visited.size(), omsg, mLastMessage);
      size_t i;
      for(i = 0; i < visited.size(); i++)
        {
          ADD_TO_MSG_IF_CHANGED("VISITED " << i, visited[i], omsg, mLastMessage);
        }
      ADD_TO_MSG_IF_CHANGED("NIRVANA", nirvana, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("DRWHO", drwho, omsg, mLastMessage);

      return true;
    }

    bool Environment::UpdateFromMessage(ai::Agent::Message &imsg)
    {
      MSG_MAKE_AGENTS_EXIST(imsg);

      /* MSG_MAKE_OBJECTS_EXIST(imsg); // this needs to be hacked to be sure that correct types are created
       * Following code replaces the macro that only supports one object type.
       */
      do
        {
          unsigned int id;
          size_t i, count = 0;
          std::string object_type;
          ai::Agent::Object *obj;
          SET_FROM_MSG("OBJECT_SEQ_COUNT", count, imsg);
          for(i = 0; i < count; i++)
            {
              SET_FROM_MSG("OBJECT_SEQ_ID " << i, id, imsg);
              SET_FROM_MSG("OBJECT_WUMPUSOBJECT_TYPE " << id, object_type, imsg);
              if(object_type == "GOLD")
                {
                  obj = dynamic_cast<GoldObject*>(objects[id]);
                  if(!obj)
                    {
                      objects[id] = new GoldObject();
                    }
                }
              else if(object_type == "PIT")
                {
                  obj = dynamic_cast<PitObject*>(objects[id]);
                  if(!obj)
                    {
                      objects[id] = new PitObject();
                    }
                }
              else if(object_type == "WUMPUS")
                {
                  obj = dynamic_cast<WumpusObject*>(objects[id]);
                  if(!obj)
                    {
                      objects[id] = new WumpusObject();
                    }
                }
              else if(object_type == "TARDIS")
                {
                  obj = dynamic_cast<TardisObject*>(objects[id]);
                  if(!obj)
                    {
                      objects[id] = new TardisObject();
                    }
                }
              else
                {
                  DBGP_E(LOG_STREAM(std::cerr) << "Bad ai::Wumpus:: Object type: " << object_type << "." << std::endl);
                  return false;
                }
            }
        } while(0);

      if(!ai::XY::Environment::UpdateFromMessage(imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to update parent class." << std::endl);
          return false;
        }

      size_t count = 0;
      SET_FROM_MSG_IF_EXISTS("VISITED_SIZE", count, imsg);
      if(count > 0)
        {
          visited.resize(count);
        }
      size_t i;
      for(i = 0; i < visited.size(); i++)
        {
          SET_FROM_MSG_IF_EXISTS("VISITED " << i, visited[i], imsg);
        }
      SET_FROM_MSG_IF_EXISTS("NIRVANA", nirvana, imsg);
      SET_FROM_MSG_IF_EXISTS("DRWHO", drwho, imsg);

      return true;
    }

    bool Environment::InPit(ai::Agent::Agent *agent_in)
    {
      ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(agent_in->GetLocation());

      std::vector<ai::Agent::Object *>::iterator i;
      for(auto oit = objects.begin(); oit != objects.end(); oit++)
        {
          ai::XY::Location *loc = dynamic_cast<ai::XY::Location *>(oit->second->GetLocation());

          if((loc->GetX() == xy_loc->GetX()) &&
             (loc->GetY() == xy_loc->GetY()) &&
             (dynamic_cast<PitObject*>(oit->second) != 0))
            {
              return true;
            }
        }
      return false;
    }

    bool Environment::EatenByWumpus(ai::Agent::Agent *agent_in)
    {
      ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(agent_in->GetLocation());

      for(auto oit = objects.begin(); oit != objects.end(); oit++)
        {
          WumpusObject *obj = dynamic_cast<WumpusObject *>(oit->second);
          if(!obj) { continue; }
          ai::XY::Location *loc = dynamic_cast<ai::XY::Location *>(obj->GetLocation());

          if((loc->GetX() == xy_loc->GetX()) &&
             (loc->GetY() == xy_loc->GetY()))
            {
              if(obj->IsAlive())
                {
                  return true;
                }
            }
        }
      return false;
    }


  }
}

