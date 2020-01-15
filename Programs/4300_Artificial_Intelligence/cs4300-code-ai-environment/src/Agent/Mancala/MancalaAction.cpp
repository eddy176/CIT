#include <ai_mancala.h>
#include <cstdio>

namespace ai
{
  namespace Mancala
  {
    bool Action::TextDisplay(std::ostream & os) const
    {
      std::string str = "";

      switch(GetCode())
        {
        case MOVE:
          str = "Move ";
          {
            str += move.ToString();
          }
          break;
        case QUIT:
          str = "Quit";
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
        case MOVE:
          ADD_VECTOR_TO_MSG("MOVEBINS", move.bins, omsg);
          ADD_VECTOR_TO_MSG("MOVECOUNTS", move.counts, omsg);
          break;
        case QUIT:
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
        case MOVE:
          SET_VECTOR_FROM_MSG("MOVEBINS", move.bins, imsg);
          SET_VECTOR_FROM_MSG("MOVECOUNTS", move.counts, imsg);
          break;
        case QUIT:
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

    bool Action::SetMove(const MoveData &move_in)
    {
      move = move_in;
      return true;
    }

    const MoveData &Action::GetMove() const
    {
      return move;
    }

  }
}
