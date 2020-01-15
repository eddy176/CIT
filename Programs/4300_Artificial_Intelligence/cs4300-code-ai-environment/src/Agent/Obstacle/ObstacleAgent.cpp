#include <typeinfo>
#include <cmath>
#include <stdio.h>
#include <ai_obstacle.h>

namespace ai
{
  namespace Agent
  {
    ObstacleAgent::ObstacleAgent()
    {
    }

    ObstacleAgent::ObstacleAgent(Socket * sock_in)
      : Agent(sock_in)
    {
      stopped     = false;
      bump        = false;
      found_goal  = false;
      path_cost   = 0.;
    }
  
    Percept *ObstacleAgent::GetPercept(const Location *location)
    {
      ObstacleLocation *obs_loc = 0;
      Location   *loc    = GetLocation();
      //if(typeid(*loc) == typeid(ObstacleLocation))
      {
	obs_loc = (ObstacleLocation *) loc;
      }
      char x_str[16];
      char y_str[16];
      sprintf(x_str, "%.02f", obs_loc->GetX());
      sprintf(y_str, "%.02f", obs_loc->GetY());
    
      Percept *p = new Percept();
      PerceptAtom p_X("X", x_str);
      PerceptAtom p_Y("Y", y_str);
    
      p->JoinAtom(p_X);
      p->JoinAtom(p_Y);
      if(bump)
	{
	  PerceptAtom p_bump("BUMP", "T");
	  p->JoinAtom(p_bump);
	}
    
      return p;
    }
  
    void ObstacleAgent::Go(double direction_in, double distance_in)
    { 
      ObstacleLocation *obs_loc = 0;
      Location   *loc    = GetLocation();
      obs_loc = (ObstacleLocation *) loc;

      double x = obs_loc->GetX();
      double y = obs_loc->GetY();
      x += cos(direction_in) * distance_in;
      y += sin(direction_in) * distance_in;
      obs_loc->Set(x, y);
      path_cost += distance_in;
    }
  
    void ObstacleAgent::Stop()
    {
      stopped = true;
      alive   = false;
    }
  
    bool ObstacleAgent::GetStopped() const
    {
      return stopped;
    }

    void ObstacleAgent::SetBump(bool bump_in)
    {
      bump = bump_in;
    }

    bool ObstacleAgent::GetBump() const
    {
      return bump;
    }
    
    double  ObstacleAgent::GetPathCost() const
    {
      return path_cost;
    }
    bool    ObstacleAgent::GetFoundGoal() const
    {
      return found_goal;
    }
    void    ObstacleAgent::FoundGoal()
    {
      found_goal = true;
    }

  }
}
