#ifndef _SCAVENGERLOCATION_H_
#define _SCAVENGERLOCATION_H_

namespace ai
{
  namespace Scavenger
  {
    class Location: public ai::Agent::Location
    {
    public:

      Location();
      Location(const int& unused);
      Location(const Location &rhs);
      Location(double x_in, double y_in, double elevation_in);
      bool Set(double x_in, double y_in, double elevation_in);
      double GetX() const;
      double GetY() const;
      double GetElevation() const;

      // the numbers are important as they are used as array indexes
      enum Direction { NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3 };

      Location & operator=(const Location &rhs);
      bool operator==(const Location &rhs) const;
      bool operator<(const Location &rhs) const;

      std::string             GetString() const;
    protected:
      friend class Agent;
      friend class Object;
      friend class Base;
      friend class Cell;
      friend std::ostream &operator<<(std::ostream &os, const Location &loc);
      friend std::istream &operator>>(std::istream &is, Location &loc);

      double x;
      double y;
      double elevation;

    private:
    };

  }
}

#endif /* _SCAVENGERLOCATION_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
