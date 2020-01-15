#include <ai_ultimatetictactoe.h>
#include <sys/time.h>
#include <unistd.h>

namespace ai
{
  namespace UltimateTicTacToe
  {
    Environment::Environment()
    {
    }

    Environment::Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in)
      : ai::Agent::Environment(rand_in, displays_in),
        game_board()
    {
      /*
        std::cout << game_board.GetBoardString() << std::endl;
      */
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
      int t;
      for(auto ait = agents.begin(); ait != agents.end(); ait++)
        {
          ait->second->SetPerformance(0);
        }
      UpdateDisplays();
      if(delay)
        {
          sleep(delay);
        }
      for(t = 0; t < n_steps; t++)
        {
          if(game_board.HaveWinner())
            {
              break;
            }
          Step();
          if(delay)
            {
              sleep(delay);
            }
        }
    }

    void Environment::AddAgent(ai::Agent::Agent *agent)
    {
      Agent  *a_agent  = dynamic_cast<Agent *>(agent);
      ai::Agent::Environment::AddAgent(agent, 0);
      a_agent->SetPlayerNumber((int)agents.size());
      game_board.SetNumPlayer((int)agents.size());
    }

    ai::Agent::Location *Environment::DefaultLocation() const
    {
      return 0;
    }

    bool Environment::GetUpdateMessage(ai::Agent::Message &omsg)
    {
      if(!ai::Agent::Environment::GetUpdateMessage(omsg))
        {
          DBGP_E(LOG_STREAM(std::cerr) << "Failed to get parent class data." << std::endl);
          return false;
        }

      /*
       * BoardData information
       */
      const BoardData           &board = game_board.GetBoard();
      int i, j, bi, bj;
      for( bi = 0; bi < 3; bi++ ) {
        for( bj = 0; bj < 3; bj++ ) {
          for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
              ADD_TO_MSG_IF_CHANGED("GRID " << bi << " " << bj << " " << i << " " << j, board.grid[bi][bj].grid[i][j], omsg, mLastMessage);
            }
          }
        }
      }
      ADD_TO_MSG_IF_CHANGED("NUM_PLAYERS", board.num_players, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("PLAYER_TURN", board.player_turn, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("NEXT_BOARD_X", board.next_board_x, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("NEXT_BOARD_Y", board.next_board_y, omsg, mLastMessage);

      /*
       * UTTTBoard information
       */
      ADD_TO_MSG_IF_CHANGED("NUMBER_OF_TURNS", game_board.GetTotalMoves(), omsg, mLastMessage);

      const std::vector<MoveData> &last_moves = game_board.GetLastMoves();
      size_t ii;
      for(ii = 0; ii < last_moves.size(); ii++)
        {
          ADD_TO_MSG_IF_CHANGED("LAST_MOVES " << ii, last_moves[ii].board_x << " " << last_moves[ii].board_y << " " << last_moves[ii].pos_x << " " << last_moves[ii].pos_y, omsg, mLastMessage);
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
      int i, j, bi, bj;
      for( bi = 0; bi < 3; bi++ ) {
        for( bj = 0; bj < 3; bj++ ) {
          for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
              SET_FROM_MSG_IF_EXISTS("GRID " << bi << " " << bj << " " << i << " " << j, board.grid[bi][bj].grid[i][j], imsg);
            }
          }
        }
      }
      SET_FROM_MSG_IF_EXISTS("NUM_PLAYERS", board.num_players, imsg);
      SET_FROM_MSG_IF_EXISTS("PLAYER_TURN", board.player_turn, imsg);
      SET_FROM_MSG_IF_EXISTS("NEXT_BOARD_X", board.next_board_x, imsg);
      SET_FROM_MSG_IF_EXISTS("NEXT_BOARD_Y", board.next_board_y, imsg);
      game_board.SetBoard(board);


      /*
       * UTTTBoard information
       */
      SET_FROM_MSG_IF_EXISTS("NUMBER_OF_TURNS", game_board.number_of_turns, imsg);

      for(i = 1; i <= board.num_players; i++)
        {
          SET_FROM_MSG_IF_EXISTS("LAST_MOVES " << (i-1), 
                                 game_board.last_moves[i-1].board_x >> game_board.last_moves[i-1].board_y >> 
                                 game_board.last_moves[i-1].pos_x >> game_board.last_moves[i-1].pos_y, imsg);
        }

      for(i = 1; i <= board.num_players; i++)
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

