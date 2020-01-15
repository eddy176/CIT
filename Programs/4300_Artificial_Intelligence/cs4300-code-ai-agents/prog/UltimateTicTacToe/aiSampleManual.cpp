#include "aiSampleManual.h"
#include <cstdio>

namespace ai
{
  namespace UltimateTicTacToe
  {
    Manual::Manual(ai::Agent::Options *opts)
    {
      SetName("Manual");
    }
    
    Manual::~Manual()
    {
    }
    
    ai::Agent::Action * Manual::Program(const ai::Agent::Percept * percept)
    {
      ai::UltimateTicTacToe::Action *action = new ai::UltimateTicTacToe::Action;
      
      std::string board_str = percept->GetAtom("BOARD").GetValue();
      ai::UltimateTicTacToe::Board board(board_str);
      
      int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

      const std::vector<ai::UltimateTicTacToe::MoveData> & moves = board.DetermineLegalMoves(player);

      if(moves.size() > 0)
        {
          std::cout << "Player: " << player << std::endl;
          std::cout << "Board: " << board_str << std::endl;
          
          bool done = false;
          while(!done)
            {
              ai::UltimateTicTacToe::MoveData move;
              std::cout << "Move? bx,by,x,y ";
              
              char buf[128];
              std::cin.getline(buf, 128);
              
              if(std::sscanf(buf, "%d,%d,%d,%d",
                             &move.board_x, &move.board_y, 
                             &move.pos_x, &move.pos_y) == 4) {
                if( board.IsLegal( player,  move ) ) {
                  action->SetMove(move);
                  action->SetCode(ai::UltimateTicTacToe::Action::MOVE);
                  done = true;
                }
              }
            }
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
