#include <ai_abalone.h>

#ifdef USE_GLUT

#include <ai_glut.h>
#include <typeinfo>
#include <cmath>
#include <cstdio>
#include <unistd.h>

// Windows headers have DrawText() macro defined somewhere.
#ifdef DrawText
#undef DrawText
#endif

namespace ai
{
  namespace Abalone
  {
    enum
      {
        P_BLACK = 0,
        P_GREY  = 1,
        P_WHITE = 2
      };
     
    static float pen_colors[][4] =
      {
        {0.f, 0.f, 0.f, 1.f}, // black
        {.7f, .7f, .7f, 1.f}, // grey
        {1.f, 1.f, 1.f, 1.f}, // white
      };

    static float player_colors[][4] =
      {
        {0, 0, 0, 1}, // no marble
        {1, 0, 0, 1}, // p1
        {0, 0, 1, 1}, // p2
        {0, 1, 0, 1}, // p3
        {1, 1, 0, 1}  // p4
      };

    static EnvironmentDisplay *ed = 0;

    static void keyboard(unsigned char key, int x, int y)
    {
      //std::cout << "key press" << std::endl;
      if((key == 27) || (key == 'q') || (key == 'Q'))
        {
          ed->Quit();
        }
    }

    static void display()
    {
      ed->Redraw(ed->GetEnv());
    }

    static void reshape(int width, int height)
    {
      ed->Redraw(ed->GetEnv());
    }

    static void visibility(int a)
    {
      ed->Redraw(ed->GetEnv());
    }

    static void overlay()
    {
      ed->Redraw(ed->GetEnv());
    }

    static void status(int a)
    {
      ed->Redraw(ed->GetEnv());
    }
	

    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in)
      : ai::Agent::EnvironmentDisplay(env, width_in, height_in)
    {
      //my_env = dynamic_cast<Environment *>(env);

      ed = this;
      quit = false;

      width  = width_in;
      height = height_in;

      glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

      glutDisplayFunc(display);
      glutKeyboardFunc(keyboard);
      glutReshapeFunc(reshape);
      glutVisibilityFunc(visibility);
      glutOverlayDisplayFunc(overlay);
      glutWindowStatusFunc(status);

      glutReshapeWindow(width, height);
      glutMainLoopEvent();

      glViewport(0, 0, width, height);

      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      // Set the world coordinates.
      const double margin = 1.0;
      gluOrtho2D(4-margin, 20+margin, 0-margin, 16+margin);
      glMatrixMode(GL_MODELVIEW);
    }

    EnvironmentDisplay::~EnvironmentDisplay()
    {
    }

    float EnvironmentDisplay::DrawConvertX(int x, int y)
    {
      return (float)(8+x-y*0.5); // centers about x=12
    }

    void EnvironmentDisplay::DrawGridLines()
    {
      int x, y;

      // lines
      SetColor(pen_colors[P_GREY]);
      for(x=0; x<11; x++)
        {
          for(y=0; y<11; y++)
            {
              DrawLine(DrawConvertX(x,y), (float)y, DrawConvertX(x+1,y),(float)y);
              DrawLine(DrawConvertX(x,y), (float)y, DrawConvertX(x,y+1),(float)y+1);
            }
        }

      // mark special intersections
      SetColor(pen_colors[P_BLACK]);
      DrawText(DrawConvertX(0,0)-1.2f,  (float)0,  (char *)"(0,0)");
      DrawText(DrawConvertX(0,5)-1.4f,  (float)5,  (char *)"(0,5)");
      DrawText(DrawConvertX(4,0)+.3f,   (float)0,  (char *)"(4,0)");
      DrawText(DrawConvertX(4,10)+.3f, (float)10, (char *)"(4,10)");
      //DrawText(DrawConvertX(10,4)+.3f, (float)10, (char *)"(10,4)");
    }

    void EnvironmentDisplay::DrawBoardLines(ai::Agent::Environment *env)
    {
      Environment *cc_env = dynamic_cast<Environment *>(env);
      const BasicBoard & game_board = cc_env->GameBoard();
      int x, y;
      int offset = 1;

      // draw lines connecting holes
      SetColor(pen_colors[P_BLACK]);
      for(x=0; x<11; x++)
        {
          for(y=0; y<11; y++)
            {
            	if (x <= 5) {
		          if(game_board.Usable(x,y) && game_board.Usable(x+1,y))
		            {
		              DrawLine(DrawConvertX(y,x), (float)x, DrawConvertX(y+1,x),(float)x);
		            }
		          if(game_board.Usable(x,y) && game_board.Usable(x+1,y+1))
		            {
		              DrawLine(DrawConvertX(y,x), (float)x, DrawConvertX(y+1,x+1),(float)x+1);
		            }
		          if(game_board.Usable(x,y) && game_board.Usable(x,y+1))
		            {
		              DrawLine(DrawConvertX(y,x), (float)x, DrawConvertX(y,x+1),(float)x+1);
		            }
                }
                else if (x > 5) {
		          if(game_board.Usable(x,y) && game_board.Usable(x+1,y))
		            {
		              DrawLine(DrawConvertX(y+offset,x), (float)x, DrawConvertX(y+offset+1,x),(float)x);
		            }
		          if(game_board.Usable(x,y) && game_board.Usable(x+1,y+1))
		            {
		              DrawLine(DrawConvertX(y+offset,x), (float)x, DrawConvertX(y+offset+1,x+1),(float)x+1);
		            }
		          if(game_board.Usable(x,y) && game_board.Usable(x,y+1))
		            {
		              DrawLine(DrawConvertX(y+offset,x), (float)x, DrawConvertX(y+offset,x+1),(float)x+1);
		            }
                }
            }
            if (x > 5) {
            	offset++;
			}
        }
    }

