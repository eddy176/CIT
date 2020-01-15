#include <ai_scavenger.h>
#include <cctype>
#include <cstdio>

namespace ai
{
  namespace Scavenger
  {
    Object::Object(const std::string &object_in, unsigned int &cell_id_out)
    {
      Object::ParseString(object_in, cell_id_out);
    }

    Object::Object()
    {
    }

    Object::Object(const std::string &short_name_in,
                   const double &value_in,
                   const std::string &type_in,
                   const double &mass_in,
                   const double &volume_in,
                   const std::string &color_in,
                   const std::string &shape_in,
                   const std::string &size_in,
                   const std::string &luminescence_in)
      : ai::Agent::Object(),
        short_name(short_name_in),
        value(value_in),
      type(type_in),
      mass(mass_in),
      volume(volume_in),
      color(color_in),
      shape(shape_in),
      size(size_in),
      luminescence(luminescence_in)
    {
    }

    ai::Agent::Percept *Object::GetPercept(const ai::Agent::Location *location)
    {
      ai::Agent::Percept *percept = new ai::Agent::Percept();

      const Location *agent_location   = dynamic_cast<const Location *>(location);
      const Location *object_location  = dynamic_cast<const Location *>(GetLocation());

      if(!object_location)
        { // object is in the bin, or in the base, don't report it here
          return percept;
        }

      if(*agent_location == *object_location)
        {
          percept->JoinAtom(ai::Agent::PerceptAtom(std::string("OBJECT_") + m_object_id_str, m_object_id_str));
        }

      return percept;
    }

