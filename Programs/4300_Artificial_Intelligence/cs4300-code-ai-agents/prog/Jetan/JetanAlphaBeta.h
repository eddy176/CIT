#ifndef _JETANALPHABETA_H_
#define _JETANALPHABETA_H_
#include <ai_jetan.h>
// #include "JetanMinimax.h"
namespace ai
{
namespace Jetan
{
class PlyData
{
public:
  PlyData(double utility_in);
  bool move_ok;
  ai::Jetan::MoveData move;
  double utility;
};
class AlphaBeta : public ai::Agent::AgentProgram
{
public:
  enum EvaluationOption
  {
    PIECE_COUNT,     // 0
    PIECE_COUNT_WIN, // 1
    WEIGHTED_PIECE_COUNT_WIN,
    NEW_WEIGHTS,
    NEW_TECHNIQUE,
    NEW_TECHNIQUE_NEW_WEIGHTS,
    TT_H_4,
    TT_H_5,
    TT_H_6,
    TT_H_COMBO_1,
    TT_H_COMBO_2,
    TT_H_COMBO_3,
  };
  AlphaBeta(ai::Agent::Options *opts);
  ~AlphaBeta();
  virtual ai::Agent::Action *Program(const ai::Agent::Percept *percept);

protected:
  PlyData PickMove(const ai::Jetan::Board &board, int player);
  PlyData Max(const ai::Jetan::Board &board, int player, int depth, double alpha, double beta);
  PlyData Min(const ai::Jetan::Board &board, int player, int depth, double alpha, double beta);

  double Evaluate(const ai::Jetan::Board &board, int player);

  double EvaluatePieceCount(const ai::Jetan::Board &board, int player);
  double EvaluatePieceCountWin(const ai::Jetan::Board &board, int player);
  double EvaluatePieceCountWeight(const ai::Jetan::Board &board, int player);
  double EvaluatePieceCountWinPlusWeight(const ai::Jetan::Board &board, int player);
  double EvaluatePieceCountWinPlusWeight2(const ai::Jetan::Board &board, int player);

  double EvaluateLocationWorth(const ai::Jetan::Board &board, int player);
  double EvaluateAttackedSpaces(const ai::Jetan::Board &board, int player);
  double EvaluateAttackedSpaces2(const ai::Jetan::Board &board, int player);
  double EvaluateAttackLocation(const ai::Jetan::Board &board, int player);
  double EvaluateNewVersion(const ai::Jetan::Board &board, int player);
  double EvaluateNewVersion2(const ai::Jetan::Board &board, int player);

private:
  int max_depth;
  EvaluationOption evaluation_method;
  char pieceArray[8];
  SetOfBoardLocations myAttacked;
  SetOfBoardLocations otherAttacked;
};
} // namespace Jetan
} // namespace ai
#endif /* _AISAMPLEALPHABETA_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