    void EnvironmentDisplay::DrawHolesAndMarbles(ai::Agent::Environment *env)
    {
      Environment *cc_env = dynamic_cast<Environment *>(env);

      int x, y;
      int offset = 1;
      const BoardData &board = cc_env->game_board.GetBoard();

      for(x=0; x<11; x++)
        {
          for(y=0; y<11; y++)
            {
              if(board.hole[x][y] >= 0)
                {
                	if (x <= 5) {
		              	SetColor(player_colors[board.hole[x][y]]);
		              	DrawCircle(DrawConvertX(y,x),(float)x,.2f);
		            }
		            else if (x > 5) {
		            	SetColor(player_colors[board.hole[x][y]]);
		              	DrawCircle(DrawConvertX(y+offset,x),(float)x,.2f);
		            }
                }
            }
            if (x > 5) {
            	offset++;
			}
        }
    }

    void EnvironmentDisplay::DrawLastMoves(ai::Agent::Environment *env)
    {
      Environment *cc_env = dynamic_cast<Environment *>(env);

      const std::vector<MoveData> & last_moves = cc_env->game_board.GetLastMoves();
      unsigned int i, j;
      for(i=0; i<last_moves.size(); i++)
        {
          for (j=0; j<last_moves.at(i).number; j++)
            {
          	  if(last_moves[i].from_x[j] >= 0)
		        {
		          SetColor(player_colors[i+1]);
		          DrawCircle(DrawConvertX(last_moves[i].from_x[j],last_moves[i].from_y[j]),(float)last_moves[i].from_y[j],.1f);

		          SetColor(pen_colors[P_WHITE]);
		          DrawCircle(DrawConvertX(last_moves[i].to_x[j],last_moves[i].to_y[j]),(float)last_moves[i].to_y[j],.1f);
		        }
            }
        }
    }

    void EnvironmentDisplay::DrawStats(ai::Agent::Environment *env)
    {
      Environment *cc_env = dynamic_cast<Environment *>(env);
      const BoardData           &board = cc_env->game_board.GetBoard();
      const std::vector<double> &times = cc_env->game_board.GetPlayerTimes();
      char buffer[100];
      int i;
      float xoffset = .25;
      float yoffset = .25;
      double h[6];

      //Total Moves
      SetColor(pen_colors[P_BLACK]);
      std::sprintf(buffer, "# of Moves: %d", cc_env->game_board.GetTotalMoves());
      DrawText(3+xoffset,16.0f+yoffset,buffer);

		/*
      //Total Time
      sprintf(buffer,"Total Time: %02i:%02i", GetGameTime()/60, GetGameTime()%60);
      text_output(3+xoffset,15.5f+yoffset,buffer);
		*/

      //Player Time
      for(i = 1; i <= board.num_players; i++)
        {
          if(board.player_turn == i)
            {
              SetColor(player_colors[i]);
            }
          else
            {
              SetColor(pen_colors[P_BLACK]);
            }
          sprintf(buffer,"%10s Time: %02i:%02i.%03d",
                  cc_env->agents[cc_env->agents_order[i-1]]->GetName().c_str(),
                  ((int)times[i-1])/60,
                  ((int)times[i-1])%60,
                  ((int)std::floor(1000.*times[i-1])) % 1000
                  );
          float y_loc = 15.25f - .5f*i + yoffset;
          DrawText(3+xoffset,y_loc,buffer);
        }


      // Player Score
      SetColor(pen_colors[P_BLACK]);
      for(i = 1; i <= board.num_players; i++)
        {
          h[i-1] = 0;

          sprintf(buffer,"%10s: %.3lf",
                  cc_env->agents[cc_env->agents_order[i-1]]->GetName().c_str(),
                  h[i-1]
                  );
          float y_loc = 4.f - .5f *i + yoffset;
          DrawText(3+xoffset,y_loc,buffer);
        }
      if(board.num_players == 2)
        {
          //Current Winner
          sprintf(buffer,"      Diff: %.3lf", h[0]-h[1]);
          float y_loc = .5f + yoffset;
          DrawText(3+xoffset,y_loc,buffer);
        }

		/*
      //pause
      if(theWorldPtr->GamePause)
      {
      sprintf(buffer,"      Paused");
      text_output(3+xoffset,.0f+yoffset,buffer);
      }
      */
    }

    void EnvironmentDisplay::Redraw(ai::Agent::Environment *env)
    {
      std::cout << "Drawing" << std::endl;
      if(!env) { std::fprintf(stderr, "Redraw NULL env\n"); return; }

      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

      DrawGridLines();
      DrawBoardLines(env);
      DrawHolesAndMarbles(env);
      DrawLastMoves(env);
      DrawStats(env);

      glutSwapBuffers();
    }

    void EnvironmentDisplay::Quit()
    {
      std::cout << "QUIT" << std::endl;
      glutLeaveMainLoop();
      quit = true;
    }
    bool EnvironmentDisplay::GetQuit() const
    {
      std::cout << "GET QUIT" << std::endl;
      return quit;
    }

    void EnvironmentDisplay::MainLoop()
    {
      std::cout << "glutMainLoop() start" << std::endl;
      glutMainLoop();
      std::cout << "glutMainLoop() end" << std::endl;
    }
  }
}
#else /* no glut, just do nothing */

namespace ai {
	namespace Abalone {
		EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in) : ai::Agent::EnvironmentDisplay(env,width_in,height_in) {
		}
		EnvironmentDisplay::~EnvironmentDisplay() {
		}
		void EnvironmentDisplay::Redraw(ai::Agent::Environment *env) {
		}
	}
}
#endif
