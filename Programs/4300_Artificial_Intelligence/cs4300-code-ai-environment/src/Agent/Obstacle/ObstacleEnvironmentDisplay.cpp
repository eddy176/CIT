#include <ai_obstacle.h>

#ifdef USE_GLUT

#include <ai_glut.h>
#include <typeinfo>

namespace ai
{
  namespace Agent
  {
    static ObstacleEnvironmentDisplay *ed = 0;
    static void display()
    {
      ed->Redraw(ed->GetEnv());
    }
    
    ObstacleEnvironmentDisplay::ObstacleEnvironmentDisplay(Environment *env, int width_in, int height_in)
      : EnvironmentDisplay(env, 100, 100)
    {
      ObstacleEnvironment *obs_env = (ObstacleEnvironment *) env;
      
      ed = this;
      glutDisplayFunc(display);

      width   = width_in;
      height  = height_in;
      
      double s1 = (double)width/(double)obs_env->width;
      double s2 = (double)height/(double)obs_env->height;
      scaling = s1 > s2 ? s2 : s1;
      
      glutSetWindow(window);
      glutReshapeWindow(width, height);
      glutMainLoopEvent();
    }
  
    ObstacleEnvironmentDisplay::~ObstacleEnvironmentDisplay()
    {
    }
  
    void ObstacleEnvironmentDisplay::Redraw(Environment *env)
    {
      ObstacleEnvironment *obs_env = (ObstacleEnvironment *) env;
    
      GLfloat whiteMaterial[]       = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat greenMaterial[]       = {0.1f, 0.9f, 0.4f, 1.0f};
      //GLfloat brightGreenMaterial[] = {0.1f, 0.9f, 0.1f, 1.0f};
      GLfloat blueMaterial[]        = {0.3f, 0.5f, 0.7f, 1.0f};
      GLfloat redMaterial[]         = {0.8f, 0.2f, 0.1f, 1.0f};
      
      glutSetWindow(window);
     
      glViewport(0, 0, width, height);
	
      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);
      glMatrixMode(GL_MODELVIEW);

      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT);
    
      SetColor(whiteMaterial);
    
      double i;
      int x, y;
      for(i = 0.; i <= obs_env->width; i+=100.)
	{
	  x = (int)(i * scaling);
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
    
      for(i = 0; i <= obs_env->height; i+=100.)
	{
	  y = (int)(i * scaling);
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
      int node_count      = 0;
      int triangle_number = -1;
      int          t_x[3];
      int          t_y[3];
      for(j = 0; j < obs_env->objects.size(); j++)
	{
	  if(typeid(*obs_env->objects[j]) == typeid(ObstacleObject))
	    {
	      ObstacleObject *o = (ObstacleObject *)obs_env->objects[j];
	      ObstacleLocation *obs_loc =
		(ObstacleLocation *)obs_env->objects[j]->GetLocation();
	      int x = (int)(scaling*obs_loc->GetX());
	      int y = (int)(height - (scaling*obs_loc->GetY()));
	      
	      if(strcmp(o->GetName().c_str(), "BEACON") == 0)
		{
		  if(o->GetTriangleNumber() == triangle_number)
		    {
		      node_count ++;
		      t_x[o->GetNodeNumber()] = x;
		      t_y[o->GetNodeNumber()] = y;
		    }
		  else
		    {
		      node_count = 1;
		      triangle_number = o->GetTriangleNumber();
		      t_x[o->GetNodeNumber()] = x;
		      t_y[o->GetNodeNumber()] = y;
		    }
		  SetColor(blueMaterial);
		}
	      else if(strcmp(o->GetName().c_str(), "GOAL") == 0)
		{
		  SetColor(redMaterial);
		}
	      DrawCircle(x, y, 2);
	      if(node_count == 3)
		{
		  DrawTriangle(t_x[0], t_y[0],
			       t_x[1], t_y[1],
			       t_x[2], t_y[2]);
		  node_count      = 0;
		  triangle_number = -1;
		}
	    }
	}
      for(j = 0; j < obs_env->agents.size(); j++)
	{
	  if(typeid(*obs_env->agents[j]) == typeid(ObstacleAgent))
	    {
	      ObstacleLocation *obs_loc =
		(ObstacleLocation *)obs_env->agents[j]->GetLocation();
	      //ObstacleAgent *obs_agent = (ObstacleAgent *)obs_env->agents[j];
	    
	      int x = (int)(scaling*obs_loc->GetX());
	      int y = (int)(height - (scaling*obs_loc->GetY()));
	      SetColor(greenMaterial);
	      DrawCircle(x, y, 5);
	    }
	}
    
      glutSwapBuffers();
    }
    void ObstacleEnvironmentDisplay::SetSize(double width_in,
					     double height_in)
    {
      width   = (int)(width_in  * scaling);
      height  = (int)(height_in * scaling);

      glutSetWindow(window);
      glutReshapeWindow(width, height);
      glutPostRedisplay();
    }
    
  }  
}
#else /* no glut, just do nothing */

namespace ai
{
  namespace Agent
  {
    ObstacleEnvironmentDisplay::ObstacleEnvironmentDisplay(Environment *env, int width_in, int height_in)
      : EnvironmentDisplay(env,width_in,height_in)
    {
    }
    ObstacleEnvironmentDisplay::~ObstacleEnvironmentDisplay()
    {
    }
    void ObstacleEnvironmentDisplay::Redraw(Environment *env)
    {
    }
  }
}
#endif
