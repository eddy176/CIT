#include <ai_ccheckers.h>
#include <sys/time.h>
#include <unistd.h>

namespace ai
{
  namespace CCheckers
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
            Action *cc_action = dynamic_cast<Action *>(action);
            Agent  *cc_agent  = dynamic_cast<Agent *>(agent);
            return game_board.Move(cc_agent->GetPlayerNumber(),
                                   cc_action->GetMove(),
                                   cc_agent->GetDuration());
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
      ai::Agent::PerceptAtom atom("BASIC_BOARD", game_board.GetBoardString());
      percept->JoinAtom(atom);

      return percept;
    }

    void Environment::Step()
    {
      size_t i;

      for(i = 0; i < agents_order.size(); i++)
        {
          Agent  *cc_agent  = dynamic_cast<Agent *>(agents[agents_order[i]]);
          if(cc_agent->GetPlayerNumber() == game_board.GetBoard().player_turn)
            {
              ai::Agent::Percept *percept = GetPercept(cc_agent);

              timeval t;

              gettimeofday(&t, NULL);
              double t1 = t.tv_sec+(t.tv_usec/1000000.0);

              ai::Agent::Action  *action  = cc_agent->Program(percept);

              gettimeofday(&t, NULL);
              double t2 = t.tv_sec+(t.tv_usec/1000000.0);

              cc_agent->SetDuration(t2-t1);

              if(action)
                {
                  ApplyAction(cc_agent, action);
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
      Agent  *cc_agent  = dynamic_cast<Agent *>(agent);
      ai::Agent::Environment::AddAgent(agent, 0);
      cc_agent->SetPlayerNumber((int)agents.size());
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
      ADD_ARRAY_OF_ARRAY_TO_MSG_IF_CHANGED("HOLE", game_board.board.hole, 17, 17, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("NUM_PLAYERS", game_board.board.num_players, omsg, mLastMessage);
      ADD_TO_MSG_IF_CHANGED("PLAYER_TURN", game_board.board.player_turn, omsg, mLastMessage);

      /*
       * BasicBoard information
       */
      ADD_TO_MSG_IF_CHANGED("NUMBER_OF_TURNS", game_board.number_of_turns, omsg, mLastMessage);

      size_t ii;
      for(ii = 0; ii < game_board.last_moves.size(); ii++)
        {
          ADD_TO_MSG_IF_CHANGED("LAST_MOVES " << ii,
                                game_board.last_moves[ii].from_x << " " << game_board.last_moves[ii].from_y <<
                                game_board.last_moves[ii].to_x << " " << game_board.last_moves[ii].to_y,
                                omsg, mLastMessage);
        }

      for(ii = 0; ii < game_board.player_times.size(); ii++)
        {
          ADD_TO_MSG_IF_CHANGED("PLAYER_TIMES " << ii, game_board.player_times[ii], omsg, mLastMessage);
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
      SET_ARRAY_OF_ARRAY_FROM_MSG_IF_EXISTS("HOLE", game_board.board.hole, 17, 17, imsg);
      SET_FROM_MSG_IF_EXISTS("NUM_PLAYERS", game_board.board.num_players, imsg);
      SET_FROM_MSG_IF_EXISTS("PLAYER_TURN", game_board.board.player_turn, imsg);


      /*
       * BasicBoard information
       */
      int i;
      SET_FROM_MSG_IF_EXISTS("NUMBER_OF_TURNS", game_board.number_of_turns, imsg);

      for(i = 1; i <= game_board.board.num_players; i++)
        {
          SET_FROM_MSG_IF_EXISTS("LAST_MOVES " << (i-1),
                                 game_board.last_moves[i-1].from_x >> game_board.last_moves[i-1].from_y >>
                                 game_board.last_moves[i-1].to_x >> game_board.last_moves[i-1].to_y, imsg);
        }

      for(i = 1; i <= game_board.board.num_players; i++)
        {
          SET_FROM_MSG_IF_EXISTS("PLAYER_TIMES " << (i-1), game_board.player_times[i-1], imsg);
        }

      return true;
    }

    const BasicBoard & Environment::GameBoard() const
    {
      return game_board;
    }
  }
}

