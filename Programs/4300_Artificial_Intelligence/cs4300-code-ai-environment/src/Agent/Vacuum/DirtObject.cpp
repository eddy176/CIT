#include <ai_vacuum.h>

namespace ai
{
  namespace Agent
  {
    DirtObject::DirtObject()
    {
      SetName("Dirt");
    }
  
    Percept *DirtObject::GetPercept(const Location *location)
    {
      Percept *percept = new Percept();
      if(Near(location, 0))
	{
	  PerceptAtom atom(GetName(), "T");
	  percept->JoinAtom(atom);
	}
      return percept;
    }
  }
}
