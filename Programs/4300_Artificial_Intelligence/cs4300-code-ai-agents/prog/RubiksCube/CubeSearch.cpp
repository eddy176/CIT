#include "CubeAppData.h"
/////////////////////////////
#include "CubeAction.h"
#include "CubeProblem.h"
#include "CubeState.h"
#include "ai_search.h"
////////////////////////////
#include "CubeAppCommand.h"
#include "CubeSearch.h"
#include <exception>
#include <iostream>
#include <sstream>

namespace ai {
namespace rubiks {

/*********************************************
 * Solving
 */
static int create_search_frontier(AppData &data,
                ai::Search::Frontier **frontier) {
  if (data.words.size() < 3) {
    return EXIT_USAGE;
  }
  *frontier = 0;
  if (data.words[2] == "astar") {
    *frontier = new ai::Search::AStarFrontier;
  } else if (data.words[2] == "bfs") {
    *frontier = new ai::Search::BFFrontier;
  } else if (data.words[2] == "dfs") {
    *frontier = new ai::Search::DFFrontier;
  } else if (data.words[2] == "dl") {
    *frontier = new ai::Search::DLFrontier(data.config.depthLimit());
  } else if (data.words[2] == "ids") {
    *frontier = new ai::Search::DLFrontier(data.config.idsDepth());
  } else if (data.words[2] == "al") {
    *frontier = new ai::Search::AStarLimitedFrontier(data.config.aStarLimit());
  } else if (data.words[2] == "greedy") {
    *frontier = new ai::Search::GreedyFrontier;
  } else if (data.words[2] == "uc") {
    *frontier = new ai::Search::UCFrontier;
  } else {
    return EXIT_USAGE;
  }
  return EXIT_OK;
}

// chooses between tree and graph
static int create_search_algorithm(AppData &data, ai::Search::Problem *problem,
                                   ai::Search::Frontier *frontier,
                                   ai::Search::Algorithm **algorithm) {
  if (data.words.size() < 2) {
    return EXIT_USAGE;
  }
  *algorithm = 0;

  if (data.words[1] == "tree") {
    *algorithm = new ai::Search::Tree(problem, frontier);
  } else if (data.words[1] == "graph") {
    *algorithm = new ai::Search::Graph(problem, frontier);
  } else {
    return EXIT_USAGE;
  }
  (*algorithm)->SetGenerationLimit(data.config.generationLimit());
  (*algorithm)->SetStoreLimit(data.config.storageLimit());

  return EXIT_OK;
}

static int search_init(AppData &data, ai::Search::Algorithm **algorithm) {
  // initial state
  ai::Search::State *initial_state = new ai::rubiks::State(data.cube);
  // problem
  Problem *problem = new Problem(initial_state, data.goal_cubes);
  // will be configuring this later
  // const std::map<std::string, Move> goalCubes = static_cast<const std::map<std::string, Move>>(data.move_set.getDefinedMoves());

  problem->setHeuristic( static_cast<Problem::HeuristicEnum> (data.config.heuristic()));

  problem->setAllowedMoves(data.move_set.getMoves());
  int ok;

  // search frontier style
  ai::Search::Frontier *frontier = 0;
  ok = create_search_frontier(data, &frontier);
  if (ok != EXIT_OK) {
    delete problem;
    return ok;
  }

  // search algorithm
  ok = create_search_algorithm(data, problem, frontier, algorithm);
  if (ok != EXIT_OK) {
    delete problem;
    delete frontier;
    return ok;
  }

  return EXIT_OK;
}

static int search_aux(AppData &data) {
  int max_iterations = 1;
  if (data.words.size() > 2 && data.words[2] == "ids") {
    max_iterations = data.config.idsLimit();
  }

  int i;
  bool solved = false;
  std::stringstream machine_stream;
  unsigned int generated_nodes = 0;
  size_t stored_nodes = 0;
  double cost = 0.0;
  std::stringstream moves;

  if (data.config.displaySolutionMachine()) {
    machine_stream << data.words[0] << " " << data.words[1] << " "
                   << data.words[2] << " ";
  }

  for (i = 1; i <= max_iterations && !solved; i++) {
    data.config.setIDSDepth(i);

    ai::Search::Algorithm *algorithm = 0;
    int ok = EXIT_THROW;
    if (data.words[0] == "search") {
      ok = search_init(data, &algorithm);
    } else {
      data.os << "Only search understood." << std::endl;
      ok = EXIT_THROW;
    }
    if (ok != EXIT_OK) {
      return ok;
    }

    if (data.config.displaySolutionHuman()) {
      data.os << data.words[0] << " " << data.words[1] << " " << data.words[2]
              << std::endl;
    }

    // Execute the search
    if (algorithm->Search()) {
      bool first = true;
      cost = 0.0;
      solved = true;
      if (data.config.displaySolutionHuman()) {
        data.os << "Found solution." << std::endl;
      }

      std::list<ai::Search::Node *> *solution =
          algorithm->GetSolution().GetList();
      std::list<ai::Search::Node *>::const_iterator it;

      for (it = solution->begin(); it != solution->end(); it++) {
        if ((*it)->GetAction()) {
          ai::rubiks::Action *action =
              dynamic_cast<ai::rubiks::Action *>((*it)->GetAction());
          if (!first) {
            moves << " ";
          } else {
            first = false;
          }
          moves << *action;
          if (data.config.applySolution()) {
            Cube cube2 = data.cube;
            data.cube.applyMove(action->getMove(), cube2);
          }

          cost += action->getMove().getCost();
        }
        /*
          if( (*it)->GetState( ) ) {
            ai::rectangle::State *state = dynamic_cast< ai::rectangle::State *
          >( (*it)->GetState( ) ); data.os << "rectangle: " << *state <<
          std::endl;
          }
          */
      }
      if (data.config.displaySolutionHuman()) {
        data.os << "rotate " << moves.str() << std::endl;
        data.os << "Cost: " << cost << std::endl;
        data.os << "Generated " << algorithm->GetNumberNodesGenerated()
                << " nodes." << std::endl;
        data.os << "Maximum frontier size " << algorithm->GetMaxNodesStored()
                << " nodes." << std::endl;
        data.os << std::endl;
      }
      if (data.config.displaySolutionMachine()) {
        generated_nodes += algorithm->GetNumberNodesGenerated();
        stored_nodes = std::max(stored_nodes, algorithm->GetMaxNodesStored());
      }
    } else {
      if (data.config.displaySolutionHuman()) {
        data.os << "Could not find solution." << std::endl;
        data.os << "Generated " << algorithm->GetNumberNodesGenerated()
                << " nodes." << std::endl;
        data.os << "Maximum frontier size " << algorithm->GetMaxNodesStored()
                << " nodes." << std::endl;
        data.os << std::endl;
      }
      if (data.config.displaySolutionMachine()) {
        generated_nodes += algorithm->GetNumberNodesGenerated();
        stored_nodes = std::max(stored_nodes, algorithm->GetMaxNodesStored());
      }
    }

    delete algorithm;
    algorithm = 0;
  }

  if (data.config.displaySolutionMachine()) {
    if (!solved) {
      machine_stream << "F " << generated_nodes << " " << stored_nodes;
    } else {
      machine_stream << "T " << generated_nodes << " " << stored_nodes << " ";
      machine_stream << cost << " ";
      machine_stream << "rotate " << moves.str();
    }
    data.os << machine_stream.str() << std::endl;
  }
  return EXIT_OK;
}

int search(AppData &data) { return search_aux(data); }
} // namespace rubiks
} // namespace ai
/*
 * Solving
 *********************************************/
