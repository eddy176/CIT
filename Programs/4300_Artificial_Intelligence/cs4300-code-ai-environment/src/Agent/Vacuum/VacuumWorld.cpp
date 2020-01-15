#include <typeinfo>
#include <ai_vacuum.h>

namespace ai
{
  namespace Agent
  {
    VacuumWorld::VacuumWorld(const RandomNumber &rand_in,
			     int width, int height, bool do_display)
      : XYEnvironment(rand_in, width, height, false)
    {
      if(do_display)
	{
	  display = new VacuumWorldDisplay(this);
	}
#define VACUUM_BAG_SIZE 100000
      bag_size   = VACUUM_BAG_SIZE;
      suck_cost  = -2; /* noise and electricity */
      empty_cost = -2; /* noise and electricity */
      move_cost  = -1; /* electricity */
#undef VACUUM_BAG_SIZE 
    }

    bool VacuumWorld::ApplyAction(Agent *agent, Action *action)
    {
      if(typeid(*action) == typeid(XYAction))
	{
	  return XYEnvironment::ApplyAction(agent, action);
	}
  
      VacuumAction *vc_action = dynamic_cast<VacuumAction *>(action);
      XYAgent      *xy_agent  = dynamic_cast<XYAgent *>(agent);
      VacuumAgent  *v_agent   = dynamic_cast<VacuumAgent *>(agent);
      if(vc_action == 0)
	{
	  std::cerr << "vc_action is 0" << std::endl;
	  (*vc_action) = (*vc_action); // this should segfault
	}
      if(xy_agent == 0)
	{
	  std::cerr << "xy_agent is 0" << std::endl;
	  (*xy_agent) = (*xy_agent); // this should segfault
	}
      if(v_agent == 0)
	{
	  std::cerr << "v_agent is 0" << std::endl;
	  (*v_agent) = (*v_agent); // this should segfault
	}
      switch(vc_action->GetCode())
	{
	case VacuumAction::SUCK:
	  {
	    int n = RemoveDirt((XYLocation *)agent->GetLocation(),
			       bag_size - v_agent->GetNumDirt());
	    while(n > 0)
	      {
		v_agent->Suck();
		n --;
	      }
	    agent->AddPerformance(suck_cost);
	  }
	  break;
	case VacuumAction::LEFT:
	  while(xy_agent->GetDirection() != 180)
	    {
	      xy_agent->TurnRight();
	    }
	  xy_agent->Forward(width, height);
	  agent->AddPerformance(move_cost);
	  break;
	case VacuumAction::RIGHT:
	  while(xy_agent->GetDirection() != 0)
	    {
	      xy_agent->TurnRight();
	    }
	  xy_agent->Forward(width, height);
	  agent->AddPerformance(move_cost);
	  break;
	case VacuumAction::UP:
	  while(xy_agent->GetDirection() != 90)
	    {
	      xy_agent->TurnRight();
	    }
	  xy_agent->Forward(width, height);
	  agent->AddPerformance(move_cost);
	  break;
	case VacuumAction::DOWN:
	  while(xy_agent->GetDirection() != 270)
	    {
	      xy_agent->TurnRight();
	    }
	  xy_agent->Forward(width, height);
	  agent->AddPerformance(move_cost);
	  break;
	case VacuumAction::EMPTY_BAG:
	  v_agent->EmptyBag();
  	  agent->AddPerformance(empty_cost);
	  break;
	case VacuumAction::NOOP:
	  break;
	default:
	  return false;
	}
      return true;
    }
      
    void VacuumWorld::CalculatePerformance(Agent *agent)
    { // one point per timestep per clean location;
      unsigned int clean = 0;

      int x, y;

      for(x = 0; x < width; x++)
	{
	  for(y = 0; y < height; y ++)
	    {
	      bool is_clean = true;
	      std::vector<Object *>::iterator i;
	      for(i = objects.begin(); i != objects.end(); i++)
		{
		  XYLocation *loc = dynamic_cast<XYLocation *>( ((*i)->GetLocation()) );
		  if(loc == 0)
		    {
		      std::cerr << "loc is 0" << std::endl;
		      (*loc) = (*loc); // this should segfault
		    }

		  if((loc->GetX() == x) &&
		     (loc->GetY() == y))
		    {
		      is_clean = false;
		      break;
		    }
		}
	      if(is_clean)
		{
		  clean ++;
		}	      
	    }
	}
      agent->AddPerformance(clean);
    }
  
    int VacuumWorld::RemoveDirt(XYLocation *xy_loc, int max_remove)
    {
      int n_removed = 0;
      std::vector<Object *>::iterator i;
      for(i = objects.begin(); i != objects.end(); i++)
	{
	  XYLocation *loc = dynamic_cast<XYLocation *>( ((*i)->GetLocation()) );
	  if(loc == 0)
	    {
	      std::cerr << "loc is 0" << std::endl;
	      (*loc) = (*loc); // this should segfault
	    }

	  if(n_removed >= max_remove)
	    {
	      break;
	    }
	  
	  if((loc->GetX() == xy_loc->GetX()) &&
	     (loc->GetY() == xy_loc->GetY()) &&
	     (typeid(**i) == typeid(DirtObject)))
	    {
	      i--;
	      delete *(i+1);
	      objects.erase(i+1);
	      n_removed ++;
	    }
	}
      return n_removed;
    }


    bool VacuumWorld::SetMoveCost(int cost_in)
    {
      if(cost_in > 0) { return false; }
      move_cost = cost_in;
      return true;
    }
    
    bool VacuumWorld::SetSuckCost(int cost_in)
    {
      if(cost_in > 0) { return false; }
      suck_cost = cost_in;
      return true;
    }
    
    bool VacuumWorld::SetEmptyCost(int cost_in)
    {
      if(cost_in > 0) { return false; }
      empty_cost = cost_in;
      return true;
    }
    
    bool VacuumWorld::SetBagSize(int size_in)
    {
      if(size_in < 0) { return false; }
      bag_size = size_in;
      return true;
    }
    
    
    int VacuumWorld::GetMoveCost() const
    {
      return move_cost;
    }
    
    int VacuumWorld::GetSuckCost() const
    {
      return suck_cost;
    }
    
    int VacuumWorld::GetEmptyCost() const
    {
      return empty_cost;
    }
    
    int VacuumWorld::GetBagSize() const
    {
      return bag_size;
    }
    
  }
}

