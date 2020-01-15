#include <typeinfo>
#include <stdio.h>
#include <ai_xy.h>

namespace ai
{
  namespace XY
  {
    Agent::Agent()
    {
    }

    Agent::Agent(ai::Agent::Socket * sock_in)
      : ai::Agent::Agent(sock_in), bump(false), direction(0)
    {
    }

    ai::Agent::Percept *Agent::GetPercept(const ai::Agent::Location *location)
    {
      Location *xy_loc = dynamic_cast<Location *>(GetLocation());
      char dir_str[16];
      sprintf(dir_str, "%d", direction);
      char x_str[16];
      sprintf(x_str, "%d", xy_loc->GetX());
      char y_str[16];
      sprintf(y_str, "%d", xy_loc->GetY());

      ai::Agent::Percept *p = new ai::Agent::Percept();
      ai::Agent::PerceptAtom p_bump("Bump", bump?"T":"F");
      ai::Agent::PerceptAtom p_direction("Direction", dir_str);
      ai::Agent::PerceptAtom p_X("X", x_str);
      ai::Agent::PerceptAtom p_Y("Y", y_str);

      p->JoinAtom(p_bump);
      p->JoinAtom(p_direction);
      p->JoinAtom(p_X);
      p->JoinAtom(p_Y);

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
      // bump, direction, XYLocation
      ADD_TO_MSG_IF_CHANGED("OBJECT_XYAGENT_BUMP " << m_object_id, bump, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_XYAGENT_DIRECTION " << m_object_id, direction, omsg, old_msg);
      // XYLocation
      Location *xy_location = dynamic_cast<Location *>(location);
      if(xy_location)
        {
          ADD_TO_MSG("OBJECT_HAS_XYLOCATION " << m_object_id, true, omsg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_XYLOCATION_X " << m_object_id, xy_location->x, omsg, old_msg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_XYLOCATION_Y " << m_object_id, xy_location->y, omsg, old_msg);
        }
      else
        {
          ADD_TO_MSG("OBJECT_HAS_XYLOCATION " << m_object_id, false, omsg);
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
      // bump, direction, XYLocation
      SET_FROM_MSG_IF_EXISTS("OBJECT_XYAGENT_BUMP " << m_object_id, bump, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_XYAGENT_DIRECTION " << m_object_id, direction, imsg);
      // XYLocation
      bool has_xylocation = false;
      SET_FROM_MSG("OBJECT_HAS_XYLOCATION " << m_object_id, has_xylocation, imsg);
      if(has_xylocation)
        {
          Location *xy_location = dynamic_cast<Location *>(location);
          if(!xy_location)
            {
              if(location) { delete location; location = 0; }
              location = xy_location = new Location;
            }
          SET_FROM_MSG_IF_EXISTS("OBJECT_XYLOCATION_X " << m_object_id, xy_location->x, imsg);
          SET_FROM_MSG_IF_EXISTS("OBJECT_XYLOCATION_Y " << m_object_id, xy_location->y, imsg);
        }
      return true;
    }

    void Agent::TurnRight()
    {
      bump = false;
      direction -= 90;
      while(direction < 0)
        {
          direction += 360;
        }
    }

    void Agent::TurnLeft()
    {
      bump = false;
      direction += 90;
      while(direction >= 360)
        {
          direction -= 360;
        }
    }

    void Agent::Forward(int width_in, int height_in)
    {
      int dx = 0;
      int dy = 0;
      switch(direction)
        {
        case 0:
          dx = 1;
          dy = 0;
          break;
        case 90:
          dx = 0;
          dy = 1;
          break;
        case 180:
          dx = -1;
          dy = 0;
          break;
        case 270:
          dx = 0;
          dy = -1;
          break;
        }
      Location *xy_loc = dynamic_cast<Location *>(GetLocation());
      int x = xy_loc->GetX();
      int y = xy_loc->GetY();
      if(((x + dx) >= width_in) ||
         ((x + dx) < 0) ||
         ((y + dy) >= height_in) ||
         ((y + dy) < 0))
        {
          bump = true;
        }
      else
        {
          xy_loc->Set(x + dx, y + dy);
          bump = false;
        }
    }

    int Agent::GetDirection()
    {
      return direction;
    }

  }
}
