#include <ai_tictactoe.h>

#ifdef USE_GLUT

#include <ai_glut.h>
#include <typeinfo>
#include <cmath>
#include <cstdio>

// Windows headers have DrawText() macro defined somewhere.
#ifdef DrawText
#undef DrawText
#endif

namespace ai
{
  namespace TicTacToe
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
        {0, 0, 0, 1}, // no mark
        {1, 0, 0, 1}, // X
        {0, 0, 1, 1}  // O
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
      if(ed->GetEnv())
        {
          ed->Redraw(ed->GetEnv());
        }
      else
        {
          std::cerr << "Error in display():  ed->GetEnv() = " << ed->GetEnv() << std::endl;
        }
    }


    EnvironmentDisplay::EnvironmentDisplay(ai::Agent::Environment *env, int width_in, int height_in)
      : ai::Agent::EnvironmentDisplay(env, width_in, height_in)
    {
      ed = this;
      quit = false;

      width  = width_in;
      height = height_in;

      glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

      glutDisplayFunc(display);
      glutKeyboardFunc(keyboard);

      glutReshapeWindow(width, height);
      glutMainLoopEvent();
    }

    EnvironmentDisplay::~EnvironmentDisplay()
    {
    }

    void EnvironmentDisplay::DrawBoardLines(ai::Agent::Environment *env_in)
    {
      /*
        Environment *env = dynamic_cast<Environment *>(env_in);
        const Board & game_board = env->GameBoard();
      */

      // draw lines of the board's hash
      SetColor(pen_colors[P_BLACK]);
      DrawLine(this->width/3, 0, this->width/3, this->height);
      DrawLine(2 * this->width/3, 0, 2 * this->width/3, this->height);
      DrawLine(0, this->height/3, this->width, this->height/3);
      DrawLine(0, 2 * this->height/3, this->width, 2 * this->height/3);
    }

    void EnvironmentDisplay::DrawNoughtsAndCrosses(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);
      const BoardData &board = env->game_board.GetBoard();
      int x, y;
      float fx, fy, radius;

      radius = this->height/10.;
      if(radius > this->width/10.)
        {
          radius = this->width/10.;
        }

      /* Draw Player's Marks */
      for(y = 0; y < 3; y++)
        {
          fy = (this->height / 3.) * (y + .5);
          for(x = 0; x < 3; x++)
            {
              fx = (this->width / 3.) * (x + .5);
              if(board.grid[y][x] > 0)
                {
                  SetColor(player_colors[board.grid[y][x]]);
                  switch(board.grid[y][x])
                    {
                    case 1:
                      DrawX(fx, fy, radius);
                      break;
                    case 2:
                      DrawO(fx, fy, radius);
                      break;
                    }
                }
            }
        }
    }

    void EnvironmentDisplay::DrawLastMoves(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);

      const std::vector<MoveData> & last_moves = env->game_board.GetLastMoves();
      unsigned int i;
      float fx, fy, radius;
      radius = this->height/25.;
      if(radius > this->width/25.)
        {
          radius = this->width/25.;
        }
      for(i=0; i<last_moves.size(); i++)
        {
          if(last_moves[i].pos_x >= 0)
            {
              fy = (this->height / 3.) * (last_moves[i].pos_y + .5);
              fx = (this->width / 3.) * (last_moves[i].pos_x + .5);

              SetColor(player_colors[i+1]);
              switch(i+1)
                {
                case 1:
                  DrawCircle(fx, fy, radius);
                  break;
                case 2:
                  DrawCircle(fx, fy, radius);
                  break;
                }
            }
        }
    }

    void EnvironmentDisplay::DrawStats(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);
      const BoardData           &board = env->game_board.GetBoard();
      const std::vector<double> &times = env->game_board.GetPlayerTimes();
      char buffer[100];
      int i;
      float xoffset = this->width/25.;
      float yoffset = this->height/25.;
      float y_inc   = 16.0f;
      float y_loc   = y_inc + yoffset;
      float x_loc   = xoffset;

      //Total Moves
      SetColor(pen_colors[P_BLACK]);
      std::sprintf(buffer, "# of Moves: %d", env->game_board.GetTotalMoves());
      DrawText(x_loc, y_loc, buffer);

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
                  env->agents[env->agents_order[i-1]]->GetName().c_str(),
                  ((int)times[i-1])/60,
                  ((int)times[i-1])%60,
                  ((int)std::floor(1000.*times[i-1])) % 1000
                  );
          y_loc += y_inc;
          DrawText(x_loc, y_loc, buffer);
        }
    }

    void EnvironmentDisplay::Redraw(ai::Agent::Environment *env)
    {
      glViewport(0, 0, width, height);

      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      // Set the world coordinates.
      gluOrtho2D(0, width, height, 0);
      glMatrixMode(GL_MODELVIEW);

      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT);

      DrawBoardLines(env);
      DrawNoughtsAndCrosses(env);
      DrawLastMoves(env);
      DrawStats(env);

      glutSwapBuffers();
    }

    void EnvironmentDisplay::Quit()
    {
      glutLeaveMainLoop();
      quit = true;
    }

    bool EnvironmentDisplay::GetQuit() const
    {
      return quit;
    }

    void EnvironmentDisplay::MainLoop()
    {
      glutMainLoop();
    }
  }
}
#else /* no glut, just do nothing */

namespace ai
{
  namespace TicTacToe
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
