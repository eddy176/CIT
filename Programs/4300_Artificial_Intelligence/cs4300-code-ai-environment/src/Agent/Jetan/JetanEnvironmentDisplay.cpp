#include <ai_jetan.h>

#ifdef USE_GLUT

#include <ai_glut.h>
#include <typeinfo>
#include <cmath>
#include <cstdio>
#include <iomanip>

// Windows headers have DrawText() macro defined somewhere.
#ifdef DrawText
#undef DrawText
#endif

namespace ai
{
  namespace Jetan
  {
    enum
      {
        P_BLACK = 0,
        P_GREY  = 1,
        P_WHITE = 2,
        P_GREEN = 3,
        P_CHECKER_1 = 4,
        P_CHECKER_2 = 5,
        P_PLAYER_1_FG = 6,
        P_PLAYER_1_BG = 7,
        P_PLAYER_2_FG = 8,
        P_PLAYER_2_BG = 9,
        P_PLAYER_MAT = 10,
        P_LAST_MOVE = 11,
        P_ATTACK_COLOR = 12,
      };

    static float pen_colors[][4] =
      {
        {0.f, 0.f, 0.f, 1.f}, // black
        {.7f, .7f, .7f, 1.f}, // grey
        {1.f, 1.f, 1.f, 1.f}, // white
        {0.0f, 1.0f, 0.0f, 1.0f}, // green
        {1.0f, 0.518f, 0.012f, 1.0f}, // checker 1 ( orange )
        {0.0f, 0.0f, 0.0f, 1.0f}, // checker 2 ( black )

        {1.0f, 0.518f, 0.012f, 1.0f}, // player 1 foreground
        {1.0f, 1.0f, 1.0f, 1.0f}, // player 1 background

        {1.0f, 0.518f, 0.012f, 1.0f}, // player 2 foreground
        {0.0f, 0.0f, 0.0f, 1.0f}, // player 2 background

        {0.5f, 0.5f, 0.5f, 1.0f}, // player mat midground
        {0.5f, 0.259f, 0.006f, 1.0f}, // last move line

        {0.8f, 0.8f, 0.0f, 0.7f}, // attack color
      };

    static EnvironmentDisplay *ed = 0;