    // Add Object's data to omsg, if values are different than stored in old_msg
    bool Object::AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg)
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
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_SHORT_NAME " << m_object_id, short_name, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_VALUE " << m_object_id, value, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_TYPE " << m_object_id, type, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_MASS " << m_object_id, mass, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_VOLUME " << m_object_id, volume, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_COLOR " << m_object_id, color, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_SHAPE " << m_object_id, shape, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_SIZE " << m_object_id, size, omsg, old_msg);
      ADD_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_LUMINESCENCE " << m_object_id, luminescence, omsg, old_msg);
      ADD_VECTOR_TO_MSG_IF_CHANGED("OBJECT_SCAVOBJECT_OTHER " << m_object_id, other, omsg, old_msg);
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
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_SHORT_NAME " << m_object_id, short_name, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_VALUE " << m_object_id, value, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_TYPE " << m_object_id, type, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_MASS " << m_object_id, mass, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_VOLUME " << m_object_id, volume, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_COLOR " << m_object_id, color, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_SHAPE " << m_object_id, shape, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_SIZE " << m_object_id, size, imsg);
      SET_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_LUMINESCENCE " << m_object_id, luminescence, imsg);
      SET_VECTOR_FROM_MSG_IF_EXISTS("OBJECT_SCAVOBJECT_OTHER " << m_object_id, other, imsg);
      return true;
    }

    std::string Object::GetExamineString()
    {
      char buf[64];
      std::string s = "";
      std::sprintf(buf, "%s ", m_object_id_str.c_str());
      s += buf;

      std::sprintf(buf, "%s ", color.c_str());
      s += buf;
      std::sprintf(buf, "%s ", shape.c_str());
      s += buf;
      std::sprintf(buf, "%s ", size.c_str());
      s += buf;
      std::sprintf(buf, "%s ", luminescence.c_str());
      s += buf;

      return s;
    }

    std::string Object::GetDepositString()
    {
      char buf[64];
      std::string s = "";
      std::sprintf(buf, "%s ", m_object_id_str.c_str());
      s += buf;

      std::sprintf(buf, "%f", value);
      s += buf;

      return s;
    }

    std::string Object::GetPickupString()
    {
      char buf[64];
      std::string s = "";
      std::sprintf(buf, "%s", m_object_id_str.c_str());
      s += buf;
      return s;
    }

    bool Object::SetShortName(const std::string & short_name_in)
    {
      short_name = short_name_in;
      return true;
    }
    bool Object::SetValue(const double value_in)
    {
      value = value_in;
      return true;
    }
    bool Object::SetType(const std::string &type_in)
    {
      type = type_in;
      return true;
    }
    bool Object::SetMass(const double mass_in)
    {
      mass = mass_in;
      return true;
    }
    bool Object::SetVolume(const double volume_in)
    {
      volume = volume_in;
      return true;
    }
    bool Object::SetColor(const std::string &color_in)
    {
      color = color_in;
      return true;
    }
    bool Object::SetShape(const std::string &shape_in)
    {
      shape = shape_in;
      return true;
    }
    bool Object::SetSize(const std::string &size_in)
    {
      size = size_in;
      return true;
    }
    bool Object::SetLuminescence(const std::string &luminescence_in)
    {
      luminescence = luminescence_in;
      return true;
    }
    bool Object::AddOther(const std::string &other_in)
    {
      other.push_back(other_in);
      return true;
    }

    std::string Object::GetShortName() const
    {
      return short_name;
    }
    double Object::GetValue() const
    {
      return value;
    }
    std::string Object::GetType() const
    {
      return type;
    }
    double Object::GetMass() const
    {
      return mass;
    }
    double Object::GetVolume() const
    {
      return volume;
    }
    std::string Object::GetColor() const
    {
      return color;
    }
    std::string Object::GetShape() const
    {
      return shape;
    }
    std::string Object::GetSize() const
    {
      return size;
    }
    std::string Object::GetLuminescence() const
    {
      return luminescence;
    }
    const std::vector<std::string> & Object::GetOther() const
    {
      return other;
    }

    std::string Object::GetString(const unsigned int cell_id) const
    {
      char buf[128];
      std::string s = "";

      s += "Object: ";
      std::sprintf(buf, "%s ", m_object_id_str.c_str());
      s += buf;
      std::sprintf(buf, "%d ", cell_id);
      s += buf;

      std::sprintf(buf, "%s ", short_name.c_str());
      s += buf;
      std::sprintf(buf, "%.2f ", value);
      s += buf;
      std::sprintf(buf, "%s ", type.c_str());
      s += buf;
      std::sprintf(buf, "%.2f ", mass);
      s += buf;
      std::sprintf(buf, "%.2f ", volume);
      s += buf;
      std::sprintf(buf, "%s ", color.c_str());
      s += buf;
      std::sprintf(buf, "%s ", shape.c_str());
      s += buf;
      std::sprintf(buf, "%s ", size.c_str());
      s += buf;
      std::sprintf(buf, "%s ", luminescence.c_str());
      s += buf;

      unsigned int i;
      for(i = 0; i < other.size(); i++)
        {
          std::sprintf(buf, "%s ", other[i].c_str());
          s += buf;
        }

      return s;
    }

    /* currently, s points to a non-space character.
     * skip forward until we find a space, then skip all spaces. */
    const char *skip_to_space(const char *s)
    {
      while(*s && !std::isspace(*s)) { s++; } /* skip non-spaces */
      while(*s && std::isspace(*s)) { s++; }  /* skip spaces */
      return s;
    }

    bool Object::ParseString(const std::string &str_in,
                             unsigned int &cell_id_out)
    {
      const char * s = str_in.c_str();
      char buf[64];

      // Object:
      s = skip_to_space(s);

      unsigned int id_tmp;
      if(s[0] == 'O')
        { // format is OBJ%05d
          std::sscanf(s, "OBJ%d", &id_tmp);
        }
      else
        { // format is %d
          std::sscanf(s, "%d", &id_tmp);
        }
      if(!SetId(id_tmp))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Unable to SetId()" << std::endl);
        }

      s = skip_to_space(s);
      std::sscanf(s, "%d", &cell_id_out);
      s = skip_to_space(s);

      std::sscanf(s, "%s", buf);
      short_name = buf;
      s = skip_to_space(s);

      std::sscanf(s, "%lf", &value);
      s = skip_to_space(s);

      std::sscanf(s, "%s", buf);
      type = buf;
      s = skip_to_space(s);

      std::sscanf(s, "%lf", &mass);
      s = skip_to_space(s);

      std::sscanf(s, "%lf", &volume);
      s = skip_to_space(s);

      std::sscanf(s, "%s", buf);
      color = buf;
      s = skip_to_space(s);

      std::sscanf(s, "%s", buf);
      shape = buf;
      s = skip_to_space(s);

      std::sscanf(s, "%s", buf);
      size = buf;
      s = skip_to_space(s);

      std::sscanf(s, "%s", buf);
      luminescence = buf;
      s = skip_to_space(s);

      while(*s)
        {
          std::sscanf(s, "%s", buf);
          std::string o = buf;
          s = skip_to_space(s);
          other.push_back(o);
        }

      return true;
    }

  }
}
