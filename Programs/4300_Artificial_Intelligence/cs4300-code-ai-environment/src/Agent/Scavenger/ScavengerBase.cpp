#include <ai_scavenger.h>
#include <cstdio>

namespace ai
{
  namespace Scavenger
  {
    Base::Base()
      : m_agent_id(0), m_cell_id(0),
        m_next_sequence_number(0)
    {
    }

    Base::Base(unsigned int agent_id_in, unsigned int cell_id_in)
      : m_agent_id(agent_id_in), m_cell_id(cell_id_in),
        m_next_sequence_number(0)
    {
    }

    ai::Agent::Percept *Base::GetPercept(const ai::Agent::Location *location_in)
    {
      const Location *agent_location = dynamic_cast<const Location *>(location_in);
      const Location *base_location = dynamic_cast<const Location *>(location);
      ai::Agent::Percept *p = new ai::Agent::Percept;

      if((base_location->GetX() == agent_location->GetX()) &&
         (base_location->GetY() == agent_location->GetY()))
        {
          char base_str[16];
          sprintf(base_str, "%d",
                  (m_agent_id)
                  );
          ai::Agent::PerceptAtom p_BASE("BASE", base_str);
          p->JoinAtom(p_BASE);
        }

      /* put all hopper items into percept */
      for(auto hit = m_hopper.begin(); hit != m_hopper.end(); hit++)
        {
          const std::string &id_str = environment->GetObject(hit->second)->GetIdString();
          p->JoinAtom(ai::Agent::PerceptAtom(std::string("BASE_HOPPER_") + id_str, id_str));
        }

      return p;
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool Base::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      if(!ai::Agent::Object::AddToMessageIfChanged(omsg, old_msg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to add to message." << std::endl);
          return false;
        }
      Location *sl = dynamic_cast<Location *>(location);
      if(sl)
        {
          ADD_TO_MSG("OBJECT_HAS_SCAVLOCATION " << m_object_id, true, omsg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVLOCATION_X " << m_object_id, sl->x, omsg, old_msg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVLOCATION_Y " << m_object_id, sl->y, omsg, old_msg);
          ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVLOCATION_ELEVATION " << m_object_id, sl->elevation, omsg, old_msg);
        }
      else
        {
          ADD_TO_MSG("OBJECT_HAS_SCAVLOCATION " << m_object_id, false, omsg);
        }
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVBASE_AGENT_ID " << m_object_id,
                            m_agent_id, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVBASE_CELL_ID " << m_object_id,
                            m_cell_id, omsg, old_msg);
      ADD_MAP_TO_MSG_IF_CHANGED("OBJECT_SCAVBASE_HOPPER " << m_object_id, m_hopper, omsg, old_msg);
      ADD_MAP_TO_MSG_IF_CHANGED("OBJECT_SCAVBASE_SEQUENCE_NUMBER " << m_object_id, m_sequence_number, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVBASE_NEXT_SEQUENCE_NUMBER " << m_object_id,
                            m_next_sequence_number, omsg, old_msg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool Base::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      if(!ai::Agent::Object::SetFromMessageIfExists(id, imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to extract from message." << std::endl);
          return false;
        }
      bool has_slocation = false;
      SET_FROM_MSG("OBJECT_HAS_SCAVLOCATION " << m_object_id, has_slocation, imsg);
      if(has_slocation)
        {
          Location *sl = dynamic_cast<Location *>(location);
          if(!sl)
            {
              if(location) { delete location; location = 0; }
              location = sl = new Location;
            }
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVLOCATION_X " << m_object_id, sl->x, imsg);
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVLOCATION_Y " << m_object_id, sl->y, imsg);
          SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVLOCATION_ELEVATION " << m_object_id, sl->elevation, imsg);
        }
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVBASE_AGENT_ID " << m_object_id,
                             m_agent_id, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVBASE_CELL_ID " << m_object_id,
                             m_cell_id, imsg);

      SET_MAP_FROM_MSG_IF_EXISTS("OBJECT_SCAVBASE_HOPPER " << m_object_id, m_hopper, unsigned int, imsg);
      SET_MAP_FROM_MSG_IF_EXISTS("OBJECT_SCAVBASE_SEQUENCE_NUMBER " << m_object_id, m_sequence_number, unsigned int, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVBASE_NEXT_SEQUENCE_NUMBER " << m_object_id,
                             m_next_sequence_number, imsg);
      return true;
    }

    bool Base::SetAgent(unsigned int agent_id_in)
    {
      m_agent_id = agent_id_in;
      return true;
    }
    bool Base::SetCell(unsigned int cell_id_in)
    {
      m_cell_id = cell_id_in;
      return true;
    }
    unsigned int Base::GetAgent() const
    {
      return m_agent_id;
    }
    unsigned int Base::GetCell() const
    {
      return m_cell_id;
    }

    bool Base::AddObject ( ai::Scavenger::Object *obj_in )
    {
      m_hopper[obj_in->GetIdNum()] = obj_in->GetIdNum();
      m_sequence_number[obj_in->GetIdNum()] = m_next_sequence_number++;
      return true;
    }

    std::map<unsigned int, unsigned int> & Base::GetHopper (  )
    {
      return m_hopper;
    }

    ai::Scavenger::Object * Base::GetObject(const unsigned int object_id_in)
    {
      auto hit = m_hopper.find(object_id_in);
      if(hit != m_hopper.end())
        {
          return dynamic_cast<ai::Scavenger::Object *>(environment->GetObject(object_id_in));
        }
      return 0;
    }

    std::string Base::GetString() const
    {
      char buf[128];
      std::string s = "";
      s += "Base: ";
      if(m_cell_id)
        {
          sprintf(buf, "%d",m_cell_id);
          s += buf;
        }
      else
        {
          s += "0";
        }
      return s;
    }

    bool Base::ParseString(const std::string &base_in,
                           unsigned int &cell_id_out)
    {
      const char * s = base_in.c_str();

      std::sscanf(s,
                  "Base: %d",
                  &cell_id_out);

      return true;
    }

    double Base::GetHopperValue(const unsigned int skip_object_count, const unsigned int max_object_count) const
    {
      double total = 0;
      int count = 0;
      for(auto hit = m_hopper.begin(); hit != m_hopper.end(); hit++, count++)
        {
          std::map<unsigned int, unsigned int>::const_iterator sit = m_sequence_number.find(hit->second);
          if(sit != m_sequence_number.end() &&
             sit->second >= skip_object_count &&
             sit->second < max_object_count)
            {
              total += dynamic_cast<ai::Scavenger::Object *>(environment->GetObject(hit->second))->GetValue();
            }
        }
      return total;
    }
  }
}
