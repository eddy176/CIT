#include <ai_ultimatetictactoe.h>

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
  namespace UltimateTicTacToe
  {
    enum
      {
        P_BLACK = 0,
        P_GREY  = 1,
        P_WHITE = 2,
        P_GREEN = 3
      };
    static float pen_colors[][4] =
      {
        {0.f, 0.f, 0.f, 1.f}, // black
        {.7f, .7f, .7f, 1.f}, // grey
        {1.f, 1.f, 1.f, 1.f}, // white
        {0.0f, 1.0f, 0.0f, 1.0f}, // green
      };

    static float player_colors[][7] =
      {
        // cell marks
        {0, 0, 0, 1}, // no mark
        {1, 0, 0, 1}, // X
        {0, 0, 1, 1}, // O
        // sub boards
        {0.3, 0.3, 0.3, 1.0}, // no mark  
        {1.0, 0.5, 0.5, 1.0}, // X
        {0.5, 0.5, 1.0, 1.0}, // O
        // full board
        {0.7, 0.7, 0.7, 1.0}, // no mark  
        {1.0, 0.8, 0.8, 1.0}, // X
        {0.7, 0.8, 1.0, 1.0}  // O
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

      SetColor(pen_colors[P_GREEN]);
      int ii, jj;
      float xmin, xmax, ymin, ymax, gapx, gapy;
      gapx = this->width/9.;
      gapy = this->height/9.;
      for( ii = 0; ii < 3; ii++ ) {
        for( jj = 0; jj < 3; jj++ ) {

          xmin = (this->width/3.)*jj;
          xmax = (this->width/3.)*(jj+1);
          ymin = (this->height/3.)*ii;
          ymax = (this->height/3.)*(ii+1);

          DrawLine(xmin+gapx, ymin, xmin+gapx, ymax);
          DrawLine(xmin+2*gapx, ymin, xmin+2*gapx, ymax);
          
          DrawLine(xmin, ymin+gapy, xmax, ymin+gapy);
          DrawLine(xmin, ymin+2*gapy, xmax, ymin+2*gapy);
        }
      }

    }

    void EnvironmentDisplay::DrawNoughtsAndCrosses(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);
      const BoardData &board = env->game_board.GetBoard();
      int x, y, xx, yy;
      float fx, fy, radius;
      float xmin, ymin, gapx, gapy;
      gapx = this->width/9.;
      gapy = this->height/9.;

      radius = this->height/25.;
      if(radius > this->width/25.) {
        radius = this->width/25.;
      }

      /* Draw Player's Marks */
      for( yy = 0; yy < 3; yy++ ) {
        for( xx = 0; xx < 3; xx++ ) {

          xmin = (this->width/3.)*xx;
          ymin = (this->height/3.)*yy;

          for(y = 0; y < 3; y++) {
            fy = ymin + gapy * (y + .5);
            
            for(x = 0; x < 3; x++) {
              fx = xmin + gapx * (x + .5);
              if(board.grid[yy][xx].grid[y][x] > 0) {
                SetColor(player_colors[board.grid[yy][xx].grid[y][x]]);
                switch(board.grid[yy][xx].grid[y][x]) {
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
      }
    }

    void EnvironmentDisplay::DrawWins(ai::Agent::Environment *env_in) {
      Environment *env = dynamic_cast<Environment *>(env_in);
      const BoardData &board = env->game_board.GetBoard();
      int xx, yy;
      float xmin, xmax, ymin, ymax;
      float gapx = (this->width/3.) * 0.05;
      float gapy = (this->height/3.) * 0.05;

      /* Draw Completed SubBoard's Marks */
      for( yy = 0; yy < 3; yy++ ) {
        for( xx = 0; xx < 3; xx++ ) {
          if( board.grid[yy][xx].Complete( ) ) {
            int draw_rectangle = 1;
            WinReasonEnum reason = WIN_NONE;
            if( board.grid[yy][xx].Winner( 1 ) ) {
              SetColor( player_colors[ 1 + 3 ] );
              reason = board.grid[yy][xx].FindPlayerWin( 1 );
            } else if( board.grid[yy][xx].Winner( 2 ) ) {
              SetColor( player_colors[ 2 + 3 ] );
              reason = board.grid[yy][xx].FindPlayerWin( 2 );
            } else {
              SetColor( player_colors[ 0 + 3 ] );
            }
            
            xmin = (this->width/3.)*xx + gapx;
            xmax = (this->width/3.)*(xx+1) - gapx;
            ymin = (this->height/3.)*yy + gapy;
            ymax = (this->height/3.)*(yy+1) - gapy;

            switch( reason ) {
            case WIN_ROW_0:
              ymin = (this->height/3.)*(yy+0./3.) + gapy;
              ymax = (this->height/3.)*(yy+1./3.) - gapy;
              draw_rectangle = 1;
              break;
            case WIN_ROW_1:
              ymin = (this->height/3.)*(yy+1./3.) + gapy;
              ymax = (this->height/3.)*(yy+2./3.) - gapy;
              draw_rectangle = 1;
              break;
            case WIN_ROW_2:
              ymin = (this->height/3.)*(yy+2./3.) + gapy;
              ymax = (this->height/3.)*(yy+3./3.) - gapy;
              draw_rectangle = 1;
              break;
            case WIN_COLUMN_0:
              xmin = (this->width/3.)*(xx+0./3.) + gapx;
              xmax = (this->width/3.)*(xx+1./3.) - gapx;
              draw_rectangle = 1;
              break;
            case WIN_COLUMN_1:
              xmin = (this->width/3.)*(xx+1./3.) + gapx;
              xmax = (this->width/3.)*(xx+2./3.) - gapx;
              draw_rectangle = 1;
              break;
            case WIN_COLUMN_2:
              xmin = (this->width/3.)*(xx+2./3.) + gapx;
              xmax = (this->width/3.)*(xx+3./3.) - gapx;
              draw_rectangle = 1;
              break;
            case WIN_DIAGONAL_0:
              xmin = (this->width/3.)*(xx+1./6.) + gapx;
              xmax = (this->width/3.)*(xx+5./6.) - gapx;
              ymin = (this->height/3.)*(yy+1./6.) + gapy;
              ymax = (this->height/3.)*(yy+5./6.) - gapy;
              draw_rectangle = 2;
              break;
            case WIN_DIAGONAL_1:
              xmin = (this->width/3.)*(xx+5./6.) - gapx;
              xmax = (this->width/3.)*(xx+1./6.) + gapx;
              ymin = (this->height/3.)*(yy+5./6.) - gapy;
              ymax = (this->height/3.)*(yy+1./6.) + gapy;
              draw_rectangle = 2;
              break;
            case WIN_NONE:
              draw_rectangle = 1;
              break;
            }
            if( draw_rectangle == 1 ) {
              DrawRectangle( xmin, ymin, xmax, ymax );
            } else if( draw_rectangle == 2 ) {
              DrawRotatedRectangle( (this->width/3.)*(xx) + gapx, ymin,     // 1
                                    xmin, (this->height/3.)*(yy) + gapy,    // 2
                                    xmax, (this->height/3.)*(yy+1) - gapy,  // 3
                                    (this->width/3.)*(xx+1) - gapx, ymax ); // 4
            }
            
          }
        }
      }
      
    }

    void EnvironmentDisplay::DrawWin(ai::Agent::Environment *env_in) {
      Environment *env = dynamic_cast<Environment *>(env_in);
      const BoardData &board = env->game_board.GetBoard();
      float xmin, xmax, ymin, ymax;
      float gapx = (this->width/3.) * 0.05;
      float gapy = (this->height/3.) * 0.05;


      /* Draw Completed Board's Marks */
      if( board.Complete( ) ) {
        int draw_rectangle = 1;
        WinReasonEnum reason = WIN_NONE;
        if( board.Winner( 1 ) ) {
          SetColor( player_colors[ 1 + 6 ] );
          reason = board.FindPlayerWin( 1 );
        } else if( board.Winner( 2 ) ) {
          SetColor( player_colors[ 2 + 6 ] );
          reason = board.FindPlayerWin( 2 );
        } else {
          SetColor( player_colors[ 0 + 6 ] );
        }
        
        xmin = gapx;
        xmax = this->width - gapx;
        ymin = gapy;
        ymax = this->height - gapy;

        switch( reason ) {
        case WIN_ROW_0:
          ymin = (this->height/3.)*(0.) + gapy;
          ymax = (this->height/3.)*(1.) - gapy;
          draw_rectangle = 1;
          break;
        case WIN_ROW_1:
          ymin = (this->height/3.)*(1.) + gapy;
          ymax = (this->height/3.)*(2.) - gapy;
          draw_rectangle = 1;
          break;
        case WIN_ROW_2:
          ymin = (this->height/3.)*(2.) + gapy;
          ymax = (this->height/3.)*(3.) - gapy;
          draw_rectangle = 1;
          break;
          
        case WIN_COLUMN_0:
          xmin = (this->width/3.)*(0.) + gapx;
          xmax = (this->width/3.)*(1.) - gapx;
          draw_rectangle = 1;
          break;
        case WIN_COLUMN_1:
          xmin = (this->width/3.)*(1.) + gapx;
          xmax = (this->width/3.)*(2.) - gapx;
          draw_rectangle = 1;
          break;
        case WIN_COLUMN_2:
          xmin = (this->width/3.)*(2.) + gapx;
          xmax = (this->width/3.)*(3.) - gapx;
          draw_rectangle = 1;
          break;
          
        case WIN_DIAGONAL_0:
          xmin = (this->width/3.)*(0+3./6.) + gapx;
          xmax = (this->width/3.)*(2+3./6.) - gapx;
          ymin = (this->height/3.)*(0+3./6.) + gapy;
          ymax = (this->height/3.)*(2+3./6.) - gapy;
          draw_rectangle = 2;
          break;
        case WIN_DIAGONAL_1:
          xmin = (this->width/3.)*(2+3./6.) - gapx;
          xmax = (this->width/3.)*(0+3./6.) + gapx;
          ymin = (this->height/3.)*(2+3./6.) - gapy;
          ymax = (this->height/3.)*(0+3./6.) + gapy;
          draw_rectangle = 2;
          break;
        case WIN_NONE:
          draw_rectangle = 1;
          break;
        }
        if( draw_rectangle == 1 ) {
          DrawRectangle( xmin, ymin, xmax, ymax );
        } else if( draw_rectangle == 2 ) {
          DrawRotatedRectangle( (this->width/3.)*(0) + gapx, ymin,     // 1
                                xmin, (this->height/3.)*(0) + gapy,    // 2
                                xmax, (this->height/3.)*(3) - gapy,  // 3
                                (this->width/3.)*(3) - gapx, ymax ); // 4
        }
      }
    }

    void EnvironmentDisplay::DrawLastMoves(ai::Agent::Environment *env_in)
    {
      Environment *env = dynamic_cast<Environment *>(env_in);

      const std::vector<MoveData> & last_moves = env->game_board.GetLastMoves();
      unsigned int i;
      float fx, fy, radius;
      float xmin, ymin, gapx, gapy;
      gapx = this->width/9.;
      gapy = this->height/9.;

      radius = this->height/25.;
      if(radius > this->width/25.)
        {
          radius = this->width/25.;
        }
      for(i=0; i<last_moves.size(); i++)
        {
          DBGP_L(LOG_STREAM(std::cerr) 
                 << "i: " << i
                 << "  last_moves[i]: " << last_moves[i]
                 << "  radius: " << radius
                 << std::endl);
          if(last_moves[i].pos_x >= 0)
            {
              xmin = (this->width/3.)*last_moves[i].board_x;
              ymin = (this->height/3.)*last_moves[i].board_y;

              fy = ymin + gapy * (last_moves[i].pos_y + .5);
              fx = xmin + gapx * (last_moves[i].pos_x + .5);
              
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

      DrawWin(env);
      DrawWins(env);
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
  namespace UltimateTicTacToe
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
