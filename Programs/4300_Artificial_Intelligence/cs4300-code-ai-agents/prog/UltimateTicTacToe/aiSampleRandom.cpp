#include "aiSampleRandom.h"
#include <ctime>
#include <cstdlib>

namespace ai
{
  namespace UltimateTicTacToe
  {
    Random::Random(ai::Agent::Options *opts)
    {
      SetName("Random");
    }
    
    Random::~Random()
    {
    }
    
    ai::Agent::Action * Random::Program(const ai::Agent::Percept * percept)
    {
      ai::UltimateTicTacToe::Action *action = new ai::UltimateTicTacToe::Action;
      
      std::string board_str = percept->GetAtom("BOARD").GetValue();
      ai::UltimateTicTacToe::Board board(board_str);
      
      int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

      const std::vector<ai::UltimateTicTacToe::MoveData> & moves = board.DetermineLegalMoves(player);

      if(moves.size() > 0)
        {
          int best_i = rand() % moves.size();
          ai::UltimateTicTacToe::MoveData best_move = moves[best_i];
          action->SetMove(best_move);
          action->SetCode(ai::UltimateTicTacToe::Action::MOVE);
        }
      else
        {
          /* no legal move */
          action->SetCode(ai::UltimateTicTacToe::Action::QUIT);
        }
      return action;
    }
  }
}
