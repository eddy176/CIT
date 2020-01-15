#include <ai_ultimatetictactoe.h>
#include <cstdio>

namespace ai
{
  namespace UltimateTicTacToe
  {
    bool Action::TextDisplay(std::ostream & os) const
    {
      std::string str = "";

      switch(GetCode())
        {
        case MOVE:
          str = "Move ";
          {
            char c_str[64];
            std::sprintf(c_str, "%2d,%2d:%2d,%2d",
                         move.board_x, move.board_y, move.pos_x, move.pos_y);
            str += c_str;
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
          ADD_TO_MSG("MOVE", move.board_x << " " << move.board_y << " " << move.pos_x << " " << move.pos_y, omsg);
          DBGP_MSG(LOG_STREAM(std::cerr) << "Move: " << move.board_x << "," << move.board_y << ":" << move.pos_x << "," << move.pos_y << std::endl);
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
          SET_FROM_MSG("MOVE", move.board_x >> move.board_y >> move.pos_x >> move.pos_y, imsg);
          DBGP_MSG(LOG_STREAM(std::cerr) << "Move: " << move.board_x << "," << move.board_y << ":" << move.pos_x << "," << move.pos_y << std::endl);
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
