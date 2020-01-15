// /**
//  * @ Author: Curtis Larsen
//  * @ Create Time: 2019-10-10 12:41:26
//  * @ Modified by: Kacy Stocks
//  * @ Modified time: 2019-10-15 17:18:27
//  * @ Description: First Implementation of Minimax
// :
//  */

#include "JetanMinimax.h"
#include <cstdio>

namespace ai
{
namespace Jetan
{
const double MY_INFINITY = 1.e10;

PlyData::PlyData(double utility_in)
    : move_ok(false),
      utility(utility_in)
{
}

Minimax::Minimax(ai::Agent::Options *opts)
    : max_depth(3),
      evaluation_method(T_SCORE_DIFF)
{
  if (opts->GetArgInt("user1") > 0)
  {
    this->max_depth = opts->GetArgInt("user1");
  }
  if (opts->GetArgInt("user2") > 0)
  {
    this->evaluation_method = opts->GetArgInt("user2");
  }
  {
    char buf[128];
    std::sprintf(buf, "Minimax-%d-%d",
                 this->max_depth,
                 this->evaluation_method);
    SetName(buf);
  }

  std::cout << "Options:" << std::endl;
  std::cout << "-U num : maximum search depth (in ply)." << std::endl;
  std::cout << "-V num : evaluation method." << std::endl;
  std::cout << "       : my score    : " << T_SCORE_ME << std::endl;
  std::cout << "       : other score : " << T_SCORE_OTHER << std::endl;
  std::cout << "       : diff score  : " << T_SCORE_DIFF << std::endl;
  std::cout << "       : h1   : " << T_H_1 << std::endl;
  std::cout << "       : h2   : " << T_H_2 << std::endl;
  std::cout << "       : h3   : " << T_H_3 << std::endl;
  std::cout << "       : h4   : " << T_H_4 << std::endl;
  std::cout << "       : h5   : " << T_H_5 << std::endl;
  std::cout << "       : h6   : " << T_H_6 << std::endl;
  std::cout << "       : hcombo1 : " << T_H_COMBO_1 << std::endl;
  std::cout << "       : hcombo2 : " << T_H_COMBO_2 << std::endl;
  std::cout << "       : hcombo3 : " << T_H_COMBO_3 << std::endl;
}

Minimax::~Minimax()
{
}

ai::Agent::Action *Minimax::Program(const ai::Agent::Percept *percept)
{
  ai::Jetan::Action *action = new ai::Jetan::Action;

  std::string board_str = percept->GetAtom("BOARD").GetValue();
  ai::Jetan::Board board(board_str);

  int player = atoi(percept->GetAtom("PLAYER_NUMBER").GetValue().c_str());

  PlyData ply_data = this->PickMove(board, player);

  if (ply_data.move_ok)
  {
    action->SetCode(ai::Jetan::Action::MOVE);
    action->SetMove(ply_data.move);
  }
  else
  {
    /* no legal move, or bad choice */
    action->SetCode(ai::Jetan::Action::QUIT);
  }
  return action;
}

PlyData Minimax::PickMove(const ai::Jetan::Board &board, int player)
{
  PlyData ply_data = this->Max(board, player, 1);
  return ply_data;
}

PlyData Minimax::Max(const ai::Jetan::Board &board, int player, int depth)
{
  PlyData ply_data(-MY_INFINITY);
  if (board.HaveWinner() || depth > this->max_depth)
  {
    ply_data.utility = this->Evaluate(board, player);
    return ply_data;
  }

  ai::Jetan::Board my_board(board);
  const std::vector<ai::Jetan::MoveData> &moves = my_board.DetermineLegalMoves(player);
  int i;
  for (i = 0; i < (int)moves.size(); i++)
  {
    ai::Jetan::Board tmp_board(board);
    tmp_board.Move(player, moves[i]);
    PlyData tmp_ply_data = this->Min(tmp_board, player, depth + 1);
    if ((tmp_ply_data.utility > ply_data.utility) ||
        ((tmp_ply_data.utility == ply_data.utility) &&
         (std::rand() % 2)))
    {
      ply_data.utility = tmp_ply_data.utility;
      ply_data.move = moves[i];
      ply_data.move_ok = true;
    }
  }

  return ply_data;
}

PlyData Minimax::Min(const ai::Jetan::Board &board, int player, int depth)
{
  PlyData ply_data(MY_INFINITY);
  if (board.HaveWinner() || depth > this->max_depth)
  {
    ply_data.utility = this->Evaluate(board, player);
    return ply_data;
  }

  int other_player = (player == 1) ? 2 : 1;
  ai::Jetan::Board my_board(board);
  const std::vector<ai::Jetan::MoveData> &moves = my_board.DetermineLegalMoves(other_player);
  int i;
  for (i = 0; i < (int)moves.size(); i++)
  {
    ai::Jetan::Board tmp_board(board);
    tmp_board.Move(other_player, moves[i]);
    PlyData tmp_ply_data = this->Max(tmp_board, player, depth + 1);
    if ((tmp_ply_data.utility < ply_data.utility) ||
        ((tmp_ply_data.utility == ply_data.utility) &&
         (std::rand() % 2)))
    {
      ply_data.utility = tmp_ply_data.utility;
      ply_data.move = moves[i];
      ply_data.move_ok = true;
    }
  }

  return ply_data;
}

/*
     * Choose evaluation method
     */
double Minimax::Evaluate(const ai::Jetan::Board &board, int player)
{
  double v = 0.0;
  switch (this->evaluation_method)
  {
  case T_SCORE_ME:
    v = this->EvaluateScoreMe(board, player);
    break;
  case T_SCORE_OTHER:
    v = this->EvaluateScoreOther(board, player);
    break;
  default:
    v = this->EvaluateScoreDiff(board, player);
    break;
      // case T_H_1:
      //   v = this->EvaluateScoreDiff(board, player) + this->hCloseToPrincess(board, player);
      //   break;
    //   case T_H_2:
    //     v = this->hCloseToWinningMe(board, player);
    //     break;
    //   case T_H_3:
    //     v = this->hCloseToWinningOther(board, player);
    //     break;
    //   case T_H_4:
    //     v = this->hCloseToHome(board, player);
    //     break;
    //   case T_H_5:
    //     v = this->hFarFromHome(board, player);
    //     break;
    //   case T_H_6:
    //     v = this->hMiddleFromHome(board, player);
    //     break;
    //   case T_H_COMBO_1:
    //     v = -1*this->hCloseToWinningMe(board, player) +
    //       this->hCloseToHome(board, player) +
    //       3*this->hFarFromHome(board, player) +
    //       2*this->hMiddleFromHome(board, player);
    //     break;
    //   case T_H_COMBO_2:
    //     v = -2*this->hCloseToWinningMe(board, player) +
    //       1*this->hCloseToWinningOther(board, player) +
    //       1*this->hFarFromHome(board, player);
    //     break;
    //   case T_H_COMBO_3:
    //     v = 1*this->EvaluateScoreDiff(board, player) +
    //       -1*this->hCloseToWinningMe(board, player) +
    //       1*this->hCloseToWinningOther(board, player);
    //     break;
  }
  return v;
}

double Minimax::EvaluateScoreMe(const ai::Jetan::Board &board, int player)
{
  // estimate board's value
  double mTotal = 0;
  BoardData bd = board.GetBoard();
  for (size_t y = 0; y < 20; y++) // for all pieces
  {
    Piece p = bd.pieces[y];
    if (p.mAlive)
    {
      mTotal += 1;
    }
  }
  return mTotal / 20;
}

double Minimax::EvaluateScoreOther(const ai::Jetan::Board &board, int player)
{
  // estimate board's value
  double mTotal = 0;
  BoardData bd = board.GetBoard();
  for (size_t y = 20; y < 40; y++) // for all pieces
  {
    Piece p = bd.pieces[y];
    if (p.mAlive)
    {
      mTotal += 1;
    }
  }
  return mTotal / 20;
}

double Minimax::EvaluateScoreDiff(const ai::Jetan::Board &board, int player)
{
  return EvaluateScoreMe(board, player) - EvaluateScoreOther(board, player);
}

double Minimax::hCloseToPrincess(const ai::Jetan::Board &board, int player){
    int other_player = (player == 1) ? 2 : 1;
    double v = 0;
    BoardData bd = board.GetBoard();
    Piece princess = bd.pieces[Piece::PRINCESS + other_player*20];
    double ox = princess.mLocation.x;
    double oy = princess.mLocation.y;
    for (size_t y = 0 + 20*(unsigned int)player; y < 20 + 20*(unsigned int)player; y++) // for all pieces
    {
        Piece p = bd.pieces[y];
        int px = p.mLocation.x;
        int py = p.mLocation.y;
        v = abs(ox - px) + abs(oy - py);
    }
    // std::cout << "How close to princes: " << v/100 << std::endl;
    return v / 100;
}

double Minimax::hFarFromMyPrincess(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
}

double Minimax::hCloseToTheirCheiftain(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
}

double Minimax::hFarFromMyCheiftain(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
}

double Minimax::costofSacarafice(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
}        // is the cost of the sacarafice worth the opp's peice/position?
double Minimax::canTakeForFree(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
}          // is the kill a free kill? - is it a trap?
double Minimax::advantageousPositioning(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
} // estimate of if I can come out on top in skirmish
double Minimax::evenTradeBetterPosition(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
} // if an even trade, is the position that results better?
double Minimax::runOrFight(const ai::Jetan::Board &board, int player){
  double v = 0;

  return v;
}              // is it a good idea to fight or run? 



} // namespace Jetan
} // namespace ai