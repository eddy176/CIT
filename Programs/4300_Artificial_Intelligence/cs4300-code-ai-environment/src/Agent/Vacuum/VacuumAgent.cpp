#include <typeinfo>
#include <stdio.h>
#include <ai_vacuum.h>

namespace ai
{
  namespace Agent
  {

    VacuumAgent::VacuumAgent(AgentProgram *agent_program_in)
      : XYAgent(agent_program_in)
    {
      n_dirt = 0;
    }
    
    Percept *VacuumAgent::GetPercept(const Location *location)
    {
      Percept *p = XYAgent::GetPercept(location);
      VacuumWorld *env = dynamic_cast<VacuumWorld *>(environment);
      
      if(n_dirt >= env->GetBagSize())
	{
	  PerceptAtom p_dirt("BagFull", "T");
	  p->JoinAtom(p_dirt);
	}
      
      return p;
    }
  
    bool VacuumAgent::Suck()
    {
      VacuumWorld *env = dynamic_cast<VacuumWorld *>(environment);
      if(n_dirt < env->GetBagSize())
	{
	  n_dirt++;
	  return true;
	}
      return false;
    }
    
    bool VacuumAgent::EmptyBag()
    {
      XYLocation *xy_loc = (XYLocation *) GetLocation();
      
      if((xy_loc->GetX() == 0) && (xy_loc->GetY() == 0))
	{
	  n_dirt = 0;
	  return true;
	}
      return false;
    }
    
    int VacuumAgent::GetNumDirt() const
    {
      return n_dirt;
    }

  }
}
