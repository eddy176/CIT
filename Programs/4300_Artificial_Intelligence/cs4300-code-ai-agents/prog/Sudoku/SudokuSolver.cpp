#include "SudokuSolver.h"
#include "SudokuProblem.h"
#include "SudokuLocalProblem.h"
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include <map>


namespace example {
  namespace Sudoku {

    Exception::Exception( const std::string& msg ) 
      : std::exception(), mMsg( msg ) {
    }
    const char* Exception::what() const throw() {
      return mMsg.c_str( );
    }

    
#define GENERATION_LIMIT "generation_limit"
#define STORAGE_LIMIT "storage_limit"
#define DEPTH_LIMIT "depth_limit"
#define ASTAR_LIMIT "astar_limit"
#define BOARD_SIZE "board_size"
#define START_TEMPERATURE "start_temperature"
#define MIN_TEMPERATURE "min_temperature"
#define TEMPERATURE_REDUCTION "temperature_reduction"
#define RESOLUTION "resolution"
#define RESTART "restart"
#define POPULATION_SIZE "population_size"
#define MUTATE_PROBABILITY "mutate_probability"

void skip_to_end_of_line( std::istream& is ) {
      std::string line;
      std::getline( is, line );
    }

    void read_board( std::istream& is, std::map< std::string, double >& config, Board& board ) {
      board.Resize( static_cast< int >( config.at( BOARD_SIZE ) ) );
      board.Fill( is );
    }
    
    void show_board( const Board& board ) {
      board.ToStream( std::cout );
    }
    
    void configure( std::istream& is, std::map< std::string, double >& config ) {
      std::string word;
      double number;
      is >> word >> number;
      if ( word == GENERATION_LIMIT ) {
        config[ word ] = number;
      } else if ( word == STORAGE_LIMIT ) {
        config[ word ] = number;
      } else if ( word == DEPTH_LIMIT ) {
        config[ word ] = number;
      } else if ( word == ASTAR_LIMIT ) {
        config[ word ] = number;
      } else if ( word == BOARD_SIZE ) {
        config[ word ] = number;
      } else if ( word == START_TEMPERATURE ) {
        config[ word ] = number;
      } else if ( word == MIN_TEMPERATURE ) {
        config[ word ] = number;
      } else if ( word == TEMPERATURE_REDUCTION ) {
        config[ word ] = number;
      } else if ( word == RESOLUTION ) {
        config[ word ] = number;
      } else if ( word == RESTART ) {
        config[ word ] = number;
      } else if ( word == POPULATION_SIZE ) {
        config[ word ] = number;
      } else if ( word == MUTATE_PROBABILITY ) {
        config[ word ] = number;
      } else {
        throw Exception( std::string( "usage: config generation_limit|"
                                      "storage_limit|depth_limit|astar_limit|"
                                      "board_size|start_temperature|min_temperature|"
                                      "temperature_reduction|resolution|restart|"
                                      POPULATION_SIZE "|" MUTATE_PROBABILITY
                                      " number.\nparameter name (" ) + word + ( ") not recognized." ) );
      }
    }

    void search_board( std::istream& is, Board& board, const std::map< std::string, double >& config ) {
      std::string algorithm_word, frontier_word;
      is >> algorithm_word >> frontier_word;
      
      // initial state
      State *initial_state = new State( board );
      // problem
      Problem *problem = new Problem( initial_state );
      
      // search frontier style
      ai::Search::Frontier *frontier  = 0;
      if ( frontier_word == "astar" ) {
        frontier  = new ai::Search::AStarFrontier;
      } else if ( frontier_word == "bfs" ) {
        frontier  = new ai::Search::BFFrontier;
      } else if ( frontier_word == "dfs" ) {
        frontier  = new ai::Search::DFFrontier;
      } else if ( frontier_word == "dl" ) {
        frontier  = new ai::Search::DLFrontier( static_cast< int >( config.at( DEPTH_LIMIT ) ) );
      } else if ( frontier_word == "al" ) {
        frontier  = new ai::Search::AStarLimitedFrontier( config.at( ASTAR_LIMIT ) );
      } else if ( frontier_word == "greedy" ) {
        frontier  = new ai::Search::GreedyFrontier;
      } else if ( frontier_word == "uc" ) {
        frontier  = new ai::Search::UCFrontier;
      } else {
        delete problem;
        throw Exception( std::string( "usage: solve tree|graph astar|bfs|dfs|dl|al|greedy|uc\nfrontier name (" ) + frontier_word + ( ") not recognized." ) );
        return;
      }
      
      // search algorithm
      ai::Search::Algorithm *search = 0;
      if ( algorithm_word == "tree" ) {
        search = new ai::Search::Tree( problem, frontier );
      } else if ( algorithm_word == "graph" ) {
        search = new ai::Search::Graph( problem, frontier );
      } else {
        delete problem;
        delete frontier;
        throw Exception( std::string( "usage: solve tree|graph astar|bfs|dfs|dl|al|greedy|uc\ntree|graph not found" ) );
        return;
      }
      search->SetGenerationLimit( static_cast< int >( config.at( GENERATION_LIMIT ) ) );
      search->SetStoreLimit( static_cast< int >( config.at( STORAGE_LIMIT ) ) );
      std::cout << "solve" << " " << algorithm_word << " " << frontier_word << std::endl;
      
      // Execute the search
      if( search->Search() ) {
        std::cout << "Found solution." << std::endl;

        std::list<ai::Search::Node *> *solution = search->GetSolution().GetList();
        std::list<ai::Search::Node *>::const_iterator it;

        for( it = solution->begin( ); it != solution->end( ); it++ ) {
          if( false && (*it)->GetAction( ) ) {
            Action *action = dynamic_cast< Action * >( (*it)->GetAction( ) );
          
            std::cout << "set "
                      << action->getRow( ) << " "
                      << action->getColumn( ) << " "
                      << action->getValue( ) << std::endl;
          }
          if( (*it)->GetState( ) ) {
            State *state = dynamic_cast< State * >( (*it)->GetState( ) );
            if( state->getModel( ).IsSolved( ) ) {
              //state->getModel( ).ToStream( std::cout );
              state->getModel( ).Display( std::cout );
            }
          }
        }
      } else {
        std::cout << "Could not find solution." << std::endl;
      }

      std::cout << "Generated " << search->GetNumberNodesGenerated() << " nodes." << std::endl;
      std::cout << "Maximum frontier size " << search->GetMaxNodesStored() << " nodes." << std::endl;
      std::cout << std::endl;
      delete search;
      search = 0;
    }
    
