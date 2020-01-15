#include <ai_obstacle.h>

#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>

namespace ai
{
  namespace Agent
  {
    ObstacleWorld::ObstacleWorld()
      : triangles(0)
    {
      goal_x = 0.0;
      goal_y = 0.0;
      //triangles.reserve(100);
    }
    
    ObstacleWorld::~ObstacleWorld()
    {
    }
    
    bool ObstacleWorld::AddNode(int triangle_index, int node_index,
				double x_in, double y_in)
    {
      if(triangles.capacity() < (unsigned int)(triangle_index + 1))
	{
	  triangles.reserve(triangle_index+1);
	  triangles.resize(triangle_index+1);
	}
      triangles[triangle_index].x[node_index] = x_in;
      triangles[triangle_index].y[node_index] = y_in;
      return true;
    }
    
    bool ObstacleWorld::SetGoal(double x_in, double y_in)
    {
      goal_x = x_in;
      goal_y = y_in;
      return true;
    }
    
    int  ObstacleWorld::GetNumTriangle() const
    {
      return (int)triangles.size();
    }
    
    bool ObstacleWorld::GetGoal(double &x_out, double &y_out) const
    {
      x_out = goal_x;
      y_out = goal_y;
      return true;
    }
    
    bool ObstacleWorld::GetNode(int triangle_index, int node_index,
				double &x_out, double &y_out) const
    {
      if(triangles.size() > (unsigned int)triangle_index)
	{
	  x_out = triangles[triangle_index].x[node_index];
	  y_out = triangles[triangle_index].y[node_index];
	  return true;
	}
      return false;
    }
    
    const double MY_EPSILON =  0.0001;
    const double MY_INFINITY = 100000.1;
    
    static bool SolveLine(double &x1, double &y1, double &x2, double &y2,
			  double &m, double &b)
    {
      double dx, dy;
      if(x1 > x2)
	{
	  double t = x1;
	  x1 = x2;
	  x2 = t;
	  t = y1;
	  y1 = y2;
	  y2 = t;
	}
      dx = x2 - x1;
      dy = y2 - y1;
      if(dx < MY_EPSILON)
	{
	  m = MY_INFINITY;
	  b = x1;
	  return false;
	}
      else
	{
	  m = dy/dx;
	  b = y1 - m*x1;
	  return true;
	}
    }
    
    static bool Between(double x1, double x2, double X)
    {
      if(x1 > x2)
	{
	  double t = x1;
	  x1 = x2;
	  x2 = t;
	}
      return (((X - x1 + MY_EPSILON) > 0) && ((x2 - X + MY_EPSILON) > 0));
    }
    
    static bool SamePoint(double x1, double y1, double x2, double y2)
    {
      double dx = fabs(x1 - x2);
      double dy = fabs(y1 - y2);
      if(dx < MY_EPSILON && dy < MY_EPSILON)
	{
	  return true;
	}
      return false;
    }
    
    static bool LinesIntersect(double x1, double y1, double x2, double y2,
			       double xx1, double yy1, double xx2, double yy2,
			       double &X, double &Y)
    {
      double m, b;
      double mm, bb;
      bool   v, vv;
      if(SamePoint(x1, y1, xx1, yy1) ||
	 SamePoint(x1, y1, xx2, yy2) ||
	 SamePoint(x2, y2, xx1, yy1) ||
	 SamePoint(x2, y2, xx2, yy2))
	{
	  return false;
	}
      v  = SolveLine(x1, y1, x2, y2, m, b);
      vv = SolveLine(xx1, yy1, xx2, yy2, mm, bb);
      if(v && vv)
	{ // normal case, no vertical lines
	  double dm = m - mm;
	  double db = bb - b;
	  if(fabs(dm) < MY_EPSILON)
	    { // parallel lines
	      return false;
	    }
	  X = db/dm;
	  Y = m*X + b;
	  if(Between(x1, x2, X) && Between(xx1, xx2, X) &&
	     Between(y1, y2, Y) && Between(yy1, yy2, Y))
	    {
	      return true;
	    }
	  return false;
	}
      else if(!v && !vv)
	{ // both vertical, either at the same X, or not.
	  return (fabs(b - bb) < MY_EPSILON);
	}
      else if(!v)
	{ // one vertical
	  X = b;
	  Y = mm * X + bb;
	  if(Between(xx1, xx2, X) && Between(y1, y2, Y) && Between(yy1, yy2, Y))
	    {
	      return true;
	    }
	  return false;
	}
      else if(!vv)
	{
	  X = bb;
	  Y = m * X + b;
	  if(Between(x1, x2, X) && Between(y1, y2, Y) && Between(yy1, yy2, Y))
	    {
	      return true;
	    }
	  return false;
	}
      return false;
    }
    
