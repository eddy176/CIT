#include <ai_scavenger.h>

namespace ai
{
  namespace Scavenger
  {
    Action::Action (  )
    {
      SetCode(NOOP);
    }

    Action::~Action()
    {
    }

    bool Action::TextDisplay(std::ostream &os) const
    {
      std::string str = "";

      switch(GetCode())
        {
        case GO_NORTH:
          str = "GO_NORTH";
          break;
        case GO_SOUTH:
          str = "GO_SOUTH";
          break;
        case GO_EAST:
          str = "GO_EAST";
          break;
        case GO_WEST:
          str = "GO_WEST";
          break;
        case LOOK:
          str = "LOOK-";
          {
            switch(direction)
              {
              case Location::NORTH:
                str += "NORTH";
                break;
              case Location::SOUTH:
                str += "SOUTH";
                break;
              case Location::EAST:
                str += "EAST";
                break;
              case Location::WEST:
                str += "WEST";
                break;
              default:
                str += "UNKNOWN";
                DBGP_E(LOG_STREAM(std::cerr) << "Bad direction: " << direction << std::endl);
                break;
              }
          }
          break;
        case RECHARGE:
          str = "RECHARGE";
          break;
        case PICKUP:
          str = "PICKUP";
          break;
        case DROP:
          str = "DROP";
          break;
        case DEPOSIT:
          str = "DEPOSIT";
          break;
        case EXAMINE:
          str = "EXAMINE";
          break;
        case QUIT:
          str = "QUIT";
          break;
        case NOOP:
          str = "NOOP";
          break;
        default:
          str = "UNKNOWN";
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          break;
        }

      os << str << " " << object_id;
      return true;
    }

    bool Action::ToMessage(ai::Agent::Message &omsg) const
    {
      if(!omsg.SetName(ai::Agent::MESSAGE_ACTION_NAME))
        {
          return false;
        }
      ADD_TO_MSG("SCAVACTION_CODE", action_code, omsg);
      switch(action_code)
        {
        case GO_NORTH:
        case GO_SOUTH:
        case GO_EAST:
        case GO_WEST:
          // OK, no other data
          break;
        case LOOK:
          ADD_TO_MSG("SCAVACTION_DIRECTION", direction, omsg);
          break;
        case RECHARGE:
          // OK, no other data
          break;
        case PICKUP:
        case DROP:
        case DEPOSIT:
        case EXAMINE:
          ADD_TO_MSG("SCAVACTION_OBJECT_ID", object_id, omsg);
          break;
        case QUIT:
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
      SET_FROM_MSG("SCAVACTION_CODE", action_code, imsg);
      switch(action_code)
        {
        case GO_NORTH:
        case GO_SOUTH:
        case GO_EAST:
        case GO_WEST:
          // OK, no other data
          break;
        case LOOK:
          {
            int dtmp = 0;
            SET_FROM_MSG("SCAVACTION_DIRECTION", dtmp, imsg);
            direction = static_cast<Location::Direction>(dtmp);
          }
          break;
        case RECHARGE:
          // OK, no other data
          break;
        case PICKUP:
        case DROP:
        case DEPOSIT:
        case EXAMINE:
          SET_FROM_MSG("SCAVACTION_OBJECT_ID", object_id, imsg);
          break;
        case QUIT:
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
      ADD_TO_MSG_IF_CHANGED(keyprefix << "SCAVACTION_CODE", action_code, omsg, old_msg);
      switch(action_code)
        {
        case GO_NORTH:
        case GO_SOUTH:
        case GO_EAST:
        case GO_WEST:
          // OK, no other data
          break;
        case LOOK:
          ADD_TO_MSG_IF_CHANGED(keyprefix << "SCAVACTION_DIRECTION", direction, omsg, old_msg);
          break;
        case RECHARGE:
          // OK, no other data
          break;
        case PICKUP:
        case DROP:
        case DEPOSIT:
        case EXAMINE:
          ADD_TO_MSG_IF_CHANGED(keyprefix << "SCAVACTION_OBJECT_ID", object_id, omsg, old_msg);
          break;
        case QUIT:
        case NOOP:
          // OK, no other data
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }
      return true;
    }
    
    bool Action::SetFromMessageIfExists(const std::string &keyprefix, ai::Agent::Message &imsg)
    {
      SET_FROM_MSG_IF_EXISTS(keyprefix << "SCAVACTION_CODE", action_code, imsg);
      switch(action_code)
        {
        case GO_NORTH:
        case GO_SOUTH:
        case GO_EAST:
        case GO_WEST:
          // OK, no other data
          break;
        case LOOK:
          {
            int dtmp = -1;
            SET_FROM_MSG_IF_EXISTS(keyprefix << "SCAVACTION_DIRECTION", dtmp, imsg);
            if(dtmp >= 0)
              {
                direction = static_cast<Location::Direction>(dtmp);
                DBGP_MSG(LOG_STREAM(std::cerr) << "Direction: " << direction << std::endl);
              }
          }
          break;
        case RECHARGE:
          // OK, no other data
          break;
        case PICKUP:
        case DROP:
        case DEPOSIT:
        case EXAMINE:
          SET_FROM_MSG_IF_EXISTS(keyprefix << "SCAVACTION_OBJECT_ID", object_id, imsg);
          break;
        case QUIT:
        case NOOP:
          // OK, no other data
          break;
        default:
          DBGP_E(LOG_STREAM(std::cerr) << "Bad action_code: " << action_code << std::endl);
          return false;
        }
      return true;
    }

    std::string Action::GetObjectId (  )
    {
      return object_id;
    }

    bool Action::SetObjectId ( const std::string & object_id_in )
    {
      object_id = object_id_in;
      return true;
    }

    Location::Direction Action::GetDirection() const
    {
      return direction;
    }

    bool Action::SetDirection(Location::Direction direction_in)
    {
      if(direction_in >= Location::NORTH && direction_in <= Location::WEST)
        {
          direction = direction_in;
          return true;
        }
      return false;
    }

  }
}
