#ifndef _CUBEPROBLEM_H_
#define _CUBEPROBLEM_H_

// may or may not be finished
#include "CubeModel.h"
#include <map>
#include "CubeState.h"

#include "ai_search.h"

namespace ai {
namespace rubiks {

class Problem : public ai::Search::Problem {
public:
  enum HeuristicEnum {ZERO_HEURISTIC, FACELET_HEURISTIC, CUBIE_HEURISTIC, CORNERS_HEURISTIC, EDGES_HEURISTIC, CORNERS_EDGES_HEURISTIC};

  Problem(ai::Search::State *initial_state_in, const std::vector<Cube> &goal_cube_in);
  virtual ~Problem();

  virtual bool GoalTest(const ai::Search::State *const state_in) const;
  virtual std::vector<ai::Search::Action *>
  Actions(const ai::Search::State *const state_in);
  virtual ai::Search::State *Result(const ai::Search::State *const state_in, const ai::Search::Action *const action_in);

  virtual double StepCost(const ai::Search::State *const state1_in, const ai::Search::Action *const action_in, const ai::Search::State *const state2_in) const;
  void setAllowedMoves(const std::map<std::string, Move> &allowed_moves);

  HeuristicEnum getHeuristic();
  virtual double Heuristic(const ai::Search::State *const state_in) const;
  virtual double FaceletHeuristic(const ai::Search::State *const state_in) const;
  virtual double CubiesHeuristic(const ai::Search::State *const state_in) const;
  virtual double EdgesHeuristic(const ai::Search::State *const state_in) const;
  virtual double CornersHeuristic(const ai::Search::State *const state_in) const;
  virtual double CornersEdgesHeuristic(const ai::Search::State *const state_in) const;

  void setHeuristic(const HeuristicEnum& heuristic); 

private:
  std::map<std::string, Move> mAllowedMoves;
  const std::vector<Cube> mGoalCubes;
  HeuristicEnum mHeuristic;
};

} // namespace rubiks
} // namespace ai

#endif /* _CUBEPROBLEM_H_ */
       /* Local Variables: */
       /* mode:c++         */
       /* End:             */