#include <ai_mancala.h>

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
  namespace Mancala
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
        {1, 0, 0, 1}, // player 1
        {0, 0, 1, 1}  // player 2
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

    void EnvironmentDisplay::DrawBoardOutline(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);
      const Board & game_board = env->GameBoard();
      const BoardData &b = game_board.GetBoard();

      float margin = 0.01;
      float w = 1./8.;
      float h = 1./4.;
      int i;
      char buffer[100];

      // Draw the bins of the board
      SetColor(pen_colors[P_BLACK]);
      DrawBox(margin, margin, w-margin, 2*h-margin);

      std::sprintf(buffer, "%2d", b.board[13]);
      SetColor(player_colors[2]);
      DrawText(2*margin, h, buffer);

      for(i = 1; i < 7; i++)
        {
          SetColor(pen_colors[P_BLACK]);
          DrawBox(i*w+margin, margin, (i+1)*w-margin, h-margin);
          std::sprintf(buffer, "%2d:%2d", i-1, b.board[i-1]);
          SetColor(player_colors[1]);
          DrawText(i*w+2*margin, h/2, buffer);

          SetColor(pen_colors[P_BLACK]);
          DrawBox(i*w+margin, h+margin, (i+1)*w-margin, 2*h-margin);
          std::sprintf(buffer, "%2d:%2d", 13-i, b.board[13-i]);
          SetColor(player_colors[2]);
          DrawText(i*w+2*margin, 3*h/2, buffer);
        }

      SetColor(pen_colors[P_BLACK]);
      DrawBox(7*w+margin, margin, 8*w-margin, 2*h-margin);
      std::sprintf(buffer, "%2d", b.board[6]);
      SetColor(player_colors[1]);
      DrawText(7*w+2*margin, h, buffer);

    }

    void EnvironmentDisplay::DrawBins(ai::Agent::Environment *env_in)
    {
      /*
        Environment *env = dynamic_cast<Environment *>(env_in);
        const BoardData &board = env->game_board.GetBoard();
      */
    }

    void EnvironmentDisplay::DrawLastMoves(ai::Agent::Environment *env_in)
    {
      /*
        Environment *env = dynamic_cast<Environment *>(env_in);
        const std::vector<MoveData> & last_moves = env->game_board.GetLastMoves();
      */
    }

    void EnvironmentDisplay::DrawStats(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);
      const BoardData           &board = env->game_board.GetBoard();
      const std::vector<double> &times = env->game_board.GetPlayerTimes();
      char buffer[100];
      int i;
      float xoffset = 1./16.;
      float yoffset = 15./16.;
      float y_inc   = -1./32.;
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
          sprintf(buffer,"%10s Time: %02i:%02i.%03d  Score: %d",
                  env->agents[env->agents_order[i-1]]->GetName().c_str(),
                  ((int)times[i-1])/60,
                  ((int)times[i-1])%60,
                  ((int)std::floor(1000.*times[i-1])) % 1000,
                  env->game_board.Score(i)
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
      gluOrtho2D(0., 1., 0., 1.);
      glMatrixMode(GL_MODELVIEW);

      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT);

      DrawBoardOutline(env);
      //DrawNoughtsAndCrosses(env);
      //DrawLastMoves(env);
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
  namespace Mancala
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
