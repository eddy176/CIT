#include <ai_jetan.h>
#include <cstdio>
#include <sstream>

namespace ai
{
  namespace Jetan
  {
    bool Action::TextDisplay(std::ostream & os) const
    {
      std::stringstream ss;

      switch( GetCode( ) )
        {
        case MOVE:
          ss << "Move ";
          ss << move;
          break;
        case QUIT:
          ss << "Quit";
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }
      os << ss.str( );
      return true;
    }

    bool Action::ToMessage( ai::Agent::Message &omsg ) const
    {
      if(!omsg.SetName(ai::Agent::MESSAGE_ACTION_NAME))
        {
          return false;
        }
      ADD_TO_MSG("CODE", action_code, omsg);
      switch(action_code)
        {
        case MOVE:
          ADD_TO_MSG("MOVE", (int)move.piece.x << " " << (int)move.piece.y << " " << (int)move.offset.dx << " " << (int)move.offset.dy, omsg);
          DBGP_MSG(LOG_STREAM(std::cerr) << "Move: " << (int)move.piece.x << " " << (int)move.piece.y << " " << (int)move.offset.dx << " " << (int)move.offset.dy << std::endl);
          break;
        case QUIT:
          // OK, no other data
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }

      DBGP_MSG(LOG_STREAM(std::cerr) << "Message: " << std::endl << omsg << std::endl);
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
          {
            int x=-100, y=-100, dx=-100, dy=-100;
            SET_FROM_MSG("MOVE", x >> y >> dx >> dy, imsg);
            move.piece.x = x;
            move.piece.y = y;
            move.offset.dx = dx;
            move.offset.dy = dy;
            DBGP_MSG(LOG_STREAM(std::cerr) << "Move: " << (int)move.piece.x << " " << (int)move.piece.y << " " << (int)move.offset.dx << " " << (int)move.offset.dy << std::endl);
          }
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
