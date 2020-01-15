#ifndef _JETANMINIMAX_H_
#define _JETANMINIMAX_H_

#include <ai_jetan.h>
namespace ai
{
  namespace Jetan
  {
    enum
    {
      T_SCORE_ME = 1,
      T_SCORE_OTHER = 2,
      T_SCORE_DIFF = 3,
      T_H_1,
      T_H_2,
      T_H_3,
      T_H_4,
      T_H_5,
      T_H_6,
      T_H_COMBO_1,
      T_H_COMBO_2,
      T_H_COMBO_3,
    };

    class PlyData
    {
    public:
      PlyData(double utility_in);
      bool move_ok;
      ai::Jetan::MoveData move;
      double utility;
    };
    
    class Minimax : public ai::Agent::AgentProgram
    {
    public:
      Minimax(ai::Agent::Options *opts);
      ~Minimax();
      virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
    protected:
      PlyData PickMove(const ai::Jetan::Board &board, int player);
      PlyData Max(const ai::Jetan::Board &board, int player, int depth);
      PlyData Min(const ai::Jetan::Board &board, int player, int depth);

      double Evaluate(const ai::Jetan::Board &board, int player);
    private:
      double EvaluateScoreMe(const ai::Jetan::Board &board, int player);
      double EvaluateScoreOther(const ai::Jetan::Board &board, int player);
      double EvaluateScoreDiff(const ai::Jetan::Board &board, int player);

      double hCloseToWinningMe(const ai::Jetan::Board &board, int player);
      double hCloseToWinningOther(const ai::Jetan::Board &board, int player);
      double hCloseToPrincess(const ai::Jetan::Board &board, int player);
      double hFarFromMyPrincess(const ai::Jetan::Board &board, int player);
      double hCloseToTheirCheiftain(const ai::Jetan::Board &board, int player);
      double hFarFromMyCheiftain(const ai::Jetan::Board &board, int player);

      ///////////////////////////
      double costofSacarafice(const ai::Jetan::Board &board, int player);        // is the cost of the sacarafice worth the opp's peice/position?
      double canTakeForFree(const ai::Jetan::Board &board, int player);          // is the kill a free kill? - is it a trap?
      double advantageousPositioning(const ai::Jetan::Board &board, int player); // estimate of if I can come out on top in skirmish
      double evenTradeBetterPosition(const ai::Jetan::Board &board, int player); // if an even trade, is the position that results better?
      double runOrFight(const ai::Jetan::Board &board, int player);              // is it a good idea to fight or run? 
      
      int max_depth;
      int evaluation_method;
    };
  }
}
#endif /* _JETANMiniMax_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */