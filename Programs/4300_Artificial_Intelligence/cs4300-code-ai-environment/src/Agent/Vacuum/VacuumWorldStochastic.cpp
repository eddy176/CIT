#include <typeinfo>
#include <ai_vacuum.h>

namespace ai
{
  namespace Agent
  {
    VacuumWorldStochastic::VacuumWorldStochastic(const RandomNumber &rand_in,
						 int width, int height,
						 bool do_display,
						 double dirty_percent_in)
      : VacuumWorld(rand_in, width, height, do_display)
    {
      dirty_percent = dirty_percent_in;
    }

    void VacuumWorldStochastic::Step()
    {
      Environment::Step();
      int x, y;
      bool have_dirt;
      XYLocation *xy_loc = new XYLocation();
      for(x = 0; x < width; x ++)
	{
	  for(y = 0; y < height; y ++)
	    {
	      xy_loc->Set(x, y);

	      have_dirt = false;
	      std::vector<Object *>::iterator i;
	      for(i = objects.begin(); i != objects.end(); i++)
		{
		  XYLocation *loc = (XYLocation *) (*i)->GetLocation();
		
		  if((loc->GetX() == xy_loc->GetX()) &&
		     (loc->GetY() == xy_loc->GetY()) &&
		     (typeid(**i) == typeid(DirtObject)))
		    {
		      // already have dirt
		      have_dirt = true;
		    }
		}
	      if(!have_dirt)
		{
		  if(random_number.Rand() < dirty_percent)
		    {
		      DirtObject     *d     = new DirtObject;
		      XYLocation     *d_loc = new XYLocation;
		      d_loc->Set(x,y);
		      AddObject(d, d_loc);
		    }
		}
	    }
	}

    }
  }
}

