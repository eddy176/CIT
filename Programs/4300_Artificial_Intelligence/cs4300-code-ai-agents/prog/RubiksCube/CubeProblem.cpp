#include "CubeProblem.h"
#include "CubeAction.h"
#include "CubeAppData.h"
#include "CubeState.h"
#include <exception>
#include <iterator>
#include <sstream>

#include <vector>
#include <array>
#include <algorithm>

namespace ai {
namespace rubiks {
Problem::Problem(ai::Search::State *initial_state_in, const std::vector<Cube> &goal_cube_in)
    : ai::Search::Problem(initial_state_in), mGoalCubes(goal_cube_in) {
  // empty
}

Problem::~Problem() {
  // empty
}

bool Problem::GoalTest(const ai::Search::State *const state_in) const {
  const State *const state = dynamic_cast<const State *const>(state_in);
  for (size_t i = 0; i < mGoalCubes.size(); i++) {
    if (state->getModel() == mGoalCubes[i]) {
      return true;
    }
  }
  return false;
}

std::vector<ai::Search::Action *>Problem::Actions(const ai::Search::State *const state_in) {
  // const State *const rs1 = dynamic_cast<const State *const>(state_in);
  std::vector<ai::Search::Action *> actions;

  for (auto it = mAllowedMoves.begin(); it != mAllowedMoves.end(); it++) {
    Action *A = new Action(it->second);
    actions.push_back(A);
  }
  return actions;
}

ai::Search::State *Problem::Result(const ai::Search::State *const state_in,
                                   const ai::Search::Action *const action_in) {
  const State *const state = dynamic_cast<const State *const>(state_in);
  const Action *const action = dynamic_cast<const Action *const>(action_in);

  // Cube model = state->getModel();
  Cube temp;
  temp.applyMove(action->getMove(), state->getModel());
  return new State(temp);
}

double Problem::StepCost(const ai::Search::State *const state1_in,const ai::Search::Action *const action_in,const ai::Search::State *const state2_in) const {
  // is used to find the cost of taking an action
  const Action *const action = dynamic_cast<const Action *const>(action_in);
  return action->getMove().getCost();
}

void Problem::setAllowedMoves(const std::map<std::string, Move> &allowed_moves) {
  mAllowedMoves.clear();
  for (auto i = allowed_moves.begin(); i != allowed_moves.end(); i++) {
    mAllowedMoves.insert({i->first, i->second});
  }
}

Problem::HeuristicEnum Problem::getHeuristic() {
  return Problem::mHeuristic;
}

void Problem::setHeuristic(const Problem::HeuristicEnum& heuristic){
  mHeuristic = heuristic;
}

// TESTING not best
double Problem::FaceletHeuristic(const ai::Search::State *const state_in) const {
  const State *state = static_cast<const State *>(state_in);
    Cube model = state->getModel();
    size_t numGoalCubes = mGoalCubes.size();
    const std::vector<ai::rubiks::Facelet> modelFacelets = model.getFacelets();
    double lowest_heuristic = 1000.0;
    for (size_t i = 0; i < numGoalCubes; i++) {
      double heuristic = 0.0;
      const std::vector<ai::rubiks::Facelet> gcFacelets = mGoalCubes[i].getFacelets();
      for (size_t j = 0; j < NUM_FACELETS_TOTAL; j++) {
        if (gcFacelets[j] != '*') {
          if (modelFacelets[j] != gcFacelets[j]) {
            heuristic += 1;
          }
        }
      }
      if (heuristic/20.0 < lowest_heuristic) {
        lowest_heuristic = heuristic/20.0;
      }
    }
    return lowest_heuristic;
}

// CornerHeuristic NOT useful anymore
double Problem::CornersHeuristic(const ai::Search::State *const state_in) const{
  const State *state = static_cast<const State *>(state_in);
  Cube model = state->getModel();
  size_t numGoalCubes = mGoalCubes.size();
  const std::vector<ai::rubiks::Facelet> modelFacelets = model.getFacelets();
  double lowest_corner_heuristic = 1000.0;
  for (size_t i = 0; i < numGoalCubes; i++) {
    double cornerHeuristic = 0.0;
    const std::vector<ai::rubiks::Facelet> gcFacelets = mGoalCubes[i].getFacelets();
    if (gcFacelets[0] != modelFacelets[0] || gcFacelets[9] != modelFacelets[9] || gcFacelets[38] != modelFacelets[38]) {
      cornerHeuristic += 1;
    }
    if (gcFacelets[2] != modelFacelets[2] || gcFacelets[29] != modelFacelets[29] || gcFacelets[36] != modelFacelets[36]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[6] != modelFacelets[6] || gcFacelets[11] != modelFacelets[11] || gcFacelets[18] != modelFacelets[18]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[8] != modelFacelets[8] || gcFacelets[20] != modelFacelets[20] || gcFacelets[27] != modelFacelets[27]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[15] != modelFacelets[15] || gcFacelets[44] != modelFacelets[44] || gcFacelets[51] != modelFacelets[51]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[17] != modelFacelets[17] || gcFacelets[24] != modelFacelets[24] || gcFacelets[45] != modelFacelets[45]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[26] != modelFacelets[26] || gcFacelets[33] != modelFacelets[33] || gcFacelets[47] != modelFacelets[47]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[35] != modelFacelets[35] || gcFacelets[42] != modelFacelets[42] || gcFacelets[53] != modelFacelets[53]) {
      cornerHeuristic += 1;
    }
    if (cornerHeuristic/NUM_CORNERS_TOTAL < lowest_corner_heuristic) {
      lowest_corner_heuristic = cornerHeuristic/NUM_CORNERS_TOTAL;
    }
  }
  return lowest_corner_heuristic;
}

// EdgeHeuristic upgraded to edges, corners, and cubie in wrong place NOT EFFECTIVE
double Problem::EdgesHeuristic(const ai::Search::State *const state_in) const{
  const State *state = static_cast<const State *>(state_in);
  Cube model = state->getModel();
  size_t numGoalCubes = mGoalCubes.size();
  const std::vector<ai::rubiks::Facelet> modelFacelets = model.getFacelets();
  double lowest_corner_heuristic = 100.0;
  double lowest_edge_heuristic = 100.0;
  for (size_t i = 0; i < numGoalCubes; i++) {
    double edgeHeuristic = 0.0;
    double cornerHeuristic = 0.0;
    const std::vector<ai::rubiks::Facelet> gcFacelets = mGoalCubes[i].getFacelets();
    if (gcFacelets[0] != modelFacelets[0] || gcFacelets[9] != modelFacelets[9] || gcFacelets[38] != modelFacelets[38]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[0], gcFacelets[9], gcFacelets[38]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[0]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[9]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[38]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }    
    }
    if (gcFacelets[1] != modelFacelets[1] || gcFacelets[37] != modelFacelets[37]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[1], gcFacelets[37]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[1]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[37]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      }  
    }        
    if (gcFacelets[2] != modelFacelets[2] || gcFacelets[29] != modelFacelets[29] || gcFacelets[36] != modelFacelets[36]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[2], gcFacelets[29], gcFacelets[36]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[2]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[29]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[36]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }   
    }        
    if (gcFacelets[3] != modelFacelets[3] || gcFacelets[10] != modelFacelets[10]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[3], gcFacelets[10]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[3]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[10]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      }  
    }        
    if (gcFacelets[6] != modelFacelets[6] || gcFacelets[11] != modelFacelets[11] || gcFacelets[18] != modelFacelets[18]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[6], gcFacelets[11], gcFacelets[18]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[6]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[11]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[18]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }   
    }        
    if (gcFacelets[5] != modelFacelets[5] || gcFacelets[28] != modelFacelets[28]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[5], gcFacelets[28]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[5]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[28]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[8] != modelFacelets[8] || gcFacelets[20] != modelFacelets[20] || gcFacelets[27] != modelFacelets[27]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[8], gcFacelets[20], gcFacelets[27]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[8]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[20]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[27]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }   
    }        
    if (gcFacelets[7] != modelFacelets[7] || gcFacelets[19] != modelFacelets[19]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[7], gcFacelets[19]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[7]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[19]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[12] != modelFacelets[12] || gcFacelets[41] != modelFacelets[41]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[12], gcFacelets[41]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[12]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[41]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[14] != modelFacelets[14] || gcFacelets[21] != modelFacelets[21]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[14], gcFacelets[21]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[14]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[21]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[23] != modelFacelets[23] || gcFacelets[30] != modelFacelets[30]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[23], gcFacelets[30]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[23]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[30]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[32] != modelFacelets[32] || gcFacelets[39] != modelFacelets[39]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[32], gcFacelets[39]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[32]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[39]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[15] != modelFacelets[15] || gcFacelets[44] != modelFacelets[44] || gcFacelets[51] != modelFacelets[51]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[15], gcFacelets[44], gcFacelets[51]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[15]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[44]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[51]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }   
    }        
    if (gcFacelets[16] != modelFacelets[16] || gcFacelets[48] != modelFacelets[48]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[16], gcFacelets[48]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[12]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[48]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[17] != modelFacelets[17] || gcFacelets[24] != modelFacelets[24] || gcFacelets[45] != modelFacelets[45]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[17], gcFacelets[24], gcFacelets[45]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[17]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[24]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[45]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }   
    }        
    if (gcFacelets[25] != modelFacelets[25] || gcFacelets[46] != modelFacelets[46]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[25], gcFacelets[46]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[25]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[46]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[26] != modelFacelets[26] || gcFacelets[33] != modelFacelets[33] || gcFacelets[47] != modelFacelets[47]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[26], gcFacelets[33], gcFacelets[47]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[26]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[33]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[47]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }   
    }        
    if (gcFacelets[34] != modelFacelets[34] || gcFacelets[50] != modelFacelets[50]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[34], gcFacelets[50]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[34]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[50]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }        
    if (gcFacelets[35] != modelFacelets[35] || gcFacelets[42] != modelFacelets[42] || gcFacelets[53] != modelFacelets[53]) {
      cornerHeuristic += 1;
      Facelet foo[3] = {gcFacelets[35], gcFacelets[42], gcFacelets[53]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[35]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[42]);
      Facelet *bat = std::find(std::begin(foo), std::end(foo), modelFacelets[53]);
      if (bar != std::end(foo) && baz != std::end(foo) && bat != std::end(foo)) {
        cornerHeuristic += 1;
      }   
    }
    if (gcFacelets[43] != modelFacelets[43] || gcFacelets[52] != modelFacelets[52]) {
      edgeHeuristic += 1;
      Facelet foo[2] = {gcFacelets[43], gcFacelets[52]};
      Facelet *bar = std::find(std::begin(foo), std::end(foo), modelFacelets[43]);
      Facelet *baz = std::find(std::begin(foo), std::end(foo), modelFacelets[52]);
      if (bar != std::end(foo) && baz != std::end(foo)) {
        edgeHeuristic += 1;
      } 
    }  
    if (cornerHeuristic/NUM_CORNERS_TOTAL < lowest_corner_heuristic) {
      lowest_corner_heuristic = cornerHeuristic/NUM_CORNERS_TOTAL;
    }
    if (edgeHeuristic/NUM_EDGES_TOTAL < lowest_edge_heuristic) {
      lowest_edge_heuristic = edgeHeuristic/NUM_EDGES_TOTAL;
    }    
  }
  if (lowest_corner_heuristic > lowest_edge_heuristic) {
    return lowest_corner_heuristic;
  }
  return lowest_edge_heuristic;
}

