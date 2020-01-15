#include <ai_scavenger.h>
#include <cstdio>

namespace ai
{
  namespace Scavenger
  {
    Location::Location()
    {
      Set(0., 0., 0.);
    }
    Location::Location(const int& unused)
    {
      (void)unused;
      Set(0., 0., 0.);
    }
    Location::Location(const Location &rhs)
    {
      *this = rhs;
    }
    Location::Location ( double x_in, double y_in, double elevation_in )
    {
      Set(x_in, y_in, elevation_in);
    }

    bool Location::Set ( double x_in, double y_in, double elevation_in )
    {
      x = x_in;
      y = y_in;
      elevation = elevation_in;
      return true;
    }

    double Location::GetX (  ) const
    {
      return x;
    }

    double Location::GetY (  ) const
    {
      return y;
    }

    double Location::GetElevation (  ) const
    {
      return elevation;
    }

    Location & Location::operator=(const Location &rhs)
    {
      x = rhs.x;
      y = rhs.y;
      elevation = rhs.elevation;
      return *this;
    }

    bool Location::operator==(const Location &rhs) const
    {
      if((x == rhs.x) &&
         (y == rhs.y) &&
         (elevation == rhs.elevation))
        {
          return true;
        }
      return false;
    }

    bool Location::operator<(const Location &rhs) const
    {
      if(x < rhs.x) { return true; }
      if(x > rhs.x) { return false; }
      if(y < rhs.y) { return true; }
      if(y > rhs.y) { return false; }
      if(elevation < rhs.elevation) { return true; }
      return false;
    }

    std::string             Location::GetString() const
    {
      std::string s = "";
      char buf[64];

      std::sprintf(buf, "%.2f ", x);
      s += buf;
      std::sprintf(buf, "%.2f ", y);
      s += buf;
      std::sprintf(buf, "%.2f", elevation);
      s += buf;

      return s;
    }

    std::ostream &operator<<(std::ostream &os, const Location &loc)
    {
      os << loc.x << " " << loc.y << " " << loc.elevation;
      return os;
    }
    std::istream &operator>>(std::istream &is, Location &loc)
    {
      is >> loc.x >> loc.y >> loc.elevation;
      return is;
    }

  }
}

