#include <ai_candy.h>
#include <ai_glut.h>
#include <cstdio>

#ifdef USE_GLUT

// Windows headers have DrawText() macro defined somewhere.
#ifdef DrawText
#undef DrawText
#endif

namespace ai
{
  namespace Candy
  {

    static EnvironmentDisplay *ed = 0;
    static void display()
    {
      ed->Redraw(ed->GetEnv());
    }

    static GLfloat textMaterial[] = {0.0f, 0.0f, 0.0f, 1.0f};
    static GLfloat backgroundMaterial[] = {1.0f, 1.0f, 1.0f, 1.0f};

    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env_in, int width_in, int height_in)
      : ai::Agent::EnvironmentDisplay(env_in, width_in, height_in)
    {
      ed = this;
      glutDisplayFunc(display);

      this->width   = width_in;
      this->height  = height_in;
      glutReshapeWindow(this->width, this->height);
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


    void EnvironmentDisplay::Redraw(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);

      glutSetWindow(this->window);
      glViewport(0, 0, this->width, this->height);

      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, this->width, this->height, 0);
      glMatrixMode(GL_MODELVIEW);

      // redraw
      glClear(GL_COLOR_BUFFER_BIT);

      // background
      this->SetColor(backgroundMaterial);
      this->DrawRectangle(0, 0, this->width, this->height);

      this->SetColor(textMaterial);

      // environment stats
      float dy = 15;
      float x0 = 10., y0 = 20.;
      char buf[128];
      int i;
      for(i = 0; i < env->num_flavors; i++)
        {
          std::sprintf(buf, "%d:  %d", i, env->flavor_history[i]);
          myDrawText(x0, y0, buf);
          y0 += dy;
        }
      y0 += dy;

      float x1, y1;
      size_t j;
      float dx = float(this->width - 2*x0) / env->agents_order.size();
      x1 = x0;
      for(j = 0; j < env->agents_order.size(); j++)
        {
          std::stringstream buf;
          Agent * agent = dynamic_cast<Agent *>(env->agents[env->agents_order[j]]);
          y1 = y0;

          buf.str(""); buf.clear();
          buf << "Agent " << j;
          myDrawText(x1, y1, buf.str().c_str());
          y1 += dy;

          buf.str(""); buf.clear();
          buf << "Total Error " << agent->GetTotalError();
          myDrawText(x1, y1, buf.str().c_str());
          y1 += dy;

          buf.str(""); buf.clear();
          buf << "Smallest Error " << agent->GetSmallestError();
          myDrawText(x1, y1, buf.str().c_str());
          y1 += dy;

          if(agent->GetNumberOfPredictions() > 0)
            {
              buf.str(""); buf.clear();
              buf << "Average Error " << agent->GetTotalError() / agent->GetNumberOfPredictions();
              myDrawText(x1, y1, buf.str().c_str());
              y1 += dy;

              buf.str(""); buf.clear();
              buf << "Performance " << env->agents[env->agents_order[j]]->GetPerformance();
              myDrawText(x1, y1, buf.str().c_str());
              y1 += dy;
            }

          x1 += dx;
        }

      glutSwapBuffers();
    }

  }
}
#else /* no glut, just do nothing */

namespace ai {
	namespace Candy {
		EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in) : ai::Agent::EnvironmentDisplay(env,width_in,height_in) {
		}
		EnvironmentDisplay::~EnvironmentDisplay() {
		}
		void EnvironmentDisplay::Redraw(ai::Agent::Environment *env) {
		}
	}
}
#endif
