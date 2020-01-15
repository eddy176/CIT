#include <ai_wumpus.h>

namespace ai
{
  namespace Wumpus
  {
    GoldObject::GoldObject()
    {
      SetName("Gold");
    }

    ai::Agent::Percept *GoldObject::GetPercept(const ai::Agent::Location *location)
    {
      ai::Agent::Percept *percept = new ai::Agent::Percept();
      if(Near(location, 0))
        {
          ai::Agent::PerceptAtom atom("GLITTER", "T");
          percept->JoinAtom(atom);
        }
      return percept;
    }

    bool GoldObject::Near(const ai::Agent::Location *location, int distance)
    { /* manhattan distance formula */
      ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(GetLocation());
      const ai::XY::Location *xy_loc2 = dynamic_cast<const ai::XY::Location *>(location);

      int dx = abs(xy_loc->GetX() - xy_loc2->GetX());
      int dy = abs(xy_loc->GetY() - xy_loc2->GetY());
      int dist = dx + dy;
      return dist <= distance;
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool GoldObject::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::XY::Object::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
      ADD_TO_MSG("OBJECT_WUMPUSOBJECT_TYPE " << m_object_id, "GOLD", omsg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool GoldObject::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::XY::Object::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      return true;
    }


    PitObject::PitObject()
    {
      SetName("Pit");
    }

    ai::Agent::Percept *PitObject::GetPercept(const ai::Agent::Location *location)
    {
      ai::Agent::Percept *percept = new ai::Agent::Percept();
      if(Near(location, 1))
        {
          ai::Agent::PerceptAtom atom("BREEZE", "T");
          percept->JoinAtom(atom);
        }
      return percept;
    }

    bool PitObject::Near(const ai::Agent::Location *location, int distance)
    { /* manhattan distance formula */
      ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(GetLocation());
      const ai::XY::Location *xy_loc2 = dynamic_cast<const ai::XY::Location *>(location);

      int dx = abs(xy_loc->GetX() - xy_loc2->GetX());
      int dy = abs(xy_loc->GetY() - xy_loc2->GetY());
      int dist = dx + dy;

      return dist <= distance;
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool PitObject::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::XY::Object::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
      ADD_TO_MSG("OBJECT_WUMPUSOBJECT_TYPE " << m_object_id, "PIT", omsg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool PitObject::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::XY::Object::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      return true;
    }

    WumpusObject::WumpusObject()
    {
      SetName("Wumpus");
      alive  = true;
      scream = false;
    }

    ai::Agent::Percept *WumpusObject::GetPercept(const ai::Agent::Location *location)
    {
      ai::Agent::Percept *percept = new ai::Agent::Percept();
      if(Near(location, 1))
        {
          ai::Agent::PerceptAtom atom("STENCH", "T");
          percept->JoinAtom(atom);
        }
      if(scream)
        {
          ai::Agent::PerceptAtom atom("SCREAM", "T");
          percept->JoinAtom(atom);
          scream = false;
        }
      return percept;
    }

    bool WumpusObject::Near(const ai::Agent::Location *location, int distance)
    { /* manhattan distance formula */
      ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(GetLocation());
      const ai::XY::Location *xy_loc2 = dynamic_cast<const ai::XY::Location *>(location);

      int dx = abs(xy_loc->GetX() - xy_loc2->GetX());
      int dy = abs(xy_loc->GetY() - xy_loc2->GetY());
      int dist = dx + dy;
      return dist <= distance;
    }


    // Add Object's data to omsg, if values are different than stored in old_msg
    bool WumpusObject::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::XY::Object::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
      ADD_TO_MSG("OBJECT_WUMPUSOBJECT_TYPE " << m_object_id, "WUMPUS", omsg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_WUMPUSOBJECT_ALIVE " << m_object_id, alive, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_WUMPUSOBJECT_SCREAM " << m_object_id, scream, omsg, old_msg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool WumpusObject::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::XY::Object::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      SET_FROM_MSG_IF_EXISTS("OBJECT_WUMPUSOBJECT_ALIVE " << m_object_id, alive, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_WUMPUSOBJECT_SCREAM " << m_object_id, scream, imsg);
      return true;
    }

    void WumpusObject::Kill()
    {
      if(alive)
        {
          alive  = false;
          scream = true;
        }
    }

    bool WumpusObject::IsAlive() const
    {
      return alive;
    }


    TardisObject::TardisObject()
    {
      SetName("Tardis");
    }

    ai::Agent::Percept *TardisObject::GetPercept(const ai::Agent::Location *location)
    {
      ai::Agent::Percept *percept = new ai::Agent::Percept();
      if(Near(location, 1))
        {
          ai::Agent::PerceptAtom atom("TEMPORAL_WARP", "T");
          percept->JoinAtom(atom);
        }
      return percept;
    }

    bool TardisObject::Near(const ai::Agent::Location *location, int distance)
    { /* manhattan distance formula */
      ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(GetLocation());
      const ai::XY::Location *xy_loc2 = dynamic_cast<const ai::XY::Location *>(location);

      int dx = abs(xy_loc->GetX() - xy_loc2->GetX());
      int dy = abs(xy_loc->GetY() - xy_loc2->GetY());
      int dist = dx + dy;
      return dist <= distance;
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool TardisObject::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::XY::Object::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
      ADD_TO_MSG("OBJECT_WUMPUSOBJECT_TYPE " << m_object_id, "TARDIS", omsg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool TardisObject::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::XY::Object::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      return true;
    }

  }
}
