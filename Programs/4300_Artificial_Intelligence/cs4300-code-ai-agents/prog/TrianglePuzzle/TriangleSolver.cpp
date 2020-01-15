#include "TrianglePuzzle.h"
#include "TriangleSolver.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>

void initializeRand( ) {
  /* srand seeds at 100 usecond resolution */
  struct timeval time; 
  gettimeofday(&time,NULL);
  srand((time.tv_sec * 10000) + (time.tv_usec / 100));
}

bool read_one_line( std::istream& is, std::vector< std::string >& words ) {
  words.clear( );
  
  std::string line;
  std::getline( is, line );
  if ( ! is ) { 
    return false;
  }
  
  std::stringstream ss( line );
  std::string word;
  while ( ss >> word ) {
    words.push_back( word );
  }
  return true;
}

void resizePuzzle( ai::TrianglePuzzle& p, const std::vector< std::string >& words ) {
  if ( words.size( ) < 2 ) {
    throw ai::Exception( std::string( "Bad resize command: '" ) + words[ 0 ] + std::string( "'." ) );
  }

  std::stringstream ss( words[ 1 ] );
  size_t size = 0;
  ss >> size;

  p.setSize( size );
}

void resizeAnimals( ai::TrianglePuzzle& p, const std::vector< std::string >& words ) {
  if ( words.size( ) < 2 ) {
    throw ai::Exception( std::string( "Bad animals command: '" ) + words[ 0 ] + std::string( "'." ) );
  }

  std::stringstream ss( words[ 1 ] );
  size_t size = 0;
  ss >> size;

  p.setAnimalSize( size );
}

void showPuzzle( std::ostream& os, const ai::TrianglePuzzle& p ) {
  os << p << std::endl;
}

void loadPuzzle( std::istream& is, ai::TrianglePuzzle& p ) {
  is >> p;
}

void shufflePuzzle( ai::TrianglePuzzle& p ) {
  p.shuffle( );
}

// solve a copy of this puzzle, show the result if solved, and any statistics
void solvePuzzle( const ai::TrianglePuzzle& p, const std::vector< std::string >& words ) {
  if ( words.size( ) < 2 ) {
    throw ai::Exception( std::string( "Bad solve command: '" ) + words[ 0 ] + std::string( "'." ) );
  }

  std::stringstream ss( words[ 1 ] );
  std::string method;
  ss >> method;

  if( method == "hillclimb" ) {
    std::cout << "Implement the hillclimb function that finds a solution to the puzzle, displays the solution and shows statistics." << std::endl;
    // hillclimb( p );
  } else {
    throw ai::Exception( std::string( "Bad solve command: '" ) + words[ 0 ] + " " + words[ 1 ] + std::string( "'." ) );
  }
}


void processInput( std::istream& is, std::ostream& os ) {
  initializeRand( );

  ai::TrianglePuzzle p( 1, 1 );
  std::vector< std::string > words;
  while( read_one_line( is, words ) ) {
    if( words.size( ) == 0 ) {
      continue;
    } else if( words[ 0 ][ 0 ] == '#' ) {
      continue;
    } else if( words[ 0 ] == "resize" ) {
      resizePuzzle( p, words );
    } else if( words[ 0 ] == "animals" ) {
      resizeAnimals( p, words );
    } else if( words[ 0 ] == "show" ) {
      showPuzzle( os, p );
    } else if( words[ 0 ] == "shuffle" ) {
      shufflePuzzle( p );
    } else if( words[ 0 ] == "load" ) {
      loadPuzzle( is, p );
    } else if( words[ 0 ] == "solve" ) {
      solvePuzzle( p, words );
    } else {
      os << "Unrecognized command: '" << words[ 0 ] << "'." << std::endl;
    }
  }

}
