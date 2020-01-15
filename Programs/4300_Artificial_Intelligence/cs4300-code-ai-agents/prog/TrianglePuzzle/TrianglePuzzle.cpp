#include "TrianglePuzzle.h"
#include <cstdlib>
#include <iostream>

namespace ai {
  
  Exception::Exception( const std::string& msg ) 
    : std::exception(), mMsg( msg ) {
  }
  const char* Exception::what() const throw() {
    return mMsg.c_str( );
  }
  
  TrianglePuzzle::TrianglePuzzle( )
    : mSize( 0 ), mAnimalSize( 0 ) {
  }
  TrianglePuzzle::TrianglePuzzle( const size_t& size, const size_t& number_of_animal_types )
    : mSize( size ), mAnimalSize( number_of_animal_types ) {
    resizeVectors( );
    makeRandomPuzzle( );
  }
  TrianglePuzzle::TrianglePuzzle( const TrianglePuzzle& src)
    : mSize( 0 ), mAnimalSize( 0 ) {
    *this = src;
  }
  
  size_t TrianglePuzzle::getSize( ) const {
    return mSize;
  }
  size_t TrianglePuzzle::getAnimalSize( ) const {
    return mAnimalSize;
  }
  size_t TrianglePuzzle::getNumberOfPieces( ) const {
    return mPieces.size( );
  }
  const std::string TrianglePuzzle::getPiece( const size_t& number ) const {
    size_t piece_number = mPositions[ number ];
    std::string s = mPieces[ piece_number ];
    char t;
    
    switch( mRotations[ number ] ) {
    case 0: break;
    case 1:
      t = s[ 0 ];
      s[ 0 ] = s[ 2 ];
      s[ 2 ] = s[ 1 ];
      s[ 1 ] = t;
      break;
    case 2:
      t = s[ 0 ];
      s[ 0 ] = s[ 1 ];
      s[ 1 ] = s[ 2 ];
      s[ 2 ] = t;
      break;
    default:
      throw Exception( "bad rotation value" );
      break;
    }
    return s;
  }
  const std::string& TrianglePuzzle::getBoardEdge( const size_t& number ) const {
    return mBoard[ number ];
  }

  void TrianglePuzzle::setSize( const size_t& size ) {
    mSize = size;
    resizeVectors( );
    makeRandomPuzzle( );
  }
  void TrianglePuzzle::setAnimalSize( const size_t& animal_size ) {
    mAnimalSize = animal_size;
    makeRandomPuzzle( );
  }
  void TrianglePuzzle::setPiece( const size_t& number, const std::string& s ) {
    mPositions[ number ] = number;
    mRotations[ number ] = 0;
    mPieces[ number ] = s;
  }
  void TrianglePuzzle::setBoardEdge( const size_t& number, const std::string& s ) {
    mBoard[ number ] = s;
  }

  void TrianglePuzzle::shuffle( ) {
    size_t i, j;
    int t;
    for( i = 0 ; i < mPositions.size( ) ; i++ ) {
      j = std::rand( ) % mPositions.size( );
      t = mPositions[ i ];
      mPositions[ i ] = mPositions[ j ];
      mPositions[ j ] = t;
      mRotations[ i ] = std::rand( ) % 3;
    }
  }

  void TrianglePuzzle::rotate( const size_t& position, const size_t& cw_count ) {
    mRotations[ position ] += cw_count;
    mRotations[ position ] %= 3;
  }

  void TrianglePuzzle::swap( const size_t& src, const size_t& dst ) {
    size_t tmp = mPositions[ src ];
    mPositions[ src ] = mPositions[ dst ];
    mPositions[ dst ] = tmp;
  }

  std::vector< std::pair< size_t, size_t > > TrianglePuzzle::getRotateActions( ) const {
    std::vector< std::pair< size_t, size_t > > rotations;
    size_t i, j;
    for( i = 0 ; i < mRotations.size( ) ; i++ ) {
      for( j = 1 ; j <= 2 ; j++ ) {
        rotations.push_back( std::pair< size_t, size_t >( i, j ) );
      }
    }
    return rotations;
  }
  
