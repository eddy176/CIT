#include <ai_scavenger.h>
#include <cstdio>

namespace ai
{
  namespace Scavenger
  {
    const bool l_debug = false;

    CellInterface::CellInterface()
      : title(""),
        damage(0),
        energy_cost(0),
        traversable(false),
        is_fall(false)
    {
      if(l_debug)
        {
          std::cout << "CellInterface: Default Constructor: '" << title << "'" <<std::endl;
        }
    }

    CellInterface::CellInterface ( const std::string & title_in,
                                   double damage_in, double energy_cost_in,
                                   bool   traversable_in,
                                   bool   is_fall_in)
    {
      title       = title_in;
      damage      = damage_in;
      energy_cost = energy_cost_in;
      traversable = traversable_in;
      is_fall     = is_fall_in;

      if(l_debug)
        {
          std::cout << "CellInterface: Assigned Constructor: '" << title << "'" <<std::endl;
        }
    }

    CellInterface::CellInterface(const std::string &cell_interface_in)
    {
      ParseString(cell_interface_in,  title, damage, energy_cost, traversable, is_fall);

      if(l_debug)
        {
          std::cout << "CellInterface: String Constructor: '" << title << "'" <<std::endl;
        }
    }

    CellInterface & CellInterface::operator=(const CellInterface &rhs_in)
    {
      title       = rhs_in.title;
      damage      = rhs_in.damage;
      energy_cost = rhs_in.energy_cost;
      traversable = rhs_in.traversable;
      is_fall     = rhs_in.is_fall;

      if(l_debug)
        {
          std::cout << "CellInterface: operator=: '" << title << "'" <<std::endl;
        }

      return *this;
    }



    bool CellInterface::SetTitle(const std::string &title_in)
    {
      title = title_in;
      if(l_debug)
        {
          std::cout << "CellInterface: SetTitle: '" << title << "'" <<std::endl;
        }
      return true;
    }

    bool CellInterface::SetDamage(double damage_in)
    {
      damage = damage_in;
      return true;
    }
    bool CellInterface::SetEnergyCost(double energy_cost_in)
    {
      energy_cost = energy_cost_in;
      return true;
    }
    bool CellInterface::SetTraversable(bool traversable_in)
    {
      traversable = traversable_in;
      return true;
    }
    bool CellInterface::SetIsFall(bool is_fall_in)
    {
      is_fall = is_fall_in;
      return true;
    }



    std::string CellInterface::GetTitle (  ) const
    {
      if(l_debug)
        {
          std::cout << "CellInterface: GetTitle: '" << title << "'" <<std::endl;
        }
      return title;
    }

    double CellInterface::GetDamage (  ) const
    {
      return damage;
    }

    double CellInterface::GetEnergyCost (  ) const
    {
      return energy_cost;
    }

    bool CellInterface::Traversable (  ) const
    {
      return traversable;
    }

    bool CellInterface::IsFall (  ) const
    {
      return is_fall;
    }

    std::string CellInterface::GetString() const
    {
      char buf[64];
      std::string s = "";

      s += "Interface: ";
      std::sprintf(buf, "%s ", title.c_str());
      s += buf;
      std::sprintf(buf, "%.2f ", damage);
      s += buf;
      std::sprintf(buf, "%.2f ", energy_cost);
      s += buf;
      std::sprintf(buf, "%d ", traversable);
      s += buf;
      std::sprintf(buf, "%d ", is_fall);
      s += buf;

      return s;
    }

    bool CellInterface::ParseString(const std::string &str_in,
                                    std::string &title_out,
                                    double      &damage_out,
                                    double      &energy_cost_out,
                                    bool        &traversable_out,
                                    bool        &is_fall_out)
    {
      const char * s = str_in.c_str();
      int  traversable_int;
      int  is_fall_int;
      char title_char[64];

      std::sscanf(s,
                  "Interface: %s %lf %lf %d %d",
                  title_char,
                  &damage_out, &energy_cost_out,
                  &traversable_int,
                  &is_fall_int);

      title_out = title_char;
      traversable_out = traversable_int?true:false;
      is_fall_out = is_fall_int?true:false;

      return true;
    }

    std::ostream &operator<<(std::ostream &os, const CellInterface &o)
    {
      os << o.title << " " << o.damage << " " << o.energy_cost << " " << o.traversable << " " << o.is_fall;
      return os;
    }

    std::istream &operator>>(std::istream &is, CellInterface &o)
    {
      is >> o.title >> o.damage >> o.energy_cost >> o.traversable >> o.is_fall;
      return is;
    }

  }
}

