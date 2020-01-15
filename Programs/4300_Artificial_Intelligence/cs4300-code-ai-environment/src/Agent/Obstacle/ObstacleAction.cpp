#include <ai_obstacle.h>
#include <cstdio>

#ifdef WIN32
#define sprintf sprintf
#else
#define sprintf std::sprintf
#endif

namespace ai
{
  namespace Agent
  {
    bool ObstacleAction::TextDisplay(std::ostream & os) const
    {
      std::string str = "";
    
      switch(GetCode())
	{
	case GO:
	  str = "Go ";
	  {
	    char c_str[32];
	    sprintf(c_str, "%.04f %.02f", direction, distance);
	    str += c_str;
	  }
	  break;
	case STOP:
	  str = "Stop";
	  break;
	default:
	  return false;
	}
      os << str;
      return true;
    }
    bool ObstacleAction::SetDirection(double dir_in)
    {
      direction = dir_in;
      return true;
    }
    bool ObstacleAction::SetDistance(double dist_in)
    {
      distance = dist_in;
      return true;
    }
    double ObstacleAction::GetDirection() const
    {
      return direction;
    }
    double ObstacleAction::GetDistance() const
    {
      return distance;
    }
    
  }
}
