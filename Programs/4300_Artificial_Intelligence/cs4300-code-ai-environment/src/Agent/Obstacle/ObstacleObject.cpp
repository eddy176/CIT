#include <ai_obstacle.h>
#include <cmath>
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
    ObstacleObject::ObstacleObject()
    {
    }

    ObstacleObject::ObstacleObject(int tn_in, int nn_in,
				   ObstacleLocation *loc_in)
    {
      triangle_number = tn_in;
      node_number     = nn_in;
      location        = loc_in;
    }
    
    Percept *ObstacleObject::GetPercept(const Location *location)
    {
      ObstacleLocation *l = (ObstacleLocation *)this->location;
      Percept *percept = new Percept();
      double heading;
      double distance;
      HeadingDistance(location, heading, distance);
      char name_str[32];
      char value_str[32];
      if(triangle_number >= 0)
	{
	  sprintf(name_str, "%s_%d_%d",
		  GetName().c_str(),
		  triangle_number,
		  node_number);
	  sprintf(value_str, "%.04f %.02f",
		  heading, distance);
	  PerceptAtom atom(name_str, value_str);
	  percept->JoinAtom(atom);
	}
      else
	{
	  sprintf(name_str, "%s_X",
		  GetName().c_str());
	  sprintf(value_str, "%.02f",
		  l->GetX());
	  PerceptAtom x_atom(name_str, value_str);
	  percept->JoinAtom(x_atom);
	  
	  sprintf(name_str, "%s_Y",
		  GetName().c_str());
	  sprintf(value_str, "%.02f",
		  l->GetY());
	  PerceptAtom y_atom(name_str, value_str);
	  percept->JoinAtom(y_atom);
	}
      return percept;
    }
  
    bool ObstacleObject::HeadingDistance(const Location *location,
					 double &heading_out,
					 double &distance_out)
    {
      ObstacleLocation *obs_loc = 0;
      Location   *loc    = GetLocation();
      obs_loc = (ObstacleLocation *) loc;
    
      ObstacleLocation *obs_loc2 = 0;
      obs_loc2 = (ObstacleLocation *) location;
      
      double dx = obs_loc->GetX() - obs_loc2->GetX();
      double dy = obs_loc->GetY() - obs_loc2->GetY();
      double d2 = dx*dx + dy*dy;

      heading_out  = atan2(dy, dx);
      distance_out = sqrt(d2);
      
      return true;
    }
    int ObstacleObject::GetTriangleNumber() const
    {
      return triangle_number;
    }
    int ObstacleObject::GetNodeNumber() const
    {
      return node_number;
    }
  }
}