    static void keyboard(unsigned char key, int x, int y)
    {
      //std::cout << "key press" << std::endl;
      if((key == 27) || (key == 'q') || (key == 'Q'))
        {
          if(ed->GetEnv())
            {
              ed->Quit();
            }
          else 
            {
              std::cerr << "Error in keyboard():  ed->GetEnv() = " << ed->GetEnv() << std::endl;
            }
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

    /*
     * Use the top g_stats_height pixels to draw 
     * text/game stats information.
     * Use the biggest square that remains as the board, centering
     * it in the available area, giving each square 1/10 of the size.
     *
     * g_square_margin is the percent of the square to leave blank
     * on each side.
     */
    static float g_stats_height  = 100.0;
    static float g_square_margin = 0.10;
    static float g_last_move_margin = 0.10;
    static float g_labels_size  = 25.0;
    
    static void board_dimensions( float window_width, float window_height,
                                  float& board_x, float& board_y,
                                  float& board_size ) {
      window_height -= g_stats_height + 2*g_labels_size;
      window_width  -= 2*g_labels_size;
      board_size = window_height;
      if( window_width < board_size ) {
        board_size = window_width;
      }

      if( board_size < window_width ) {
        board_x = ( window_width - board_size ) / 2.0;
      } else {
        board_x = 0.0;
      }
      if( board_size < window_height ) {
        board_y = ( window_height - board_size ) / 2.0;
      } else {
        board_y = 0.0;
      }
      board_y += g_stats_height + g_labels_size;
      board_x += g_labels_size;
    }

    void EnvironmentDisplay::DrawStats( ai::Agent::Environment *env_in ) {
      Environment *env = dynamic_cast< Environment * >( env_in );
      const BoardData             &board = env->game_board.GetBoard( );
      const std::vector< double > &times = env->game_board.GetPlayerTimes( );
      int i;
      std::stringstream ss;
      float xoffset = this->width/25.;
      float yoffset = this->height/25.;
      float y_inc   = 16.0f;
      float y_loc   = y_inc + yoffset;
      float x_loc   = xoffset;

      //Total Moves
      SetColor( pen_colors[ P_BLACK ] );
      ss << "# of Moves: " << env->game_board.GetTotalMoves( );
      DrawText( x_loc, y_loc, ss.str( ).c_str( ) );
      ss.str( "" );
      ss.clear( );

      //Player Time
      for( i = 1; i <= 2; i++ ) {
        if( board.player_turn == i && i == 1 ) {
          SetColor( pen_colors[ P_PLAYER_1_BG ] );
        } else if( board.player_turn == i && i == 2 ) {
          SetColor( pen_colors[ P_PLAYER_2_BG ] );
        } else {
          SetColor( pen_colors[ P_WHITE ] );
        }
        DrawRectangle( x_loc, y_loc, x_loc + this->width, y_loc + y_inc );


        if( board.player_turn == i && i == 1 ) {
          SetColor( pen_colors[ P_PLAYER_1_FG ] );
        } else if( board.player_turn == i && i == 2 ) {
          SetColor( pen_colors[ P_PLAYER_2_FG ] );
        } else {
          SetColor( pen_colors[ P_BLACK ] );
        }
        ss << std::setfill( ' ' ) << std::setw( 10 ) 
           << env->agents[env->agents_order[i-1]]->GetName( )

           << " Time: "
           << std::setfill( '0' ) << std::setw( 2 )
           << ((int)times[i-1])/60 << ":"
           << ((int)times[i-1])%60 << "."
           << std::setfill( '0' ) << std::setw( 3 )
           << ((int)std::floor(1000.*times[i-1])) % 1000;

        ss << "   escaped: " << (int)board.used_escape[ i-1 ];

        y_loc += y_inc;
        DrawText( x_loc, y_loc, ss.str( ).c_str( ) );
        ss.str( "" );
        ss.clear( );
      }
    }
    
    void EnvironmentDisplay::DrawBoard( ai::Agent::Environment *env_in ) {
      float board_x, board_y, board_size;
      board_dimensions( this->width, this->height, board_x, board_y, board_size );
      float square_size = board_size / 10.0;

      float xmin, xmax, ymin, ymax;

      /* Draw the background color for the board (1/2 of the checkered
       * squares) */
      xmin = board_x;
      xmax = board_x + board_size;
      ymin = board_y;
      ymax = board_y + board_size;

      SetColor( pen_colors[ P_CHECKER_1 ] );
      DrawRectangle( xmin, ymin, xmax, ymax );
      
      /* Draw the foreground color for the board (the other 
       * 1/2 of the checkered squares) */
      SetColor( pen_colors[ P_CHECKER_2 ] );
      int row, column;
      for( row = 0; row < 10; row++ ) {
        for( column = row%2; column < 10; column+=2 ) {
          xmin = board_x + column*square_size;
          xmax = xmin + square_size;
          ymin = board_y + row*square_size;
          ymax = ymin + square_size;
          
          DrawRectangle( xmin, ymin, xmax, ymax );
        }
      }

      /* Draw row and column numbers
       */
      for( row = 0; row < 10; row++ ) {
        std::stringstream row_ss;
        row_ss << row;
        ymin = board_y + row*square_size;
        ymax = ymin + square_size;

        xmin = board_x - g_labels_size;
        xmax = board_x;
        DrawText( -4.5+(xmin + xmax)/2.0, 5.0+(ymin + ymax)/2.0, row_ss.str( ).c_str( ) );
        
        xmin = board_x + 10*square_size;
        xmax = board_x + 10*square_size + g_labels_size;
        DrawText( -4.5+(xmin + xmax)/2.0, 5.0+(ymin + ymax)/2.0, row_ss.str( ).c_str( ) );
      }

      for( column = 0; column < 10; column++ ) {
        std::stringstream row_ss;
        row_ss << column;
        xmin = board_x + column*square_size;
        xmax = xmin + square_size;

        ymin = board_y - g_labels_size;
        ymax = board_y;
        DrawText( -4.5+(xmin + xmax)/2.0, 5.0+(ymin + ymax)/2.0, row_ss.str( ).c_str( ) );

        ymin = board_y + 10*square_size;
        ymax = board_y + 10*square_size + g_labels_size;
        DrawText( -4.5+(xmin + xmax)/2.0, 5.0+(ymin + ymax)/2.0, row_ss.str( ).c_str( ) );
      }

      DrawAttackedSquares( env_in );
      
      /* Draw a border around the board */
      SetColor( pen_colors[ P_BLACK ] );
      glLineWidth( 1.0 );
      DrawBox( board_x, board_y, board_x + board_size, board_y + board_size );


      /* Draw pieces */
      Environment *env = dynamic_cast< Environment * >( env_in );
      const Board& game_board = env->GameBoard( );
      const BoardData& board = game_board.GetBoard( );

      int piece_count = 0;
      int piece;
      DBGP_DPY( LOG_STREAM(std::cerr) << "Piece Begin <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl );
      for( row = 0; row < 10; row++ ) {
        for( column = 0; column < 10; column++ ) {
          piece = board.squares[ row ][ column ];
          if( piece < 0 || piece >= 40 ) {
            continue;
          }
          const Piece& p = board.pieces[ piece ];

          if( !p.mAlive ) {
            continue;
          }
          
          piece_count += 1;
          xmin = board_x + column*square_size + square_size*g_square_margin;
          xmax = board_x + (column+1)*square_size - square_size*g_square_margin;
          ymin = board_y + row*square_size + square_size*g_square_margin;
          ymax = board_y + (row+1)*square_size - square_size*g_square_margin;

          DBGP_DPY( LOG_STREAM(std::cerr) 
                    << "Piece @" << column << "," << row << " i=" << piece
                    << " Near: " << (xmin+xmax)/2.0 << "," << (ymin+ymax)/2.0
                    << std::endl );


          SetColor( pen_colors[ P_PLAYER_MAT ] );
          DrawCircle( (xmin + xmax)/2.0, (ymin + ymax)/2.0,
                      (xmax - xmin)/2.0 );

          std::stringstream type_str;
          switch( p.mType ) {
          case Piece::WARRIOR:
            type_str << "W";
            break;
          case Piece::PADWAR:
            type_str << "P";
            break;
          case Piece::DWAR:
            type_str << "D";
            break;
          case Piece::FLIER:
            type_str << "F";
            break;
          case Piece::CHIEF:
            type_str << "C";
            break;
          case Piece::PRINCESS:
            type_str << "*";
            break;
          case Piece::THOAT:
            type_str << "T";
            break;
          case Piece::PANTHAN:
            type_str << "p";
            break;
          default:
            {
              std::stringstream ss;
              ss << "Unknown Jetan::Piece::TYPE ( ";
              ss << (int) p.mType;
              ss << " )";
              DBGP_E( LOG_STREAM(std::cerr) << ss.str( ) << std::endl );
            }
            break;
          }

          if( p.mPlayer == 1 ) {
            SetColor( pen_colors[ P_PLAYER_1_BG ] );
          } else {
            SetColor( pen_colors[ P_PLAYER_2_BG ] );
          }
          DrawCircle( (xmin + xmax)/2.0, (ymin + ymax)/2.0,
                      (xmax - xmin)/3.0 );

          if( p.mPlayer == 1 ) {
            SetColor( pen_colors[ P_PLAYER_1_FG ] );
          } else {
            SetColor( pen_colors[ P_PLAYER_2_FG ] );
          }
          DrawText( -4.5+(xmin + xmax)/2.0, 5.0+(ymin + ymax)/2.0, type_str.str( ).c_str( ) );
        }
      }
      DBGP_DPY( LOG_STREAM(std::cerr) << "Piece End   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl );
    }


    void EnvironmentDisplay::DrawAttackedSquares( ai::Agent::Environment *env_in ) {
      float xmin, xmax, ymin, ymax;

      float board_x, board_y, board_size;
      board_dimensions( this->width, this->height, board_x, board_y, board_size );
      float square_size = board_size / 10.0;

      Environment *env = dynamic_cast< Environment * >( env_in );
      const Board& game_board = env->GameBoard( );
      const BoardData& board = game_board.GetBoard( );
      SetOfBoardLocations attacked_locations;
      int other_player = ( board.player_turn == 1 ) ? 2 : 1;
      game_board.DetermineAttackedLocations( other_player, attacked_locations );

      int row, column;
      SetColor( pen_colors[ P_ATTACK_COLOR ] );
      for( row = 0; row < 10; row++ ) {
        for( column = 0; column < 10; column++ ) {
          BoardLocation destination( { (char)column, (char)row } );
          if( attacked_locations.count( destination ) > 0 ) {
            xmin = board_x + column*square_size;
            xmax = xmin + square_size;
            ymin = board_y + row*square_size;
            ymax = ymin + square_size;
            
            DrawRectangle( xmin, ymin, xmax, ymax );
          }
        }
      }

      
    }

    void EnvironmentDisplay::DrawLastMove( ai::Agent::Environment *env_in ) {
      float board_x, board_y, board_size;
      board_dimensions( this->width, this->height, board_x, board_y, board_size );
      float square_size = board_size / 10.0;

      Environment *env = dynamic_cast< Environment * >( env_in );
      const Board& game_board = env->GameBoard( );
      int i;
      for( i = 0; i < 2; i++ ) {
        const MoveData& md = game_board.GetLastMoves( )[ i ];
        if( md.piece.x < 0 ) {
          continue;
        }

        float x1 = board_x + ( md.piece.x + 0.5 ) * square_size;
        float y1 = board_y + ( md.piece.y + 0.5 ) * square_size;
        float x2 = board_x + ( md.piece.x + md.offset.dx + 0.5 ) * square_size;
        float y2 = board_y + ( md.piece.y + md.offset.dy + 0.5 ) * square_size;

        if( x1 < x2 ) {
          x1 += g_last_move_margin * square_size;
          x2 -= g_last_move_margin * square_size;
        } else if( x1 > x2 ) {
          x1 -= g_last_move_margin * square_size;
          x2 += g_last_move_margin * square_size;
        }
        if( y1 < y2 ) {
          y1 += g_last_move_margin * square_size;
          y2 -= g_last_move_margin * square_size;
        } else if( y1 > y2 ) {
          y1 -= g_last_move_margin * square_size;
          y2 += g_last_move_margin * square_size;
        }

        DBGP_DPY( LOG_STREAM(std::cerr) 
                  << "last_move[ " << i << " ] = " << md
                  << " x1,y1:x2,y2 = " << x1 << "," << y1 << ":" << x2 << "," << y2
                  << std::endl );

        glLineWidth( 3.0 );
        SetColor( pen_colors[ P_LAST_MOVE ] );
        DrawLine( x1, y1, x2, y2 );
      }
    }

    void EnvironmentDisplay::Redraw( ai::Agent::Environment *env ) {
      glViewport(0, 0, width, height);
      
      // go into 2D mode
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      // Set the world coordinates.
      gluOrtho2D(0, width, height, 0);
      glMatrixMode(GL_MODELVIEW);

      // start to redraw
      glClear(GL_COLOR_BUFFER_BIT);

      DrawBoard( env );
      DrawLastMove( env );
      DrawStats( env );

      glutSwapBuffers();
    }

    void EnvironmentDisplay::Quit( ) {
      glutLeaveMainLoop( );
      quit = true;
    }

    bool EnvironmentDisplay::GetQuit( ) const {
      return quit;
    }

    void EnvironmentDisplay::MainLoop( ) {
      glutMainLoop( );
    }
  }
}
#else /* no glut, just do nothing */

namespace ai
{
  namespace Jetan
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
