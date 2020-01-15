#ifndef _SCAVENGEROBJECT_H_
#define _SCAVENGEROBJECT_H_

namespace ai
{
  namespace Scavenger
  {
    class Object: public ai::Agent::Object
    {
    public:
      Object(const std::string &object_in, unsigned int &cell_id_out); // sets id from the string
      Object(); // automatically sets the id
      Object(const std::string &short_name_in, // automatically sets the id
             const double &value_in,
             const std::string &type_in,
             const double &mass_in,
             const double &volume_in,
             const std::string &color_in,
             const std::string &shape_in,
             const std::string &size_in,
             const std::string &luminescence_in);

      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);

      std::string GetExamineString();
      std::string GetDepositString();
      std::string GetPickupString();

      bool SetShortName(const std::string &short_name_in);
      bool SetValue(const double value_in);
      bool SetType(const std::string &type_in);
      bool SetMass(const double mass_in);
      bool SetVolume(const double volume_in);
      bool SetColor(const std::string &color_in);
      bool SetShape(const std::string &shape_in);
      bool SetSize(const std::string &size_in);
      bool SetLuminescence(const std::string &luminescence_in);
      bool AddOther(const std::string &other_in);

      std::string GetShortName() const;
      double GetValue() const;
      std::string GetType() const;
      double GetMass() const;
      double GetVolume() const;
      std::string GetColor() const;
      std::string GetShape() const;
      std::string GetSize() const;
      std::string GetLuminescence() const;
      const std::vector<std::string> & GetOther() const;

      std::string GetString(const unsigned int cell_id) const;
      bool ParseString(const std::string &str_in,
                       unsigned int &cell_id_out);

    protected:
      std::string short_name;
      double value;
      std::string type;
      double mass;
      double volume;
      std::string color;
      std::string shape;
      std::string size;
      std::string luminescence;
      std::vector<std::string> other;
    private:
    };
  }
}

#endif /* _SCAVENGEROBJECT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
