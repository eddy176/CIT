#include <ai_xy.h>

#ifdef USE_GLUT

#include <ai_glut.h>
#include <typeinfo>
#include <cmath>

namespace ai
{
  namespace XY
  {
    static EnvironmentDisplay *ed = 0;
    /*
      static void display()
      {
      ed->Redraw(ed->GetEnv());
      }
    */

    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in)
      : ai::Agent::EnvironmentDisplay(env, width_in, height_in, true)
    {
      DBGP_DPY(LOG_STREAM(std::cerr) << "Constructor Start" << std::endl);
      DBGP_DPY(LOG_STREAM(std::cerr) << "Width: " << width << " Height: " << height << std::endl);
      Environment *xy_env = dynamic_cast<Environment *>(env);

      ed = this;

      spacing = 100;
      width   = xy_env->width  * spacing;
      height  = xy_env->height * spacing;
      if(width < spacing) { width = spacing; }
      if(height < spacing) { height = spacing; }
      DBGP_DPY(LOG_STREAM(std::cerr) << "Width: " << width << " Height: " << height << std::endl);
      Init(width, height, (char *)"XY Environment");
      /*glutDisplayFunc(display);*/
      glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
      DBGP_DPY(LOG_STREAM(std::cerr) << "glutReshapeWindow()" << std::endl);
      glutReshapeWindow((int)width, (int)height);
      DBGP_DPY(LOG_STREAM(std::cerr) << "glutMainLoopEvent()" << std::endl);
      //glutMainLoopEvent();
      DBGP_DPY(LOG_STREAM(std::cerr) << "Width: " << width << " Height: " << height << std::endl);
      DBGP_DPY(LOG_STREAM(std::cerr) << "Constructor Done" << std::endl);
    }

    EnvironmentDisplay::~EnvironmentDisplay()
    {
    }

    void EnvironmentDisplay::Redraw(ai::Agent::Environment *env)
    {
      DBGP_DPY(LOG_STREAM(std::cerr) << "Redraw Start" << std::endl);
      Environment *xy_env = dynamic_cast<Environment *>(env);

      GLfloat whiteMaterial[]       = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat greenMaterial[]       = {0.1f, 0.7f, 0.4f, 1.0f};
      GLfloat brightGreenMaterial[] = {0.1f, 0.9f, 0.1f, 1.0f};
      GLfloat blueMaterial[]        = {0.1f, 0.2f, 0.7f, 1.0f};

      glViewport(0, 0, width, height);

      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);
      glMatrixMode(GL_MODELVIEW);

      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT);

      SetColor(whiteMaterial);

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
          if(dynamic_cast<Object*>(xy_env->objects[j]) != 0)
            {
              Location *xy_loc = dynamic_cast<Location *>(xy_env->objects[j]->GetLocation());
              int x = spacing*xy_loc->GetX() + spacing/2;
              int y = height - (spacing*xy_loc->GetY() + spacing/2);
              SetColor(blueMaterial);
              DrawCircle(x, y, spacing/3);
            }
        }
      for(j = 0; j < xy_env->agents.size(); j++)
        {
          if(dynamic_cast<Agent*>(xy_env->agents[j]) != 0)
            {
              Location *xy_loc = dynamic_cast<Location *>(xy_env->agents[j]->GetLocation());
              Agent *xy_agent = dynamic_cast<Agent *>(xy_env->agents[j]);

              int x = spacing*xy_loc->GetX() + spacing/2;
              int y = height - (spacing*xy_loc->GetY() + spacing/2);
              int dx = 0;
              int dy = 0;
              dx = (int)
                ((spacing/2)*cos(xy_agent->GetDirection()/180.*3.1415926535));
              dy = -(int)
                ((spacing/2)*sin(xy_agent->GetDirection()/180.*3.1415926535));
              SetColor(brightGreenMaterial);
              DrawLine(x, y, x+dx, y+dy);
              SetColor(greenMaterial);
              DrawCircle(x, y, spacing/4);
            }
        }

      DBGP_DPY(LOG_STREAM(std::cerr) << "glutSwapBuffers()" << std::endl);
      glutSwapBuffers();
      DBGP_DPY(LOG_STREAM(std::cerr) << "Redraw Done" << std::endl);
    }
  }
}
#else /* no glut, just do nothing */

namespace ai
{
  namespace XY
  {
    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in)
      : ai::Agent::EnvironmentDisplay(env,width_in,height_in)
    {
    }
    EnvironmentDisplay::~EnvironmentDisplay()
    {
    }
    void EnvironmentDisplay::Redraw(ai::Agent::Environment *env)
    {
    }
  }
}
#endif
