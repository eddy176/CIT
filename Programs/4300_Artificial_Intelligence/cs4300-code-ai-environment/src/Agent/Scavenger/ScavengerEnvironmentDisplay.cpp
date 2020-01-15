#include <ai_scavenger.h>
#include <ai_glut.h>
#include <cstdio>

#if USE_GLUT

// Windows headers have DrawText() macro defined somewhere.
#ifdef DrawText
#undef DrawText
#endif

namespace ai
{
  namespace Scavenger
  {
    static EnvironmentDisplay *ed = 0;
    static void display()
    {
      ed->Redraw(ed->GetEnv());
    }

    static GLfloat plainMaterial[] = {0.1f, 0.6f, 0.1f, 1.0f};
    static GLfloat rocksMaterial[] = {0.1f, 0.4f, 0.4f, 1.0f};
    static GLfloat mudMaterial[]   = {0.4f, 0.2f, 0.1f, 1.0f};
    static GLfloat iceMaterial[]   = {0.9f, 0.9f, 0.9f, 1.0f};
    static GLfloat wallMaterial[]  = {0.1f, 0.1f, 0.1f, 1.0f};
    static GLfloat cliffMaterial[] = {0.5f, 0.5f, 0.1f, 1.0f};
    static GLfloat agentMaterials[][4] = { { 1.0f, 0.0f, 0.0f, 1.0f },
                                           { 0.0f, 0.5f, 0.0f, 1.0f },
                                           { 0.0f, 0.0f, 1.0f, 1.0f },
                                           { 1.0f, 0.0f, 1.0f, 1.0f },
                                           { 1.0f, 0.5f, 0.0f, 1.0f },
                                           { 0.0f, 1.0f, 1.0f, 1.0f },
                                           { 1.0f, 1.0f, 1.0f, 1.0f } };
    static const unsigned int maxAgentMaterials = sizeof(agentMaterials)/sizeof(agentMaterials[0]);
    static std::map<std::string, GLfloat *> interface_material;
    static double interface_offset[][6] =
      {
        {-1,  1,  1,  1,  0, -1 },
        {-1, -1,  1, -1,  0,  1 },
        { 1,  1,  1, -1, -1,  0 },
        {-1,  1, -1, -1,  1,  0 }
      };

    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env,
                                           int width_in, int height_in)
      : ai::Agent::EnvironmentDisplay(env, width_in, height_in),
        m_width_orig(width_in), m_height_orig(height_in)
    {
      ed = this;
      glutDisplayFunc(display);

      interface_material["plain"] = plainMaterial;
      interface_material["rocks"] = rocksMaterial;
      interface_material["mud"]   = mudMaterial;
      interface_material["ice"]   = iceMaterial;
      interface_material["wall"]  = wallMaterial;
      interface_material["cliff"] = cliffMaterial;

      ResetParameters();

      glutMainLoopEvent();
    }

