#include <ai_wumpus.h>
#include <cstdio>

#ifdef USE_GLUT

#include <ai_glut.h>
#include <typeinfo>
#include <cmath>

namespace ai
{
  namespace Wumpus
  {
#include "wumpus.h"
#include "wumpus_dead.h"
#include "gold.h"
#include "pit.h"
#include "explorer_left.h"
#include "explorer_right.h"
#include "explorer_up.h"
#include "explorer_down.h"
#define  PIXEL_MODE GL_RGBA

    static EnvironmentDisplay *ed = 0;
    static void display()
    {
      if(ed->GetEnv())
        {
          ed->Redraw(ed->GetEnv());
        }
      else
        {
          std::cerr << "Error in display():  ed->GetEnv() = " << ed->GetEnv() << std::endl;
        }
    }

    static void myDrawText(float x, float y, const char *str)
    {
      void *font = GLUT_BITMAP_TIMES_ROMAN_10;
      int   i;
      int   len;

      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);

      glRasterPos2f(x, y);
      len = (int) strlen(str);
      for (i = 0; i < len; i++)
        {
          glutBitmapCharacter(font, str[i]);
        }

      glDisable(GL_BLEND);
    }

    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in)
      : ai::XY::EnvironmentDisplay(env, width_in, height_in)
    {
      DBGP_DPY(LOG_STREAM(std::cerr) << "Constructor Start" << std::endl);
      DBGP_DPY(LOG_STREAM(std::cerr) << "Width: " << width << " Height: " << height << std::endl);
      ed = this;
      glutDisplayFunc(display);
      DBGP_DPY(LOG_STREAM(std::cerr) << "Constructor Done" << std::endl);
    }

    EnvironmentDisplay::~EnvironmentDisplay()
    {
    }

    void EnvironmentDisplay::Redraw(ai::Agent::Environment *env)
    {

      DBGP_DPY(LOG_STREAM(std::cerr) << "Redraw Start" << std::endl);
      Environment *xy_env = dynamic_cast<Environment *>(env);
      {
        int tw = xy_env->width * spacing;
        int th = xy_env->height * spacing;
        if(tw != width || th != height)
          {
            width = tw;
            height = th;
            DBGP_DPY(LOG_STREAM(std::cerr) << "glutReshapeWindow()" << std::endl);
            glutReshapeWindow((int)width, (int)height);
          }
        if(width == 0 || height == 0) { return; }
      }

      GLfloat lineMaterial[]        = {.20f, .20f, .20f, 1.0f};
      GLfloat visitedMaterial[]     = {.80f, .80f, .80f, 1.0f};
      GLfloat blackMaterial[]       = {.00f, .00f, .00f, 1.0f};
      //GLfloat whiteMaterial[]       = {1.0f, 1.0f, 1.0f, 1.0f};
      GLfloat tardisMaterial[]      = {0.8f, 0.2f, 0.2f, 1.0f};
      /*
        GLfloat greenMaterial[]       = {0.1f, 0.7f, 0.4f, 1.0f};
        GLfloat brightGreenMaterial[] = {0.1f, 0.9f, 0.1f, 1.0f};
        GLfloat pitMaterial[]         = {0.1f, 0.1f, 0.1f, 1.0f};
        GLfloat goldMaterial[]        = {1.0f, 1.0f, 0.0f, 1.0f};
      */
      /*
        GLfloat wumpusMaterial[]      = {0.4f, 0.3f, 0.2f, 1.0f};
      */

      DBGP_DPY(LOG_STREAM(std::cerr) << "glViewPort(0, 0, "<<width<<", " << height<< ")" << std::endl);
      glViewport(0, 0, width, height);

      DBGP_DPY(LOG_STREAM(std::cerr) << "glMatrixMode()" << std::endl);
      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      // Set the world coordinates.
      gluOrtho2D(0, width, height, 0);
      glMatrixMode(GL_MODELVIEW);

      DBGP_DPY(LOG_STREAM(std::cerr) << "glEnable()" << std::endl);
      // allow transparency
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
      DBGP_DPY(LOG_STREAM(std::cerr) << "glClear()" << std::endl);
      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT);

      int i;
      int x, y;

      DBGP_DPY(LOG_STREAM(std::cerr) << "Drawing Visited" << std::endl);
      SetColor(visitedMaterial);
      for(x = 0; x < xy_env->width; x++)
        {
          for(y = 0; y < xy_env->height; y++)
            {
              if(xy_env->IsVisited(x, xy_env->height-y-1))
                {
                  DrawRectangle((x)*spacing, (y)*spacing, (x+1)*spacing, (y+1)*spacing);
                }
            }
        }

      DBGP_DPY(LOG_STREAM(std::cerr) << "Drawing Lines" << std::endl);
      SetColor(lineMaterial);
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

      DBGP_DPY(LOG_STREAM(std::cerr) << "Drawing Objects" << std::endl);
      DBGP_DPY(LOG_STREAM(std::cerr) << "Object size: " << xy_env->objects.size() << std::endl);
      for(auto oit = xy_env->objects.begin(); oit != xy_env->objects.end(); oit++)
        {
          DBGP_DPY(LOG_STREAM(std::cerr) << "Object loop body start 0." << std::endl);
          ai::Agent::Object *object = oit->second;
          DBGP_DPY(LOG_STREAM(std::cerr) << "Object loop body start 1. object: " << object << std::endl);
          ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(object->GetLocation());
          DBGP_DPY(LOG_STREAM(std::cerr) << "Object loop body start 2. xy_loc: " << xy_loc << std::endl);
          DBGP_DPY(LOG_STREAM(std::cerr) << "Object @" << xy_loc->GetX() << "," << xy_loc->GetY() << std::endl);
          if(typeid(*object) == typeid(PitObject))
            {
              int x = spacing*xy_loc->GetX() + spacing/2;
              int y = height - (spacing*xy_loc->GetY() + 2);

              glRasterPos2i(x, y);
              glDrawPixels(pit_width, pit_height,
                           PIXEL_MODE, GL_UNSIGNED_BYTE,
                           pit_data);

              /*
                SetColor(pitMaterial);
                DrawCircle(x, y, spacing/5);
              */
            }
          else if(typeid(*object) == typeid(GoldObject))
            {
              int x = spacing*xy_loc->GetX() + 2;
              int y = height - (spacing*xy_loc->GetY() + 2);

              glRasterPos2i(x, y);
              glDrawPixels(gold_width, gold_height,
                           PIXEL_MODE, GL_UNSIGNED_BYTE,
                           gold_data);

              /*
                SetColor(goldMaterial);
                DrawCircle(x, y, spacing/5);
              */
            }
          else if(typeid(*object) == typeid(WumpusObject))
            {
              int x = spacing*xy_loc->GetX() + 2;
              int y = height - (spacing*xy_loc->GetY() + spacing/2);

              glRasterPos2i(x, y);

              if(dynamic_cast<WumpusObject *>(object)->IsAlive())
                {
                  glDrawPixels(wumpus_width, wumpus_height,
                               PIXEL_MODE, GL_UNSIGNED_BYTE,
                               wumpus_data);
                }
              else
                {
                  glDrawPixels(wumpus_dead_width, wumpus_dead_height,
                               PIXEL_MODE, GL_UNSIGNED_BYTE,
                               wumpus_dead_data);
                }

              //SetColor(wumpusMaterial);
              //DrawCircle(x, y, spacing/5);
            }
          else if(typeid(*object) == typeid(TardisObject))
            {
              int x = spacing*xy_loc->GetX() + spacing/2;
              int y = height - (spacing*xy_loc->GetY() + spacing/2);

              SetColor(tardisMaterial);
              DrawCircle(x, y, spacing/5);
            }
        }
      DBGP_DPY(LOG_STREAM(std::cerr) << "Drawing Agents" << std::endl);
      for(auto ait = xy_env->agents.begin(); ait != xy_env->agents.end(); ait++)
        {
          ai::Agent::Agent *agent = ait->second;
          ai::XY::Location *xy_loc = dynamic_cast<ai::XY::Location *>(agent->GetLocation());
          if(typeid(*agent) == typeid(Agent))
            {
              Agent *wumpus_agent = dynamic_cast<Agent *>(agent);
              int x = spacing*xy_loc->GetX() + spacing/2;
              int y = height - (spacing*xy_loc->GetY() + spacing/2);

              glRasterPos2i(x, y);
              switch(wumpus_agent->GetDirection())
                {
                case 0:
                  glDrawPixels(explorer_right_width, explorer_right_height,
                               PIXEL_MODE, GL_UNSIGNED_BYTE,
                               explorer_right_data);
                  break;
                case 90:
                  glDrawPixels(explorer_up_width, explorer_up_height,
                               PIXEL_MODE, GL_UNSIGNED_BYTE,
                               explorer_up_data);
                  break;
                case 180:
                  glDrawPixels(explorer_left_width, explorer_left_height,
                               PIXEL_MODE, GL_UNSIGNED_BYTE,
                               explorer_left_data);
                  break;
                case 270:
                  glDrawPixels(explorer_down_width, explorer_down_height,
                               PIXEL_MODE, GL_UNSIGNED_BYTE,
                               explorer_down_data);
                  break;
                default:
                  std::cerr << "ERROR!" << std::endl;
                  break;
                }

              {
                char buf[256];
                SetColor(blackMaterial);
                std::sprintf(buf, "Arrow: %d", wumpus_agent->ArrowCount());
                myDrawText(x, y+11, buf);
                std::sprintf(buf, "Gold: %d", wumpus_agent->GoldCount());
                myDrawText(x, y+22, buf);
                if(wumpus_agent->GetYellLast())
                  {
                    std::sprintf(buf, "Yell: %d", wumpus_agent->GetYellLast());
                    myDrawText(x, y+33, buf);
                  }
              }

              /*
                int dx = 0;
                int dy = 0;
                dx = (int)
                ((spacing/4)*cos(xy_agent->GetDirection()/180.*3.1415926535));
                dy = -(int)
                ((spacing/4)*sin(xy_agent->GetDirection()/180.*3.1415926535));
                SetColor(brightGreenMaterial);
                DrawLine(x, y, x+dx, y+dy);
                SetColor(greenMaterial);
                DrawCircle(x, y, spacing/5);
              */
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
  namespace Wumpus
  {
    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in)
      : ai::XY::EnvironmentDisplay(env,width_in,height_in)
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
