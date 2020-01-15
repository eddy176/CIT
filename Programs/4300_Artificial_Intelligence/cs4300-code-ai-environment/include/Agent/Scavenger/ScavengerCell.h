#ifndef _SCAVENGERCELL_H_
#define _SCAVENGERCELL_H_

namespace ai
{
  namespace Scavenger
  {
    class Object;

    class Cell
    {
    public:
      /*
       *
       */
      Cell();
      Cell(Location location_in, unsigned int id_in);
      Cell(const std::string &cell_in);

      /*
       * Note that although Cell stores pointers to various data objects,
       * it does not delete any of the pointers.
       *
       * The pointers are not deleted in the destructor, or in the Remove*()
       * methods.
       *
       * The neighbor, obj, and base pointers should be kept in unique lists
       * somewhere else for proper clean up.
       *
       */
      virtual ~Cell();

      // Add Object's data to omsg, if values are different than stored in old_msg
      virtual bool AddToMessageIfChanged(ai::Agent::Message &omsg, ai::Agent::Message &old_msg);
      // Set Object's data from imsg, if values associated with id are present
      virtual bool SetFromMessageIfExists(unsigned int id, ai::Agent::Message &imsg);


      bool                    SetLocation(const Location & location_in);
      bool                    SetNeighborId(const Location::Direction &which,
                                            unsigned int cell_id_in);
      bool                    SetInterface(const Location::Direction &which,
                                           const CellInterface &iface_in);
      bool                    AddObject(unsigned int obj_id_in);
      bool                    RemoveObject(unsigned int obj_id_in);
      bool                    AddBase(unsigned int base_id_in);
      bool                    RemoveBase(unsigned int base_id_in);

      bool                    SetVisited(const int i);
      int                     GetVisited() const;

      unsigned int            GetId() const;
      ai::Scavenger::Location GetLocation() const;
      unsigned int            GetNeighborId(const Location::Direction &which) const;
      CellInterface           GetInterface(const Location::Direction &which) const;
      std::map<unsigned int, unsigned int> & GetObjects();
      unsigned int            GetObject(unsigned int object_id_in);
      std::map<unsigned int, unsigned int>   & GetBases();
      std::string             GetString() const;

      static bool             ParseString(const std::string &str_in,
                                          unsigned int &id_out,
                                          Location &location_out,
                                          unsigned int neighbors_out[4],
                                          CellInterface interfaces_out[4]);
    protected:
      unsigned int          m_cell_id;
      Location              location;
      unsigned int          neighbor_ids[4];
      CellInterface         interfaces[4];
      std::map<unsigned int, unsigned int> objs;
      std::map<unsigned int, unsigned int> bases;
      int                   visited;
    private:
    };
  }
}

#endif /* _SCAVENGERCELL_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