  std::vector< std::pair< size_t, size_t > > TrianglePuzzle::getSwapActions( ) const {
    std::vector< std::pair< size_t, size_t > > swaps;
    size_t i, j;
    for( i = 0 ; i < mPositions.size( ) ; i++ ) {
      for( j = i + 1 ; j < mPositions.size( ) ; j++ ) {
        swaps.push_back( std::pair< size_t, size_t >( i, j ) );
      }
    }
    return swaps;
  }
  
  int TrianglePuzzle::utility( ) const {
    int matches = 0;
    size_t i, j;
    size_t dst_position, dst_edge;
    bool is_board;
    std::string s0, s1;
    
    char A,a;
    for( i = 0 ; i < mPieces.size( ) ; i++ ) {
      s0 = getPiece( i );
      for( j = 0 ; j < s0.size( ) ; j++ ) {
        A = s0[ j ];

        calcNeighbor( i, j, dst_position, dst_edge, is_board );
        if( is_board ) {
          a = mBoard[ dst_position ][ 0 ];
        } else if( i < dst_position ) {
          s1 = getPiece( dst_position );
          a = s1[ dst_edge ];
        } else {
          a = A; // not a match
        }
        if( std::abs(A-a) == 'a' - 'A' ) {
          matches++;
        }
      }
    }
    
    return matches;
  }

  int TrianglePuzzle::maxUtility( ) const {
    int delta = 3;
    int max = 0;
    size_t i;
    for( i = 0 ; i < mSize ; i++, delta+=3 ) {
      max += delta;
    }
    return max;
  }
  
  void TrianglePuzzle::resizeVectors( ) {
    mPieces.resize( mSize * mSize );
    mBoard.resize( 3 * mSize );
    mPositions.resize( mPieces.size( ) );
    mRotations.resize( mPieces.size( ) );
  }

  void TrianglePuzzle::makeRandomPuzzle( ) {
    /* reset all board and pieces to empty */
    size_t i, j;
    for( i = 0 ; i < mPieces.size( ) ; i++ ) {
      mPieces[ i ] = "   ";
      mPositions[ i ] = i;
      mRotations[ i ] = 0;
    }
    for( j = 0 ; j < mBoard.size( ) ; j++ ) {
      mBoard[ j ] = " ";
    }

    /* Set animals for all board edges */
    char A,a;
    for( j = 0 ; j < mBoard.size( ) ; j++ ) {
      // select animal
      chooseAnimal( A, a );

      // place animal on edge and correct piece-side
      mBoard[ j ] = A;
      setPieceEdgeByBoard( j, a );
    }

    /* Set animals for all unassigned piece edges */
    for( i = 0 ; i < mPieces.size( ) ; i++ ) {
      for( j = 0 ; j < mPieces[ i ].size( ) ; j++ ) {
        if( mPieces[ i ][ j ] == ' ' ) {
          // select animal
          chooseAnimal( A, a );
          
          // place animal on the piece's edge and correct neighbor piece edge
          mPieces[ i ][ j ] = A;
          setPieceEdgeByNeighbor( i, j, a );
        }
      }
    }
    
  }

  void TrianglePuzzle::chooseAnimal( char& A, char& a ) const {
    size_t k = 0;
    if( mAnimalSize > 0 ) {
      k = std::rand( ) % mAnimalSize;
    }
    A = 'A' + k;
    a = 'a' + k;
    // select heads/tails
    int r = std::rand( ) % 2;
    if( r == 1 ) { 
      char t = a;
      a = A;
      A = t;
    }
  }
  
  void TrianglePuzzle::setPieceEdgeByBoard( const size_t& board_pos, const char& animal ) {
    size_t piece_number = 0;
    size_t side_number = 0;

    if( board_pos < mSize ) {
      // left side
      piece_number = board_pos * board_pos;
      side_number = 1;
    } else if( board_pos < 2 * mSize ) {
      // right side
      piece_number = ( 1 + board_pos - mSize ) * ( 1 + board_pos - mSize ) - 1;
      side_number = 2;
    } else if( board_pos < 3 * mSize ) {
      // bottom side
      piece_number = ( mSize - 1 ) * ( mSize - 1 ) + 2 * ( board_pos - 2*mSize );
      side_number = 0;
    } else {
      throw Exception( "board_pos out of range." );
    }

    mPieces[ piece_number ][ side_number ] = animal;
  }


