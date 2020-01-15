#include <ai_xy.h>

namespace ai
{
  namespace XY
  {
    ai::Agent::Percept *Object::GetPercept(const ai::Agent::Location *location)
    {
      ai::Agent::Percept *percept = new ai::Agent::Percept();
      if(Near(location, 1))
        {
          ai::Agent::PerceptAtom atom(GetName(), "T");
          percept->JoinAtom(atom);
        }
      return percept;
    }

    bool Object::Near(const ai::Agent::Location *location, int radius)
    {
      Location *xy_loc = dynamic_cast<Location *>(GetLocation());
      const Location *xy_loc2 = dynamic_cast<const Location *>(location);

      int dx = xy_loc->GetX() - xy_loc2->GetX();
      int dy = xy_loc->GetY() - xy_loc2->GetY();
      int d2 = dx*dx + dy*dy;
      int r2 = radius * radius;
      return d2 <= r2;
    }
    
    // Add Object's data to omsg, if values are different than stored in old_msg
    bool Object::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::Agent::Object::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
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
    bool Object::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::Agent::Object::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      
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

  }
}