    EnvironmentDisplay::~EnvironmentDisplay()
    {
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


    void EnvironmentDisplay::Redraw(ai::Agent::Environment *env)
    {
      ResetParameters();
      if(!env) { std::fprintf(stderr, "Scavenger::EnvironmentDisplay.Redraw(env=%p)\n", env); return; }
      Environment *sw_env = dynamic_cast<Environment *>(env);
      double x0, y0;
      Location location;

      //GLfloat whiteMaterial[] = {1.0, 1.0, 1.0, 1.0};
      GLfloat goalMaterial[]  = {1.0, 0.0, 1.0, 1.0};
      //GLfloat redMaterial[]   = {1.0, 0.0, 0.0, 1.0};
      GLfloat blackMaterial[] = {0.0, 0.0, 0.0, 1.0};

      glutSetWindow(window);
      glViewport(0, 0, width, height);

      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);
      glMatrixMode(GL_MODELVIEW);

      // redraw
      glClear(GL_COLOR_BUFFER_BIT);

      std::map<Location, Cell *>::iterator it;
      for(it = sw_env->cells.begin(); it != sw_env->cells.end(); it++)
        {
          if(it->second == 0)
            {
              DBGP_E(LOG_STREAM(std::cerr) << "Bad Cell pointer: " << it->first << " " << it->second << std::endl);
              continue;
            }
          location = it->second->GetLocation();
          x0 = (location.GetX() - minx) + spanx/2.;
          y0 = (location.GetY() - miny) + spany/2.;

          if(1)
            {
              GLfloat elevationMaterial[4] = { 0.0, 0.0, 0.0, 1.0 };
              //GLfloat visitedMaterial[4] = { 0.0, 0.0, 0.0, 1.0 };

              double x1 = ((location.GetX() - minx)) * scale;
              double y1 = height - ((location.GetY() - miny)) * scale;
              double x2 = ((location.GetX() - minx) + spanx)*scale;
              double y2 = height - ((location.GetY() - miny) + spany)*scale;
              DBGP_DPY(LOG_STREAM(std::cerr)
                       << "x1("<<x1<<") = (lx("<<location.GetX()<<") - minx("<<minx<<")) * scale("<<scale<<")" << std::endl);
              DBGP_DPY(LOG_STREAM(std::cerr)
                       << "x2("<<x1<<") = ((lx("<<location.GetX()<<") - minx("<<minx<<")) + spanx("<<spanx<<")) * scale("<<scale<<")" << std::endl);

              double dz = location.GetElevation() + 1000.;
              dz = dz/2000.;
              if(dz < 0.0) { dz = 0.; }
              if(dz > 1.0) { dz = 1.; }
              elevationMaterial[0] = (GLfloat)(1. - dz);
              elevationMaterial[1] = (GLfloat)(1. - dz);
              elevationMaterial[2] = (GLfloat)dz;

              SetColor(elevationMaterial);
              DrawRectangle((int) x1,
                            (int) y1,
                            (int) x2,
                            (int) y2);
              DBGP_DPY(LOG_STREAM(std::cerr)
                       << "DrawRectangle("
                       << x1 << ","
                       << y1 << ","
                       << x2 << ","
                       << y2 << ")"
                       << std::endl);
              unsigned int i;
              unsigned int color_index;
              unsigned int marks_index;
              int visited_marks[][4] =  { {(int)x1,(int)y1,(int)x2,(int)y2},               /* tl-br */
                                          {(int)x2,(int)y1,(int)x1,(int)y2},               /* tr-bl */
                                          {(int)(x1+x2)/2,(int)y1,(int)(x1+x2)/2,(int)y2}, /* t-b */
                                          {(int)x1,(int)(y1+y2)/2,(int)x2,(int)(y1+y2)/2}, /* l-r */
                                          {(int)(x1+x2)/2,(int)y1,(int)x2,(int)y2},
                                          {(int)x1,(int)y1,(int)(x1+x2)/2,(int)y2},
                                          {(int)x1,(int)y1,(int)x2,(int)(y1+y2)/2} };
              const unsigned int max_visited_marks = sizeof(visited_marks)/sizeof(visited_marks[0]);
              // visited marker
              for(i = 0; i < sw_env->agents_order.size(); i++)
                {
                  ai::Scavenger::Agent *agent = dynamic_cast<ai::Scavenger::Agent *>(sw_env->agents[sw_env->agents_order[i]]);
                  marks_index = color_index = agent->GetIndex();
                  if(color_index >= maxAgentMaterials) { color_index = maxAgentMaterials - 1; }
                  if(marks_index >= max_visited_marks) { marks_index = max_visited_marks - 1; }
                  SetColor(agentMaterials[color_index]);
                  int flag = 1 << agent->GetIndex();
                  if(flag & it->second->GetVisited())
                    {
                      DrawLine(visited_marks[marks_index][0],
                               visited_marks[marks_index][1],
                               visited_marks[marks_index][2],
                               visited_marks[marks_index][3]);
                    }
                }
            }
          /*
            SetColor(redMaterial);
            DrawBox((float)((x0-spanx/2)*scale), height - (float)((y0-spany/2.)*scale),
            (float)((x0+spanx/2)*scale), height - (float)((y0+spany/2.)*scale));
          */


          /*
            double p1 = 100;
            double p2 = 20;
          */

          double p1 = 100;
          double p2 = 10; // smaller numbers -> thicker lines

          int d;
          for(d = Location::NORTH; d <= Location::WEST; d++)
            {
              CellInterface ci = it->second->GetInterface((Location::Direction)d);
              GLfloat *material = interface_material[ci.GetTitle()];
              SetColor(material);

              DrawRectangle((int)((x0+interface_offset[d][0]*spanx/2.)*scale
                                  - (interface_offset[d][2]*spany/p1*scale)),

                            height - (int)((y0+interface_offset[d][1]*spany/2.)*scale
                                           - (interface_offset[d][3]*spany/p1*scale)),

                            (int)((x0+interface_offset[d][2]*spanx/2.)*scale
                                  + (interface_offset[d][4]*spanx/p2*scale)),

                            height -
                            (int)((y0+interface_offset[d][3]*spany/2.)*scale
                                  + (interface_offset[d][5]*spanx/p2*scale))
                            );

            }

          char  buf[128];
          if(0)
            {
              if(0)
                {
                  std::sprintf(buf, "%.0f,%.0f,%.0f",
                               location.GetX(),
                               location.GetY(),
                               location.GetElevation());
                  SetColor(blackMaterial);
                  myDrawText((float)((x0-spanx/3.)*scale), (float)(height - ((y0+spany/3.)*scale)), buf);
                }
              if(1)
                {
                  std::sprintf(buf, "%u",
                               it->second->GetId());
                  SetColor(blackMaterial);
                  myDrawText((float)((x0-spanx/3.)*scale), (float)(height - ((y0+spany/3.)*scale)+15), buf);
                }
              if(0)
                {
                  std::string obj_str = "";
                  std::map<unsigned int, unsigned int> &objs = it->second->GetObjects();
                  for(auto oit = objs.begin(); oit != objs.end(); oit++)
                    {
                      obj_str += dynamic_cast<Object *>(sw_env->objects[oit->second])->GetShortName();
                      obj_str += " ";
                    }
                  if(objs.size() > 0)
                    {
                      SetColor(blackMaterial);
                      myDrawText((float)((x0-spanx/3.)*scale), (float)(height - ((y0+spany/3.)*scale)+30), obj_str.c_str());
                    }
                }
            }
          else
            {
              std::map<unsigned int, unsigned int> &objs = it->second->GetObjects();
              if(objs.size() > 0)
                {
                  std::sprintf(buf, "%zd",
                               objs.size());
                  SetColor(blackMaterial);
                  myDrawText((float)((x0-spanx/3.)*scale)+3, (float)(height - ((y0+spany/3.)*scale)+8), buf);
                }
            }
        }

      unsigned int i;
      unsigned int color_index;
      double fraction;
      for(i = 0; i < sw_env->agents_order.size(); i++)
        {
          ai::Scavenger::Agent *agent = dynamic_cast<ai::Scavenger::Agent *>(sw_env->agents[sw_env->agents_order[i]]);
          fraction = ((double)agent->GetIndex()+2)/(sw_env->agents_order.size()+2);
          location = *(dynamic_cast<Location *>(agent->GetLocation()));
          x0 = (location.GetX() - minx) + fraction*spanx;
          y0 = (location.GetY() - miny) + fraction*spany;

          color_index = agent->GetIndex();
          if(color_index >= maxAgentMaterials) { color_index = maxAgentMaterials - 1; }
          SetColor(agentMaterials[color_index]);
          DrawCircle((float)(x0*scale), (float)(height - y0*scale), (float)(100.*scale));
        }

      i = 0;
      for(auto bit = sw_env->bases.begin(); bit != sw_env->bases.end(); bit++, i++)
        {
          fraction = ((double)i+2)/(sw_env->bases.size()+2);
          //DBGP_DPY(LOG_STREAM(std::cerr) << "fraction("<<fraction<<") = (i("<<i<<") + 2("<<2<<")) / ( bases.size()("<<sw_env->bases.size()<<")+2("<<2<<"))" << std::endl);
          location = sw_env->cells_by_id[bit->second->GetCell()]->GetLocation();
          x0 = (location.GetX() - minx) + fraction*spanx;
          y0 = (location.GetY() - miny) + fraction*spany;
          //DBGP_DPY(LOG_STREAM(std::cerr) << "x0("<<x0<<") = (lx("<<location.GetX()<<") - minx("<<minx<<")) + fraction("<<fraction<<")*spanx("<<spanx<<")" << std::endl);

          SetColor(blackMaterial);
          DrawCircle((float)(x0*scale), (float)(height - y0*scale), (float)(50.*scale));

          /*
            Agent * agent = sw_env->bases[i]->GetAgent();
            if(agent)
            {
            char buf[128];
            location = *(dynamic_cast<Location *>(agent->GetLocation()));
            std::sprintf(buf, "%.0f,%.0f,%.0f",
            location.GetX(),
            location.GetY(),
            location.GetElevation());
            SetColor(blackMaterial);
            myDrawText((float)((x0+spanx/2.)*scale), (float)(height - (y0)*scale), buf);

            std::sprintf(buf, "CH: %.1f  HP: %.1f",
            agent->GetCharge(),
            agent->GetHitPoints());
            myDrawText((float)((x0+spanx/2.)*scale), (float)(height - (y0-spany/2.)*scale), buf);

            }
          */
        }

      if(sw_env->fully_observable)
        {
          location = sw_env->cells_by_id[sw_env->goal_cell_id]->GetLocation();
          x0 = (location.GetX() - minx) + spanx/2.;
          y0 = (location.GetY() - miny) + spany/2.;

          SetColor(goalMaterial);
          DrawCircle((float)(x0*scale), (float)(height - y0*scale), (float)(50.*scale));
        }


      glutSwapBuffers();
    }