  void TrianglePuzzle::setPieceEdgeByNeighbor( const size_t& piece_number, const size_t& edge_number, const char& animal ) {
    bool is_board;
    size_t dst_piece, dst_edge;
    calcNeighbor( piece_number, edge_number, dst_piece, dst_edge, is_board );
    if( is_board ) {
      throw Exception( "Should not be a board." );
    }
    mPieces[ dst_piece ][ dst_edge ] = animal;
  }

  void TrianglePuzzle::setPieceEdgeDirectly( const size_t& piece_position, const size_t& edge_number, const char& animal ) {
    mPieces[ piece_position ][ edge_number ] = animal;
  }

  void TrianglePuzzle::setBoardEdgeDirectly( const size_t& board_position, const char& animal ) {
    mBoard[ board_position ][ 0 ] = animal;
  }
  
  void TrianglePuzzle::calcNeighbor( const size_t& position_number, const size_t& edge_number, size_t& dst_position, size_t& dst_edge, bool& is_board ) const {
    
    // what row is position_number in?
    size_t row;
    size_t row_start, row_end;
    for( row = 0; ; row++ ) {
      if( ( row + 1 ) * ( row + 1 ) > position_number ) {
        row_start = row * row;
        row_end = ( row + 1 ) * ( row + 1 ) - 1;
        break;
      }
    }
    
    // is the piece in this position pointing up?
    bool is_point_up = true;
    if( row % 2 && position_number % 2 ) {
      is_point_up = true;
    } else if( row % 2 && !( position_number % 2 ) ) {
      is_point_up = false;
    } else if( !( row % 2 ) && !( position_number % 2 ) ) {
      is_point_up = true;
    } else if( !( row % 2 ) && position_number % 2 ) {
      is_point_up = false;
    } else {
      throw Exception( "Bad is_point_up case." );
    }

    // edge and direction based calculations
    if( is_point_up ) {
      switch( edge_number ) {
      case 0: {
        // next row
        if( row < mSize - 1 ) {
          dst_position = position_number + ( ( row + 1 ) * 2 );
          dst_edge = 0;
          is_board = false;
        } else {
          dst_position = 2 * mSize + ( position_number - row_start ) / 2;
          is_board = true;
        }
      } break;
      case 1: {
        // left
        if( position_number > row_start ) {
          dst_position = position_number - 1;
          dst_edge = 1;
          is_board = false;
        } else {
          dst_position = row;
          is_board = true;
        }
      } break;
      case 2: {
        // right
        if( position_number < row_end ) {
          dst_position = position_number + 1;
          dst_edge = 2;
          is_board = false;
        } else {
          dst_position = mSize + row;
          is_board = true;
        }
      } break;
      default:
        throw Exception( "Bad edge_number case." );
        break;
      }
    } else {
      switch( edge_number ) {
      case 0: {
        // prev row
        dst_position = position_number - ( row * 2 );
        dst_edge = 0;
        is_board = false;
      } break;
      case 1: {
        // right
        dst_position = position_number + 1;
        dst_edge = 1;
        is_board = false;
      } break;
      case 2: {
        // left
        dst_position = position_number - 1;
        dst_edge = 2;
        is_board = false;
      } break;
      default:
        throw Exception( "Bad edge_number case." );
        break;
      }
    }
  }

  std::ostream& operator<<( std::ostream& os, const TrianglePuzzle& p ) {
    os << p.getSize( ) << std::endl;
    os << p.getAnimalSize( ) << std::endl;
    size_t i, j;
    for( i = 0 ; i < p.getNumberOfPieces( ) ; i++ ) {
      os << p.getPiece( i ) << std::endl;
    }
    for( j = 0 ; j < 3 * p.getSize( ) ; j++ ) {
      os << p.getBoardEdge( j ) << std::endl;
    }
    return os;
  }

  std::istream& operator>>( std::istream& is, TrianglePuzzle& p ) {
    size_t size, animal_size;
    is >> size >> animal_size;
    p.setSize( size );
    p.setAnimalSize( animal_size );

    size_t i, j;
    std::string s;
    for( i = 0 ; i < p.getNumberOfPieces( ) ; i++ ) {
      is >> s;
      p.setPiece( i, s );
    }
    for( j = 0 ; j < 3 * p.getSize( ) ; j++ ) {
      is >> s;
      p.setBoardEdge( j, s );
    }
    
    return is;
  }
  
}
