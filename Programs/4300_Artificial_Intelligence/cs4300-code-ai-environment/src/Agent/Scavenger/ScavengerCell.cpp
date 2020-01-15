#include <ai_scavenger.h>
#include <cstdio>

namespace ai
{
  namespace Scavenger
  {
    Cell::Cell()
    {
      unsigned int i;
      for(i = 0; i < 4; i++)
        {
          neighbor_ids[i] = 0;
        }
    }

    Cell::Cell(Location location_in, unsigned int id_in)
      : m_cell_id(id_in),
        location(location_in),
        visited(0)
    {
      unsigned int i;
      for(i = 0; i < 4; i++)
        {
          neighbor_ids[i] = 0;
        }

    }

    Cell::Cell(const std::string &cell_in)
      : visited(0)
    {
      unsigned int i;
      for(i = 0; i < 4; i++)
        {
          neighbor_ids[i] = 0;
        }

      ParseString(cell_in,
                  m_cell_id,
                  location,
                  neighbor_ids,
                  interfaces);
    }

    Cell::~Cell()
    {
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool Cell::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
    {
      ADD_TO_MSG_IF_CHANGED("CELL_ID " << m_cell_id, m_cell_id, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("CELL_SCAVLOCATION_X " << m_cell_id, location.x, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("CELL_SCAVLOCATION_Y " << m_cell_id, location.y, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("CELL_SCAVLOCATION_ELEVATION " << m_cell_id, location.elevation, omsg, old_msg);
      ADD_ARRAY_TO_MSG_IF_CHANGED("CELL_NEIGHBOR_IDS " << m_cell_id, neighbor_ids, 4, omsg, old_msg);
      ADD_ARRAY_TO_MSG_IF_CHANGED("CELL_INTERFACES " << m_cell_id, interfaces, 4, omsg, old_msg);
      ADD_MAP_TO_MSG_IF_CHANGED("CELL_OBJECTS " << m_cell_id, objs, omsg, old_msg);
      ADD_MAP_TO_MSG_IF_CHANGED("CELL_BASES " << m_cell_id, bases, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("CELL_VISITED " << m_cell_id, visited, omsg, old_msg);
      return true;
    }

    // Set Object's data from imsg, if values associated with id are present
    bool Cell::SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg)
    {
      SET_FROM_MSG_IF_EXISTS("CELL_ID " << id, m_cell_id, imsg);
      SET_FROM_MSG_IF_EXISTS("CELL_SCAVLOCATION_X " << m_cell_id, location.x, imsg);
      SET_FROM_MSG_IF_EXISTS("CELL_SCAVLOCATION_Y " << m_cell_id, location.y, imsg);
      SET_FROM_MSG_IF_EXISTS("CELL_SCAVLOCATION_ELEVATION " << m_cell_id, location.elevation, imsg);
      SET_ARRAY_FROM_MSG_IF_EXISTS("CELL_NEIGHBOR_IDS " << m_cell_id, neighbor_ids, 4, imsg);
      SET_ARRAY_FROM_MSG_IF_EXISTS("CELL_INTERFACES " << m_cell_id, interfaces, 4, imsg);
      SET_MAP_FROM_MSG_IF_EXISTS("CELL_OBJECTS " << m_cell_id, objs, unsigned int, imsg);
      SET_MAP_FROM_MSG_IF_EXISTS("CELL_BASES " << m_cell_id, bases, unsigned int, imsg);
      SET_FROM_MSG_IF_EXISTS("CELL_VISITED " << m_cell_id, visited, imsg);
      return true;
    }

    bool                    Cell::SetLocation(const Location & location_in)
    {
      location = location_in;
      return true;
    }

    bool                    Cell::SetNeighborId(const Location::Direction &which,
                                                unsigned int cell_id_in)
    {
      neighbor_ids[which] = cell_id_in;
      return true;
    }

    bool                    Cell::SetInterface(const Location::Direction &which,
                                               const CellInterface &iface_in)
    {
      interfaces[which] = iface_in;
      return true;
    }

    bool                    Cell::AddObject(unsigned int obj_id_in)
    {
      objs[obj_id_in] = obj_id_in;
      return true;
    }

    bool                    Cell::RemoveObject(unsigned int obj_id_in)
    {
      auto oit = objs.find(obj_id_in);
      if(oit == objs.end())
        {
          return false;
        }
      objs.erase(oit);
      return true;
    }

    bool                    Cell::AddBase(unsigned int base_id_in)
    {
      bases[base_id_in] = base_id_in;
      return true;
    }

    bool                    Cell::RemoveBase(unsigned int base_id_in)
    {
      auto bit = bases.find(base_id_in);
      if(bit == bases.end())
        {
          return false;
        }
      bases.erase(bit);
      return true;
    }

    bool                    Cell::SetVisited(const int i)
    {
      visited |= i;
      return true;
    }
    int                     Cell::GetVisited() const
    {
      return visited;
    }

    unsigned int            Cell::GetId() const
    {
      return m_cell_id;
    }

    ai::Scavenger::Location Cell::GetLocation() const
    {
      return location;
    }

    unsigned int            Cell::GetNeighborId(const Location::Direction &which) const
    {
      return neighbor_ids[which];
    }

    CellInterface           Cell::GetInterface(const Location::Direction &which) const
    {
      return interfaces[which];
    }

    std::map<unsigned int, unsigned int> & Cell::GetObjects()
    {
      return objs;
    }

    unsigned int Cell::GetObject(unsigned int object_id_in)
    {
      unsigned int obj_id = 0;
      auto oit = objs.find(object_id_in);
      if(oit != objs.end())
        {
          obj_id = oit->second;
        }
      return obj_id;
    }

    std::map<unsigned int, unsigned int>   & Cell::GetBases()
    {
      return bases;
    }

    std::string             Cell::GetString() const
    {
      char buf[64];
      std::string s = "";

      s += "Cell: ";
      std::sprintf(buf, "%d ", m_cell_id);
      s += buf;

      std::sprintf(buf, "%.2f ", location.GetX());
      s += buf;
      std::sprintf(buf, "%.2f ", location.GetY());
      s += buf;
      std::sprintf(buf, "%.2f ", location.GetElevation());
      s += buf;

      unsigned int i;
      for(i = 0; i < 4; i++)
        {
          std::sprintf(buf, "%d ", neighbor_ids[i]);
          s += buf;
        }
      for(i = 0; i < 4; i++)
        {
          if(interfaces[i].GetTitle() == "")
            {
              std::sprintf(buf, "empty ");
            }
          else
            {
              std::sprintf(buf, "%s ", interfaces[i].GetTitle().c_str());
            }
          s += buf;
        }
      return s;
    }

    bool             Cell::ParseString(const std::string &str_in,
                                       unsigned int &id_out,
                                       Location &location_out,
                                       unsigned int neighbors_out[4],
                                       CellInterface interfaces_out[4])
    {
      const char * s = str_in.c_str();
      double x, y, z;
      char iface[4][64];
      unsigned int i;

      for(i = 0; i < 4; i++)
        {
          iface[i][0] = 0;
        }

      std::sscanf(s,
                  "Cell: %d %lf %lf %lf %d %d %d %d %63s %63s %63s %63s ",
                  &id_out,
                  &x, &y, &z,
                  &neighbors_out[0], &neighbors_out[1], &neighbors_out[2], &neighbors_out[3],
                  iface[0], iface[1], iface[2], iface[3]
                  );
      location_out.Set(x, y, z);

      for(i = 0; i < 4; i++)
        {
          interfaces_out[i].SetTitle(iface[i]);
        }
      return true;
    }


  }
}
