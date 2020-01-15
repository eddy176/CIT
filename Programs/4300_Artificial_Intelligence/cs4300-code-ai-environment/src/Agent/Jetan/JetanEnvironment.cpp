#include <ai_jetan.h>
#include <sys/time.h>

namespace ai
{
  namespace Jetan
  {
    Environment::Environment()
    {
    }

    Environment::Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in)
      : ai::Agent::Environment(rand_in, displays_in),
      game_board(), mMaxPlayerTime(300.0)
    {
      game_board.SetMaxPlayerTime( mMaxPlayerTime );
    }

    Environment::~Environment()
    {
    }

    bool Environment::ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action)
    {
      switch(action->GetCode())
        {
        case Action::MOVE:
          {
            Action *a_action = dynamic_cast<Action *>(action);
            Agent  *a_agent  = dynamic_cast<Agent *>(agent);
            return game_board.Move(a_agent->GetPlayerNumber(),
                                   a_action->GetMove(),
                                   a_agent->GetDuration());
          }
          break;
        case Action::QUIT:
          {
            Agent  *a_agent  = dynamic_cast<Agent *>(agent);
            a_agent->Kill();
            return game_board.Quit(a_agent->GetPlayerNumber());
          }
          break;
        default:
          return false;
        }
      return true;
    }

    void Environment::CalculatePerformance(ai::Agent::Agent *agent)
    {
      //FIXME should set the score of the agent
    }

    ai::Agent::Percept *Environment::GetPercept(ai::Agent::Agent *agent)
    {
      ai::Agent::Percept *percept = new ai::Agent::Percept();

      /* Get Agent Percept */
      ai::Agent::Percept *p = agent->GetPercept(agent->GetLocation());
      percept->Join(p);
      delete p;

      /* Set board percept */
      ai::Agent::PerceptAtom atom("BOARD", game_board.GetBoardString());
      percept->JoinAtom(atom);

      return percept;
    }

    void Environment::Step()
    {
      unsigned int i;

      for(i = 0; i < agents_order.size(); i++)
        {
          Agent  *a_agent  = dynamic_cast<Agent *>(agents[agents_order[i]]);
          DBGP_L(LOG_STREAM(std::cerr) 
                 << "i: " << i
                 << "  a_agent->GetPlayerNumber(): " << a_agent->GetPlayerNumber()
                 << "  game_board.GetBoard().player_turn: " << game_board.GetBoard().player_turn
                 << std::endl);
          if(a_agent->GetPlayerNumber() == game_board.GetBoard().player_turn)
            {
              ai::Agent::Percept *percept = GetPercept(a_agent);

              timeval t;

              gettimeofday(&t, NULL);
              double t1 = t.tv_sec+(t.tv_usec/1000000.0);

              ai::Agent::Action  *action  = a_agent->Program(percept);

              gettimeofday(&t, NULL);
              double t2 = t.tv_sec+(t.tv_usec/1000000.0);

              a_agent->SetDuration(t2-t1);

              if(action)
                {
                  ApplyAction(a_agent, action);
                  delete action;
                }
              delete percept;
              break;
            }
        }
      UpdateDisplays();
    }

    void Environment::Run(const int n_steps)
    {
      for(auto ait = agents.begin(); ait != agents.end(); ait++)
        {
          ait->second->SetPerformance(0);
        }
      UpdateDisplays();
      if(delay)
        {
          FineSleep(delay);
        }
      while( !game_board.HaveWinner() 
             && ((int)(game_board.GetPlayerTotalMoves(1) + game_board.GetPlayerTotalMoves(2)) < (int)(2*n_steps) ) )
        {
          if(game_board.HaveWinner())
            {
              break;
            }
          Step();
          if(delay)
            {
              FineSleep(delay);
            }
        }
    }
    void Environment::SetMaxPlayerTime( const double max_time )
    {
      mMaxPlayerTime = max_time;
      game_board.SetMaxPlayerTime( mMaxPlayerTime );
    }
    void Environment::AddAgent(ai::Agent::Agent *agent)
    {
      Agent  *a_agent  = dynamic_cast<Agent *>(agent);
      ai::Agent::Environment::AddAgent(agent, 0);
      a_agent->SetPlayerNumber((int)agents.size());
    }

    ai::Agent::Location *Environment::DefaultLocation() const
    {
      return 0;
    }

    bool Environment::GetUpdateMessage(ai::Agent::Message &omsg) {
      if(!ai::Agent::Environment::GetUpdateMessage(omsg)) {
        DBGP_E(LOG_STREAM(std::cerr) << "Failed to get parent class data." << std::endl);
        return false;
      }

      /*
       * BoardData information
       */
      const BoardData           &board = game_board.GetBoard();
      int row, column, piece;
      for( row = 0; row < 10; row++ ) {
        for( column = 0; column < 10; column++ ) {
          ADD_TO_MSG_IF_CHANGED("SQUARE " << row << " " << column, (int)board.squares[ row ][ column ], omsg, mLastMessage);
        }
      }
      for( piece = 0; piece < 40; piece++ ) {
        ADD_TO_MSG_IF_CHANGED("PIECE_X " << piece, (int)board.pieces[ piece ].mLocation.x, omsg, mLastMessage);
        ADD_TO_MSG_IF_CHANGED("PIECE_Y " << piece, (int)board.pieces[ piece ].mLocation.y, omsg, mLastMessage);
        ADD_TO_MSG_IF_CHANGED("PIECE_ALIVE " << piece, (int)board.pieces[ piece ].mAlive, omsg, mLastMessage);
      }

      ADD_TO_MSG_IF_CHANGED("PLAYER_TURN", board.player_turn, omsg, mLastMessage);
      int player;
      for( player = 1; player <= 2; player++ ) {
        ADD_TO_MSG_IF_CHANGED("USED_ESCAPE " << player, (int)board.used_escape[ player-1 ], omsg, mLastMessage);
      }

      /*
       * JetanBoard information
       */
      ADD_TO_MSG_IF_CHANGED("NUMBER_OF_TURNS", game_board.GetTotalMoves(), omsg, mLastMessage);

      const std::vector<unsigned int> &turn_count = game_board.GetPlayerTotalMoves();
      size_t ii;
      for(ii = 0; ii < turn_count.size(); ii++)
        {
          ADD_TO_MSG_IF_CHANGED("NUMBER_OF_TURNS " << ii, (int)turn_count[ii], omsg, mLastMessage);
        }

      const std::vector<MoveData> &last_moves = game_board.GetLastMoves();
      for(ii = 0; ii < last_moves.size(); ii++)
        {
          ADD_TO_MSG_IF_CHANGED("LAST_MOVES " << ii, (int)last_moves[ii].piece.x << " " << (int)last_moves[ii].piece.y << " " << (int)last_moves[ii].offset.dx << " " << (int)last_moves[ii].offset.dy, omsg, mLastMessage);
        }

      const std::vector<double> &times = game_board.GetPlayerTimes();
      for(ii = 0; ii < times.size(); ii++)
        {
          ADD_TO_MSG_IF_CHANGED("PLAYER_TIMES " << ii, times[ii], omsg, mLastMessage);
        }

      return true;
    }

    bool Environment::UpdateFromMessage(ai::Agent::Message &imsg)
    {
      MSG_MAKE_AGENTS_EXIST(imsg);
      if(!ai::Agent::Environment::UpdateFromMessage(imsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to update parent class." << std::endl);
          return false;
        }

      /*
       * BoardData information
       */
      BoardData board = game_board.GetBoard();
      int row, column, piece;
      for( row = 0; row < 10; row++ ) {
        for( column = 0; column < 10; column++ ) {
          piece = -2;
          SET_FROM_MSG_IF_EXISTS("SQUARE " << row << " " << column, piece, imsg);
          if( piece > -2 ) {
            board.squares[ row ][ column ] = piece;
          }
        }
      }
      
      int x, y, alive;
      for( piece = 0; piece < 40; piece++ ) {
        x = -2;
        y = -2;
        alive = -2;
        SET_FROM_MSG_IF_EXISTS("PIECE_X " << piece, x, imsg);
        SET_FROM_MSG_IF_EXISTS("PIECE_Y " << piece, y, imsg);
        SET_FROM_MSG_IF_EXISTS("PIECE_ALIVE " << piece, alive, imsg);
        if( x > -2 ) {
          board.pieces[ piece ].mLocation.x = x;
        }
        if( y > -2 ) {
          board.pieces[ piece ].mLocation.y = y;
        }
        if( alive > -2 ) {
          board.pieces[ piece ].mAlive = alive;
        }
      }

      SET_FROM_MSG_IF_EXISTS("PLAYER_TURN", board.player_turn, imsg);

      int player;
      int used;
      for( player = 1; player <= 2; player++ ) {
        used = -2;
        SET_FROM_MSG_IF_EXISTS("USED_ESCAPE " << player, used, imsg);
        if( used > -2 ) {
          board.used_escape[ player-1 ] = used;
        }
      }

      for( row = 0; row < 10; row++ ) {
        for( column = 0; column < 10; column++ ) {
          DBGP_ENV( LOG_STREAM( std::cerr ) 
                    << "Piece @" << column << "," << row
                    << " " << (int)board.squares[ row ][ column ]
                    << std::endl);
        }
      }

      game_board.SetBoard(board);

      /*
       * JETANBoard information
       */
      SET_FROM_MSG_IF_EXISTS("NUMBER_OF_TURNS", game_board.number_of_turns, imsg);

      unsigned int turns;
      int j;
      for(j = 1; j <= 2; j++)
        {
          SET_FROM_MSG_IF_EXISTS("NUMBER_OF_TURNS " << (j-1), turns, imsg);
          game_board.number_of_player_turns[j-1]=turns;
        }
      
      int i;
      int dx, dy;
      for(i = 1; i <= 2; i++)
        {
          x = y = dx = dy = -100;
          SET_FROM_MSG_IF_EXISTS("LAST_MOVES " << (i-1), 
                                 x >> y >> dx >> dy, imsg);
          if( x > -100 ) {
            game_board.last_moves[i-1].piece.x = x;
          }
          if( y > -100 ) {
            game_board.last_moves[i-1].piece.y = y;
          }
          if( dx > -100 ) {
            game_board.last_moves[i-1].offset.dx = dx;
          }
          if( dy > -100 ) {
            game_board.last_moves[i-1].offset.dy = dy;
          }
        }

      for(i = 1; i <= 2; i++)
        {
          SET_FROM_MSG_IF_EXISTS("PLAYER_TIMES " << (i-1), game_board.player_times[i-1], imsg);
        }

      return true;
    }

    const Board & Environment::GameBoard() const
    {
      return game_board;
    }
  }
}

