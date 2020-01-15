#include "RandomPick.h"

namespace ai
{
  namespace Sample
  {

    RandomPick::RandomPick()
    {
      SetName("RandomPick");
    }

    RandomPick::~RandomPick()
    {
    }

    ai::Agent::Action * RandomPick::Program(const ai::Agent::Percept * percept)
    {
      ai::Abalone::Action *action = new ai::Abalone::Action;
      ai::Abalone::MoveData move;

      std::string board_str = percept->GetAtom("BASIC_BOARD").GetValue();
      ai::Abalone::BasicBoard board(board_str);

      int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

      const std::vector<ai::Abalone::MoveData> &moves = board.DetermineLegalMoves(player);

      move = moves[rand() % moves.size()];

      action->SetMove(move);
      action->SetCode(ai::Abalone::Action::MOVE);

      return action;
    }
  }
}
