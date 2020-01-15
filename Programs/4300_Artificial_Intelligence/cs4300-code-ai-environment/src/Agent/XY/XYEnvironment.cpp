#include <ai_xy.h>
#include <sstream>

namespace ai
{
  namespace XY
  {
    Environment::Environment()
      : width(1), height(1)
    {
    }

    Environment::Environment(const ai::Agent::RandomNumber &rand_in,
                             int width_in, int height_in,
                             std::vector<ai::Agent::Socket *> *displays_in)
      : ai::Agent::Environment(rand_in, displays_in), width(width_in), height(height_in)
    {
    }

    Environment::~Environment()
    {
    }

    bool Environment::ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action)
    {
      Action *xy_action = dynamic_cast<Action *>(action);
      Agent  *xy_agent  = dynamic_cast<Agent *>(agent);
      switch(xy_action->GetCode())
        {
        case Action::TURN_RIGHT:
          xy_agent->TurnRight();
          break;
        case Action::TURN_LEFT:
          xy_agent->TurnLeft();
          break;
        case Action::FORWARD:
          xy_agent->Forward(width, height);
          break;
        default:
          return false;
        }
      return true;
    }

    void Environment::CalculatePerformance(ai::Agent::Agent *agent)
    {
    }

    ai::Agent::Percept *Environment::GetPercept(ai::Agent::Agent *agent)
    {
      ai::Agent::Percept *percept = ai::Agent::Environment::GetPercept(agent);
      std::stringstream ss;
      ss << width;
      ai::Agent::PerceptAtom p_WIDTH("WIDTH", ss.str());
      ss.clear();
      ss.str("");
      ss << height;
      ai::Agent::PerceptAtom p_HEIGHT("HEIGHT", ss.str());
      percept->JoinAtom(p_WIDTH);
      percept->JoinAtom(p_HEIGHT);
      return percept;
    }

    ai::Agent::Location *Environment::DefaultLocation() const
    {
      Location *xy_loc = new Location();
      xy_loc->Set(1, 1);
      return xy_loc;
    }

    bool Environment::GetUpdateMessage(ai::Agent::Message &omsg)
    {
      if(!ai::Agent::Environment::GetUpdateMessage(omsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to get parent class data." << std::endl);
          return false;
        }

      /*
       * XY Environment information
       */
      ADD_TO_MSG_IF_CHANGED("XYWIDTH", width, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("XYHEIGHT", height, omsg, mLastMessage);

      return true;
    }

    bool Environment::UpdateFromMessage(ai::Agent::Message &imsg)
    {
      MSG_MAKE_AGENTS_EXIST(imsg);
      if(!ai::Agent::Environment::UpdateFromMessage(imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to update parent class." << std::endl);
          return false;
        }

      /*
       * XY Environment information
       */
      SET_FROM_MSG_IF_EXISTS("XYWIDTH", width, imsg);
      SET_FROM_MSG_IF_EXISTS("XYHEIGHT", height, imsg);

      return true;
    }

    int Environment::GetWidth() const
    {
      return width;
    }
    int Environment::GetHeight() const
    {
      return height;
    }

  }
}