    void EnvironmentDisplay::ResetParameters()
    {
      Environment *sw_env = dynamic_cast<Environment *>(env_cache);
      std::map<Location, Cell *>::iterator it;

      minx = miny = 1e12;
      maxx = maxy = -minx;

      spanx = 0.;
      spany = 0.;

      for(it = sw_env->cells.begin(); it != sw_env->cells.end(); it++)
        {
          if(it->second == 0)
            {
              std::cerr << "bad pointer" << std::endl;
              continue;
            }
          Location location = it->second->GetLocation();
          Cell     *cell_x  = sw_env->cells_by_id[it->second->GetNeighborId(Location::WEST)];
          Cell     *cell_y  = sw_env->cells_by_id[it->second->GetNeighborId(Location::SOUTH)];
          if(cell_x && spanx == 0.)
            {
              Location l2 = cell_x->GetLocation();
              spanx = location.GetX() - l2.GetX();
            }
          if(cell_y && spany == 0.)
            {
              Location l2 = cell_y->GetLocation();
              spany = location.GetY() - l2.GetY();
            }

          if(location.GetX() < minx)
            {
              minx = location.GetX();
            }
          if(location.GetX() > maxx)
            {
              maxx = location.GetX();
            }
          if(location.GetY() < miny)
            {
              miny = location.GetY();
            }
          if(location.GetY() > maxy)
            {
              maxy = location.GetY();
            }
        }
      double dx = (maxx-minx) + spanx;
      double dy = (maxy-miny) + spany;

      double s1 = m_width_orig/dx;
      double s2 = m_height_orig/dy;
      scale = s1 < s2 ? s1 : s2;

      width  = (int)(dx*scale);
      height = (int)(dy*scale);
      glutReshapeWindow(width, height);

    }


  }
}
#else /* no glut, just do nothing */

namespace ai {
	namespace Scavenger {
		EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in) : ai::Agent::EnvironmentDisplay(env,width_in,height_in) {
		}
		EnvironmentDisplay::~EnvironmentDisplay() {
		}
		void EnvironmentDisplay::Redraw(ai::Agent::Environment *env) {
		}
	}
}
#endif