    void local_search_board( std::istream& is, Board& board, const std::map< std::string, double >& config ) {
      std::string algorithm_word;
      is >> algorithm_word;
      
      int algorithm_type = 0;
      if( algorithm_word == "hillclimb" ) {
        algorithm_type = ai::LocalSearch::Algorithm::T_HillClimbing;
      } else if( algorithm_word == "firstchoice" ) {
        algorithm_type = ai::LocalSearch::Algorithm::T_FirstChoice;
      } else if( algorithm_word == "annealing" ) {
        algorithm_type = ai::LocalSearch::Algorithm::T_SimulatedAnnealing;
      // } else if( algorithm_word == "genetic" ) {
      //   algorithm_type = ai::LocalSearch::Algorithm::T_GeneticAlgorithm;
      } else {
        throw Exception( std::string( "usage: local hillclimb|firstchoice|annealing|genetic\nexpected search type not found" ) );
      }

      ai::LocalSearch::Problem *the_problem = new LocalProblem( board );
      ai::LocalSearch::Algorithm *the_algorithm =
        ai::LocalSearch::Algorithm::MakeAlgorithm( static_cast< ai::LocalSearch::Algorithm::AlgorithmType >( algorithm_type ), the_problem );
      the_algorithm->SetGenerationLimit( static_cast< int >( config.at( GENERATION_LIMIT ) ) );
      
      if(algorithm_type == ai::LocalSearch::Algorithm::T_SimulatedAnnealing) {
        ai::LocalSearch::SimulatedAnnealing *sa = dynamic_cast< ai::LocalSearch::SimulatedAnnealing * >( the_algorithm );
        sa->SetStartTemperature( config.at( START_TEMPERATURE ) );
        sa->SetMinimumTemperature( config.at( MIN_TEMPERATURE ) );
        sa->SetTemperatureReduction( config.at( TEMPERATURE_REDUCTION ) );
        sa->SetResolution( config.at( RESOLUTION ) );
      // } else if(algorithm_type == ai::LocalSearch::Algorithm::T_GeneticAlgorithm) {
      //   ai::LocalSearch::GeneticAlgorithm *ga = dynamic_cast< ai::LocalSearch::GeneticAlgorithm * >( the_algorithm );
      //   ga->SetPopulationSize( static_cast< int >( config.at( POPULATION_SIZE ) ) );
      //   ga->SetMutateProbability( config.at( MUTATE_PROBABILITY ) );
      }

      std::cout << "local" << " " << algorithm_word << std::endl;
      the_algorithm->RandomRestartSearch( static_cast< int >( config.at ( RESTART ) ) );

      const example::Sudoku::LocalState * const state = dynamic_cast< const example::Sudoku::LocalState * const >( the_algorithm->GetSolution( ) );
      std::cout << "Restarts:        " << the_algorithm->GetRestartCount( ) << std::endl;
      std::cout << "Nodes Generated: " << the_algorithm->GetStatesGenerated( ) << std::endl;
      std::cout << "Conflicts:       " << state->getModel( ).CountConflicts( ) << std::endl;
      state->Display( std::cout );
      delete the_algorithm;
    }
    
    void process_input_stream( std::istream& is ) {
      /* srand seeds at 100 usecond resolution */
      struct timeval time; 
      gettimeofday(&time,NULL);
      srand((time.tv_sec * 10000) + (time.tv_usec / 100));
      //std::srand( std::time( 0 ) );
      
      std::map< std::string, double > config;
      config[ GENERATION_LIMIT ] = 0;
      config[ STORAGE_LIMIT ] = 0;
      config[ DEPTH_LIMIT ] = 0;
      config[ ASTAR_LIMIT ] = 0;
      config[ BOARD_SIZE ] = 9;
      config[ START_TEMPERATURE ] = 30.0;
      config[ MIN_TEMPERATURE ] = 0.00001;
      config[ TEMPERATURE_REDUCTION ] = 100.0;
      config[ RESOLUTION ] = 100000.0;
      config[ RESTART ] = 1;
      config[ POPULATION_SIZE ] = 10;
      config[ MUTATE_PROBABILITY ] = 0.20;

      std::string word;
      example::Sudoku::Board board;
      
      while( is >> word ) {
        if( word.size( ) == 0 ) {
          // should not happen
        } else if( word[ 0 ] == '#' ) {
          skip_to_end_of_line( is );
        } else if( word == "initial" ) {
          read_board( is, config, board );
        } else if( word == "show" ) {
          show_board( board );
        } else if ( word == "search" ) { 
          search_board( is, board, config );
        } else if ( word == "local" ) { 
          local_search_board( is, board, config );
        } else if ( word == "config" ) { 
          configure( is, config );
        } else { 
          throw example::Sudoku::Exception( std::string( "Unexpected command: '" ) + word + std::string( "'." ) );
        }
      }
    }

  }
}