    bool ObstacleWorld::IntersectsWithObstacle(double x1, double y1,
					       double x2, double y2)
    {
      min_dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
      int i, j;
      bool rval = false;
      for(i = 0; i < GetNumTriangle(); i++)
	{
	  for(j = 0; j < 3; j++)
	    {
	      double xx1=0.0, xx2=0.0, yy1=0.0, yy2=0.0;
	      double X = 0, Y = 0;
	      if(!GetNode(i, j, xx1, yy1) ||
		 !GetNode(i, (j+1)%3, xx2, yy2))
		{
		  std::cerr << "ERROR in IntersectsWithObstacle.  GetNode returned false.  i = " << i << ", j = " << j << std::endl;
		  rval = true;
		}
	      
	      if(LinesIntersect(x1, y1, x2, y2, xx1, yy1, xx2, yy2, X, Y))
		{
		  double dist = sqrt((X-x1)*(X-x1) + (Y-y1)*(Y-y1));
		  if(dist < min_dist)
		    {
		      min_dist = dist;
		    }
		  rval = true;
		}
	    }
	}
      return rval;
    }
    
    double ObstacleWorld::GetMinDist() const
    {
      return min_dist;
    }
    
    ObstacleEnvironment::ObstacleEnvironment()
    {
    }
    
    ObstacleEnvironment::ObstacleEnvironment(const RandomNumber &rand_in,
					     double width_in,
					     double height_in,
					     std::vector<Socket *> *displays_in)
      : Environment(rand_in, displays_in)
    {
      width  = width_in;
      height = height_in;
      fully_observable = false;
      max_step_distance = 10.;
      data = new ObstacleWorld();
    }
  
    ObstacleEnvironment::~ObstacleEnvironment()
    {
      if(data)
	{
	  ObstacleWorld *w = (ObstacleWorld *)data;
	  delete w;
	  data = 0;
	}
    }

    void ObstacleEnvironment::DoGo(ObstacleAgent  *obs_agent,
				   ObstacleAction *obs_action)
    {
      ObstacleWorld *w = (ObstacleWorld *)data;
      double x1, y1, x2, y2;
      double dir, dist;

      dir  = obs_action->GetDirection();
      dist = obs_action->GetDistance();
      if(dist < 0.)
	{
	  dist = 0.;
	}
      if(dist > max_step_distance)
	{
	  dist = max_step_distance;
	}
      
      ObstacleLocation *l = (ObstacleLocation *)obs_agent->GetLocation();
      x1 = l->GetX();
      y1 = l->GetY();
      x2 = x1 + cos(dir)*dist;
      y2 = y1 + sin(dir)*dist;

      if((x2 < 0. || x2 > width) ||
	 (y2 < 0. || y2 > height))
	{
	  dist = 0;
	  x2 = x1;
	  y2 = y1;
	}
      
      if(w->IntersectsWithObstacle(x1, y1, x2, y2))
	{
	  dist = w->GetMinDist() - 1.;
	  obs_agent->SetBump(true);
	}
      else
	{
	  obs_agent->SetBump(false);
	}
      
      obs_agent->Go(dir, dist);
      
      {
	double goal_x;
	double goal_y;
	w->GetGoal(goal_x, goal_y);
	l = (ObstacleLocation *)obs_agent->GetLocation();
	x1 = l->GetX();
	y1 = l->GetY();

	double dist = sqrt((goal_x-x1)*(goal_x-x1) + (goal_y-y1)*(goal_y-y1));
	if(dist <= 0.1)
	  {
	    obs_agent->FoundGoal();
	  }
      }
    }
    
