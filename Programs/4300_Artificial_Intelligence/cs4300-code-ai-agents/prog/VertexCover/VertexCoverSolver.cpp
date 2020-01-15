#include "VertexCoverSolver.h"
#include "VertexCoverLocalProblem.h"
#include <ctime>
#include <cstdlib>
#include <sys/time.h>
#include <map>


namespace example {
  namespace VertexCover {

    Exception::Exception( const std::string& msg ) 
      : std::exception(), mMsg( msg ) {
    }
    const char* Exception::what() const throw() {
      return mMsg.c_str( );
    }

#define GENERATION_LIMIT "generation_limit"
#define START_TEMPERATURE "start_temperature"
#define MIN_TEMPERATURE "min_temperature"
#define TEMPERATURE_REDUCTION "temperature_reduction"
#define RESOLUTION "resolution"
#define RESTART "restart"
#define MAX_TRY_COUNT "max_try_count"
    
    void skip_to_end_of_line( std::istream& is ) {
      std::string line;
      std::getline( is, line );
    }

    void read_model( std::istream& is, std::map< std::string, double >& config, Model& model ) {
      model.readGraph( is );
    }
    
    void show_model( const Model& model ) {
      std::cout << model;
    }
    
    void configure( std::istream& is, std::map< std::string, double >& config ) {
      std::string word;
      double number;
      is >> word >> number;
      if ( word == GENERATION_LIMIT ) {
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
      } else if ( word == MAX_TRY_COUNT ) {
        config[ word ] = number;
      } else {
        throw Exception( std::string( "usage: config "
                                      GENERATION_LIMIT "|"
                                      START_TEMPERATURE "|"
                                      MIN_TEMPERATURE "|"
                                      TEMPERATURE_REDUCTION "|"
                                      RESOLUTION "|"
                                      RESTART "|"
                                      MAX_TRY_COUNT
                                      " number.\nparameter name (" ) + word + ( ") not recognized." ) );
      }
    }

    void local_search_board( std::istream& is, Model& model, const std::map< std::string, double >& config ) {
      std::string algorithm_word;
      is >> algorithm_word;
      
      int algorithm_type = 0;
      if( algorithm_word == "hillclimb" ) {
        algorithm_type = ai::LocalSearch::Algorithm::T_HillClimbing;
      } else if( algorithm_word == "firstchoice" ) {
        algorithm_type = ai::LocalSearch::Algorithm::T_FirstChoice;
      } else if( algorithm_word == "annealing" ) {
        algorithm_type = ai::LocalSearch::Algorithm::T_SimulatedAnnealing;
      } else {
        throw Exception( std::string( "usage: local hillclimb|firstchoice|annealing\nexpected search type not found" ) );
      }

      ai::LocalSearch::Problem *the_problem = new LocalProblem( model, static_cast< int >( config.at( MAX_TRY_COUNT ) ) );
      ai::LocalSearch::Algorithm *the_algorithm =
        ai::LocalSearch::Algorithm::MakeAlgorithm( static_cast< ai::LocalSearch::Algorithm::AlgorithmType >( algorithm_type ), the_problem );

      if(algorithm_type == ai::LocalSearch::Algorithm::T_SimulatedAnnealing) {
        ai::LocalSearch::SimulatedAnnealing *sa = dynamic_cast< ai::LocalSearch::SimulatedAnnealing * >( the_algorithm );
        sa->SetStartTemperature( config.at( START_TEMPERATURE ) );
        sa->SetMinimumTemperature( config.at( MIN_TEMPERATURE ) );
        sa->SetTemperatureReduction( config.at( TEMPERATURE_REDUCTION ) );
        sa->SetResolution( config.at( RESOLUTION ) );
      }

      std::cout << "local" << " " << algorithm_word << std::endl;
      the_algorithm->RandomRestartSearch( static_cast< int >( config.at ( RESTART ) ) );

      const example::VertexCover::LocalState * const state = dynamic_cast< const example::VertexCover::LocalState * const >( the_algorithm->GetSolution( ) );
      std::cout << "Restarts:        " << the_algorithm->GetRestartCount( ) << std::endl;
      std::cout << "Nodes Generated: " << the_algorithm->GetStatesGenerated( ) << std::endl;
      std::cout << "Value:           " << state->getModel( ).getValue( ) << std::endl;
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
      config[ GENERATION_LIMIT ] = 1000.0;
      config[ START_TEMPERATURE ] = 30.0;
      config[ MIN_TEMPERATURE ] = 0.00001;
      config[ TEMPERATURE_REDUCTION ] = 100.0;
      config[ RESOLUTION ] = 100000.0;
      config[ RESTART ] = 1;
      config[ MAX_TRY_COUNT ] = 10000.0;

      std::string word;
      example::VertexCover::Model model;
      
      while( is >> word ) {
        if( word.size( ) == 0 ) {
          // should not happen
        } else if( word[ 0 ] == '#' ) {
          skip_to_end_of_line( is );
        } else if( word == "initial" ) {
          read_model( is, config, model );
        } else if( word == "show" ) {
          show_model( model );
        } else if ( word == "local" ) { 
          local_search_board( is, model, config );
        } else if ( word == "config" ) { 
          configure( is, config );
        } else { 
          throw example::VertexCover::Exception( std::string( "Unexpected command: '" ) + word + std::string( "'." ) );
        }
      }
    }

  }
}

