#include <ai_obstacle.h>

namespace ai
{
  namespace Agent
  {
    double ObstacleLocation::GetX() const
    {
      return x;
    }
  
    double ObstacleLocation::GetY() const
    {
      return y;
    }
  
    void ObstacleLocation::Set(double x_in, double y_in)
    {
      x = x_in;
      y = y_in;
    }
  
  }
}
