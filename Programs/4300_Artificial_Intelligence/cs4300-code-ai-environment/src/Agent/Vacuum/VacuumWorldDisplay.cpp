#include <ai_vacuum.h>

#ifdef USE_GLUT
#include <ai_glut.h>
#include <typeinfo>

namespace ai
{
  namespace Agent
  {
    static VacuumWorldDisplay *ed = 0;
    static void display()
    {
      ed->Redraw(ed->GetEnv());
    }
    
    VacuumWorldDisplay::VacuumWorldDisplay(Environment *env)
      : XYEnvironmentDisplay(env)
    {
      ed = this;
      glutDisplayFunc(display);
    }
    VacuumWorldDisplay::~VacuumWorldDisplay()
    {
    }
    void VacuumWorldDisplay::Redraw(Environment *env)
    {
      VacuumWorld *xy_env = dynamic_cast<VacuumWorld *>(env);
      if(xy_env == 0)
	{
	  std::cerr << "xy_env is 0" << std::endl;
	  (*xy_env) = (*xy_env); // should cause segfault
	}
      
      //GLfloat whiteMaterial[]       = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat greenMaterial[]       = {0.1f, 0.7f, 0.4f, 1.0f};
      //GLfloat brightGreenMaterial[] = {0.1f, 0.9f, 0.1f, 1.0f};
      GLfloat blueMaterial[]        = {0.1f, 0.2f, 0.7f, 1.0f};
      GLfloat brownMaterial[]       = {0.7f, 0.2f, 0.2f, 1.0f};
  
      glViewport(0, 0, width, height);
  
      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);
      glMatrixMode(GL_MODELVIEW);
  
      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT);
  
      SetColor(blueMaterial);
  
      int i;
      int x, y;
      for(i = 0; i <= xy_env->width; i++)
	{
	  x = i * spacing;
	  if(x >= width)
	    {
	      x = width - 1;
	    }
	  if(x < 0)
	    {
	      x = 0;
	    }
	  DrawLine(x, 0, x, height);
	}
  
      for(i = 0; i <= xy_env->height; i++)
	{
	  y = i * spacing;
	  if(y >= height)
	    {
	      y = height - 1;
	    }
	  if(y < 1)
	    {
	      y = 1;
	    }
      
	  DrawLine(0, y, width, y);
	}
  
      unsigned int j;
      for(j = 0; j < xy_env->objects.size(); j++)
	{
	  if(typeid(*xy_env->objects[j]) == typeid(XYObject))
	    {
	      XYLocation *xy_loc = (XYLocation *)xy_env->objects[j]->GetLocation();
	      int x = spacing*xy_loc->GetX() + spacing/2;
	      int y = height - (spacing*xy_loc->GetY() + spacing/2);
	      SetColor(blueMaterial);
	      DrawCircle(x, y, spacing/3);
	    }
	  else if(typeid(*xy_env->objects[j]) == typeid(DirtObject))
	    {
	      XYLocation *xy_loc = (XYLocation *)xy_env->objects[j]->GetLocation();
	      int x = spacing*xy_loc->GetX() + spacing/2;
	      int y = height - (spacing*xy_loc->GetY() + spacing/2);
	      SetColor(brownMaterial);
	      DrawRectangle(x-spacing/4, y-spacing/4, x+spacing/4, y+spacing/4 );
	    }
	}
      for(j = 0; j < xy_env->agents.size(); j++)
	{
	  if(typeid(*xy_env->agents[j]) == typeid(VacuumAgent))
	    {
	      XYLocation *xy_loc =
		(XYLocation *)xy_env->agents[j]->GetLocation();
	      //XYAgent *xy_agent = (XYAgent *)xy_env->agents[j];
	  
	      int x = spacing*xy_loc->GetX() + spacing/2;
	      int y = height - (spacing*xy_loc->GetY() + spacing/2);
	      SetColor(greenMaterial);
	      DrawTriangle(x, y+spacing/4,
			   x-spacing/4, y-spacing/4,
			   x+spacing/4, y-spacing/4); 
	    }
	}
  
      glutSwapBuffers();
    }
  }
}
#else
namespace ai
{
  namespace Agent
  {
    VacuumWorldDisplay::VacuumWorldDisplay(Environment *env, int width_in, int height_in)
      : XYEnvironmentDisplay(env,width_in,height_in)	
    {
    }
    VacuumWorldDisplay::~VacuumWorldDisplay()
    {
    }
    void VacuumWorldDisplay::Redraw(Environment *env)
    {
    }
  }
}
#endif


  