// current best
double Problem::CubiesHeuristic(const ai::Search::State *const state_in) const{
  const State *state = static_cast<const State *>(state_in);
  Cube model = state->getModel();
  size_t numGoalCubes = mGoalCubes.size();
  const std::vector<ai::rubiks::Facelet> modelFacelets = model.getFacelets();
  double lowest_heuristic = 1000.0;
  for (size_t i = 0; i < numGoalCubes; i++) {
    double heuristic = 0.0;
    const std::vector<ai::rubiks::Facelet> gcFacelets = mGoalCubes[i].getFacelets();
    if (gcFacelets[0] != modelFacelets[0] || gcFacelets[9] != modelFacelets[9] || gcFacelets[38] != modelFacelets[38]) {
      heuristic += 1;
    }
    if (gcFacelets[1] != modelFacelets[1] || gcFacelets[37] != modelFacelets[37]) {
      heuristic += 1;
    }        
    if (gcFacelets[2] != modelFacelets[2] || gcFacelets[29] != modelFacelets[29] || gcFacelets[36] != modelFacelets[36]) {
      heuristic += 1;
    }        
    if (gcFacelets[3] != modelFacelets[3] || gcFacelets[10] != modelFacelets[10]) {
      heuristic += 1;
    }        
    if (gcFacelets[6] != modelFacelets[6] || gcFacelets[11] != modelFacelets[11] || gcFacelets[18] != modelFacelets[18]) {
      heuristic += 1;
    }        
    if (gcFacelets[5] != modelFacelets[5] || gcFacelets[28] != modelFacelets[28]) {
      heuristic += 1;
    }        
    if (gcFacelets[8] != modelFacelets[8] || gcFacelets[20] != modelFacelets[20] || gcFacelets[27] != modelFacelets[27]) {
      heuristic += 1;
    }        
    if (gcFacelets[7] != modelFacelets[7] || gcFacelets[19] != modelFacelets[19]) {
      heuristic += 1;
    }        
    if (gcFacelets[12] != modelFacelets[12] || gcFacelets[41] != modelFacelets[41]) {
      heuristic += 1;
    }        
    if (gcFacelets[14] != modelFacelets[14] || gcFacelets[21] != modelFacelets[21]) {
      heuristic += 1;
    }        
    if (gcFacelets[23] != modelFacelets[23] || gcFacelets[30] != modelFacelets[30]) {
      heuristic += 1;
    }        
    if (gcFacelets[32] != modelFacelets[32] || gcFacelets[39] != modelFacelets[39]) {
      heuristic += 1;
    }        
    if (gcFacelets[15] != modelFacelets[15] || gcFacelets[44] != modelFacelets[44] || gcFacelets[51] != modelFacelets[51]) {
      heuristic += 1;
    }        
    if (gcFacelets[16] != modelFacelets[16] || gcFacelets[48] != modelFacelets[48]) {
      heuristic += 1;
    }        
    if (gcFacelets[17] != modelFacelets[17] || gcFacelets[24] != modelFacelets[24] || gcFacelets[45] != modelFacelets[45]) {
      heuristic += 1;
    }        
    if (gcFacelets[25] != modelFacelets[25] || gcFacelets[46] != modelFacelets[46]) {
      heuristic += 1;
    }        
    if (gcFacelets[26] != modelFacelets[26] || gcFacelets[33] != modelFacelets[33] || gcFacelets[47] != modelFacelets[47]) {
      heuristic += 1;
    }        
    if (gcFacelets[34] != modelFacelets[34] || gcFacelets[50] != modelFacelets[50]) {
      heuristic += 1;
    }        
    if (gcFacelets[35] != modelFacelets[35] || gcFacelets[42] != modelFacelets[42] || gcFacelets[53] != modelFacelets[53]) {
      heuristic += 1;
    }
    if (gcFacelets[43] != modelFacelets[43] || gcFacelets[52] != modelFacelets[52]) {
      heuristic += 1;
    }
    if (heuristic/NUM_CUBIES_TOTAL < lowest_heuristic) {
      lowest_heuristic = heuristic/NUM_CUBIES_TOTAL;
    }   
  }
  return lowest_heuristic;
}

