#ifndef _SCAVENGERBASE_H_
#define _SCAVENGERBASE_H_

namespace ai
{
  namespace Scavenger
  {
    class Base: public ai::Agent::Object
    {
    public:
      Base();
      Base(unsigned int agent_id_in, unsigned int cell_id_in);

      virtual ai::Agent::Percept *GetPercept(const ai::Agent::Location *location_in);
      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);

      bool         SetAgent(unsigned int agent_id_in);
      bool         SetCell(unsigned int cell_id_in);
      unsigned int GetAgent() const;
      unsigned int GetCell() const;

      bool AddObject ( ai::Scavenger::Object *obj_in );
      std::map<unsigned int, unsigned int> & GetHopper (  );
      ai::Scavenger::Object * GetObject(const unsigned int object_id_in);

      std::string GetString() const;
      static bool ParseString(const std::string &base_in,
                              unsigned int &cell_id_out);

      double GetHopperValue(const unsigned int skip_object_count, const unsigned int max_object_count) const;
    protected:
      unsigned int m_agent_id;
      unsigned int m_cell_id;

      std::map<unsigned int, unsigned int> m_hopper;
      std::map<unsigned int, unsigned int> m_sequence_number;
      int                                  m_next_sequence_number;
    private:
    };
  }
}

#endif /* _SCAVENGERBASE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