    bool ObstacleEnvironment::ApplyAction(Agent *agent, Action *action)
    {
      ObstacleAction *obs_action = (ObstacleAction *) action;
      ObstacleAgent  *obs_agent  = (ObstacleAgent *) agent;
      switch(obs_action->GetCode())
	{
	case ObstacleAction::GO:
	  DoGo(obs_agent, obs_action);
	  break;
	case ObstacleAction::STOP:
	  obs_agent->Stop();
	  break;
	default:
	  return false;
	}
      return true;
    }
  
    void ObstacleEnvironment::CalculatePerformance(Agent *agent)
    { // FIXME
    }
  
    Percept *ObstacleEnvironment::GetPercept(Agent *agent)
    {
      Percept *percept = new Percept();
      unsigned int i;

      Percept *p = agent->GetPercept(agent->GetLocation());
      percept->Join(p);
      delete p;

      double x1, y1, x2, y2;
      ObstacleLocation *l = (ObstacleLocation *)agent->GetLocation();
      x1 = l->GetX();
      y1 = l->GetY();
      
      ObstacleWorld *w = (ObstacleWorld *)data;
      
      for(i = 0; i < objects.size(); i++)
	{
	  l = (ObstacleLocation *)objects[i]->GetLocation();
	  x2 = l->GetX();
	  y2 = l->GetY();
	  if((fully_observable) ||
             (!w->IntersectsWithObstacle(x1, y1, x2, y2)))
	    {
	      if(strcmp(objects[i]->GetName().c_str(), "BEACON") == 0)
		{
		  p = objects[i]->GetPercept(agent->GetLocation());
		  percept->Join(p);
		  delete p;
		}
            }
	  if(!w->IntersectsWithObstacle(x1, y1, x2, y2))
	    {
              if(strcmp(objects[i]->GetName().c_str(), "GOAL") == 0)
		{
		  PerceptAtom atom("GOAL_VISIBLE", "T");
		  percept->JoinAtom(atom);
		}
	    }
	  
	  if(strcmp(objects[i]->GetName().c_str(), "GOAL") == 0)
	    {
	      p = objects[i]->GetPercept(agent->GetLocation());
	      percept->Join(p);
	      delete p;
	    }
	}
      return percept;
    }

    void ObstacleEnvironment::AddObject(Object *object, Location *location)
    {
      Environment::AddObject(object, location);
      ObstacleObject    *o = (ObstacleObject *)object;
      ObstacleLocation  *l = (ObstacleLocation *)location;
      ObstacleWorld     *w = (ObstacleWorld *)data;
      if(strcmp(o->GetName().c_str(), "BEACON") == 0)
	{
	  w->AddNode(o->GetTriangleNumber(), o->GetNodeNumber(),
		     l->GetX(), l->GetY());
	}
      else if(strcmp(o->GetName().c_str(), "GOAL") == 0)
	{
	  w->SetGoal(l->GetX(), l->GetY());
	}
    }

    Location *ObstacleEnvironment::DefaultLocation() const
    {
      ObstacleLocation *obs_loc = new ObstacleLocation();
      obs_loc->Set(0.0, height/2.);
      return obs_loc;
    }
  
    double ObstacleEnvironment::GetWidth() const
    {
      return width;
    }
    double ObstacleEnvironment::GetHeight() const
    {
      return height;
    }
    void ObstacleEnvironment::SetWidth(double width_in)
    {
      width = width_in;
      //if(display)
      //{
      //((ObstacleEnvironmentDisplay *)display)->SetSize(width, height);
      //}
    }
    void ObstacleEnvironment::SetHeight(double height_in)
    {
      height = height_in;
      //if(display)
      //{
      //((ObstacleEnvironmentDisplay *)display)->SetSize(width, height);
      //}
    }
    bool   ObstacleEnvironment::GetFullyObservable() const
    {
      return fully_observable;
    }
    void   ObstacleEnvironment::SetFullyObservable(bool fully_observable_in)
    {
      fully_observable = fully_observable_in;
    }
    double ObstacleEnvironment::GetMaxStepDistance() const
    {
      return max_step_distance;
    }
    void   ObstacleEnvironment::SetMaxStepDistance(double max_step_distance_in)
    {
      max_step_distance = max_step_distance_in;
    }
  
  }
}