// combining edge and corner heuristic and returning the max of the two
double Problem::CornersEdgesHeuristic(const ai::Search::State *const state_in) const{
  const State *state = static_cast<const State *>(state_in);
  Cube model = state->getModel();
  size_t numGoalCubes = mGoalCubes.size();
  const std::vector<ai::rubiks::Facelet> modelFacelets = model.getFacelets();
  double lowest_corner_heuristic = 100.0;
  double lowest_edge_heuristic = 100.0;
  for (size_t i = 0; i < numGoalCubes; i++) {
    double edgeHeuristic = 0.0;
    double cornerHeuristic = 0.0;
    const std::vector<ai::rubiks::Facelet> gcFacelets = mGoalCubes[i].getFacelets();
    if (gcFacelets[0] != modelFacelets[0] || gcFacelets[9] != modelFacelets[9] || gcFacelets[38] != modelFacelets[38]) {
      cornerHeuristic += 1;
    }
    if (gcFacelets[1] != modelFacelets[1] || gcFacelets[37] != modelFacelets[37]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[2] != modelFacelets[2] || gcFacelets[29] != modelFacelets[29] || gcFacelets[36] != modelFacelets[36]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[3] != modelFacelets[3] || gcFacelets[10] != modelFacelets[10]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[6] != modelFacelets[6] || gcFacelets[11] != modelFacelets[11] || gcFacelets[18] != modelFacelets[18]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[5] != modelFacelets[5] || gcFacelets[28] != modelFacelets[28]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[8] != modelFacelets[8] || gcFacelets[20] != modelFacelets[20] || gcFacelets[27] != modelFacelets[27]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[7] != modelFacelets[7] || gcFacelets[19] != modelFacelets[19]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[12] != modelFacelets[12] || gcFacelets[41] != modelFacelets[41]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[14] != modelFacelets[14] || gcFacelets[21] != modelFacelets[21]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[23] != modelFacelets[23] || gcFacelets[30] != modelFacelets[30]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[32] != modelFacelets[32] || gcFacelets[39] != modelFacelets[39]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[15] != modelFacelets[15] || gcFacelets[44] != modelFacelets[44] || gcFacelets[51] != modelFacelets[51]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[16] != modelFacelets[16] || gcFacelets[48] != modelFacelets[48]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[17] != modelFacelets[17] || gcFacelets[24] != modelFacelets[24] || gcFacelets[45] != modelFacelets[45]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[25] != modelFacelets[25] || gcFacelets[46] != modelFacelets[46]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[26] != modelFacelets[26] || gcFacelets[33] != modelFacelets[33] || gcFacelets[47] != modelFacelets[47]) {
      cornerHeuristic += 1;
    }        
    if (gcFacelets[34] != modelFacelets[34] || gcFacelets[50] != modelFacelets[50]) {
      edgeHeuristic += 1;
    }        
    if (gcFacelets[35] != modelFacelets[35] || gcFacelets[42] != modelFacelets[42] || gcFacelets[53] != modelFacelets[53]) {
      cornerHeuristic += 1;
    }
    if (gcFacelets[43] != modelFacelets[43] || gcFacelets[52] != modelFacelets[52]) {
      edgeHeuristic += 1;
    }  
    if (cornerHeuristic/NUM_CORNERS_TOTAL < lowest_corner_heuristic) {
      lowest_corner_heuristic = cornerHeuristic/NUM_CORNERS_TOTAL;
    }
    if (edgeHeuristic/NUM_EDGES_TOTAL < lowest_edge_heuristic) {
      lowest_edge_heuristic = edgeHeuristic/NUM_EDGES_TOTAL;
    }    
  }
  if (lowest_corner_heuristic > lowest_edge_heuristic) {
    return lowest_corner_heuristic;
  }
  return lowest_edge_heuristic;
}

double Problem::Heuristic(const ai::Search::State *const state_in) const {
  switch (mHeuristic){
    case 0:
      return 0.0;
    case 1:
      return FaceletHeuristic(state_in);
    case 2:
      return CubiesHeuristic(state_in);
    case 3:
      return CornersHeuristic(state_in);
    case 4:
      return EdgesHeuristic(state_in);
    case 5:
    {
      double c = CubiesHeuristic(state_in);
      double ce = CornersEdgesHeuristic(state_in);
      double f = FaceletHeuristic(state_in);
      if (c > ce) {
        if (f > c){
          return f;
        }
        return c;
      }
      if (f > ce) {
        return f;
      }
      return ce;
    }
  default:
    return 0.0;
  }
} // heuristic

} // namespace rubiks
} // namespace ai