#include <ai_wumpus.h>

namespace ai
{
  namespace Wumpus
  {
    bool Action::TextDisplay(std::ostream & os) const
    {
      std::string str = "";

      switch(GetCode())
        {
        case GRAB:
          str = "Grab";
          break;
        case SHOOT:
          str = "Shoot";
          break;
        case TURN_RIGHT:
          str = "Turn Right";
          break;
        case TURN_LEFT:
          str = "Turn Left";
          break;
        case FORWARD:
          str = "Forward";
          break;
        case QUIT:
          str = "Quit";
          break;
        case YELL:
          str = "Yell";
          break;
        case NOOP:
          str = "NoOp";
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }
      os << str;
      return true;
    }

    bool Action::ToMessage(ai::Agent::Message &omsg) const
    {
      if(!omsg.SetName(ai::Agent::MESSAGE_ACTION_NAME))
        {
          return false;
        }
      ADD_TO_MSG("CODE", action_code, omsg);
      switch(action_code)
        {
        case GRAB:
        case SHOOT:
        case TURN_RIGHT:
        case TURN_LEFT:
        case FORWARD:
        case QUIT:
        case YELL:
        case NOOP:
          // OK, no other data
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }

      DBGP_MSG(LOG_STREAM(std::cerr) << "Message: " << omsg << std::endl);
      return true;
    }

    bool Action::FromMessage(const ai::Agent::Message &imsg)
    {
      if(imsg.GetName() != ai::Agent::MESSAGE_ACTION_NAME)
        {
          return false;
        }
      SET_FROM_MSG("CODE", action_code, imsg);
      switch(action_code)
        {
        case GRAB:
        case SHOOT:
        case TURN_RIGHT:
        case TURN_LEFT:
        case FORWARD:
        case QUIT:
        case YELL:
        case NOOP:
          // OK, no other data
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }
      return true;
    }
    bool Action::AddToMessageIfChanged(const std::string &keyprefix, ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      DBGP_E(LOG_STREAM(std::cerr) << "Implement this method to remove this error" << std::endl);
      {
        int *x = 0;
        *x = 1;
      }
      return false;
    }
    
    bool Action::SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg)
    {
      DBGP_E(LOG_STREAM(std::cerr) << "Implement this method to remove this error" << std::endl);
      {
        int *x = 0;
        *x = 1;
      }
      return false;
    }


  }
}
