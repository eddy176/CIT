#include <ai_vacuum.h>

namespace ai
{
  namespace Agent
  {
    bool VacuumAction::TextDisplay(std::ostream & os) const
    {
      std::string str = "";
    
      switch(GetCode())
	{
	case SUCK:
	  str = "Suck";
	  break;
	case LEFT:
	  str = "Left";
	  break;
	case RIGHT:
	  str = "Right";
	  break;
	case UP:
	  str = "Up";
	  break;
	case DOWN:
	  str = "Down";
	  break;
	case EMPTY_BAG:
	  str = "Empty Bag";
	  break;
	case NOOP:
	  str = "NoOp";
	  break;
	default:
	  return false;
	}
      os << str;
      return true;
    }
  }
}
