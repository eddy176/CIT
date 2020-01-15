#ifndef _SCAVENGERCELLINTERFACE_H_
#define _SCAVENGERCELLINTERFACE_H_

namespace ai
{
  namespace Scavenger
  {
    class CellInterface
    {
    public:
      CellInterface();
      CellInterface(const std::string &title_in,
                    double damage_in,
                    double energy_cost_in,
                    bool   traversable_in,
                    bool   is_fall_in);
      CellInterface(const std::string &cell_interface_in);

      CellInterface &operator=(const CellInterface &rhs_in);

      bool SetTitle(const std::string &title_in);
      bool SetDamage(double damage_in);
      bool SetEnergyCost(double energy_cost_in);
      bool SetTraversable(bool traversable_in);
      bool SetIsFall(bool is_fall_in);

      std::string GetTitle() const;
      double      GetDamage() const;
      double      GetEnergyCost() const;
      bool        Traversable() const;
      bool        IsFall() const;
      std::string GetString() const;

      static bool ParseString(const std::string &str_in,
                              std::string &title_out,
                              double      &damage_out,
                              double      &energy_cost_out,
                              bool        &traversable_out,
                              bool        &is_fall_out);

      friend std::ostream &operator<<(std::ostream &os, const CellInterface &o);
      friend std::istream &operator>>(std::istream &is, CellInterface &o);
    protected:
      std::string title;
      double damage;
      double energy_cost;
      bool   traversable;
      bool   is_fall;
    private:
    };
  }
}

#endif /* _SCAVENGERCELLINTERFACE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
