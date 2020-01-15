#include "TrianglePuzzle.h"
#include "gtest/gtest.h"

class PuzzleUtilityTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    /* configure a board with 4 pieces, and 9 unique animals */
    puzzle.setSize( 2 );
    puzzle.setAnimalSize( 9 );

    char A, a;
    int k = 1;
    size_t i, j;
    size_t dst_position, dst_edge;
    bool is_board;
    A = ' ';
    a = ' ';
    for( i = 0 ; i < puzzle.getNumberOfPieces( ) ; i++ ) {
      for( j = 0; j < puzzle.getPiece( i ).size( ) ; j++ ) {
        puzzle.calcNeighbor( i, j, dst_position, dst_edge, is_board );
        puzzle.setPieceEdgeDirectly( i, j, A );
        if( is_board ) {
          puzzle.setBoardEdgeDirectly( dst_position, a );
        } else {
          puzzle.setPieceEdgeDirectly( dst_position, dst_edge, a );
        }
      }
    }
    for( i = 0 ; i < puzzle.getNumberOfPieces( ) ; i++ ) {
      for( j = 0; j < puzzle.getPiece( i ).size( ) ; j++ ) {
        if( puzzle.getPiece( i )[ j ] == ' ' ) {
          A = 'A' + k;
          a = 'a' + k;
          puzzle.calcNeighbor( i, j, dst_position, dst_edge, is_board );
          puzzle.setPieceEdgeDirectly( i, j, A );
          if( is_board ) {
            puzzle.setBoardEdgeDirectly( dst_position, a );
          } else {
            puzzle.setPieceEdgeDirectly( dst_position, dst_edge, a );
          }
          k++;
        }
      }
    }
    
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::TrianglePuzzle puzzle;
};


TEST_F( PuzzleUtilityTest, solvedIsMaxUtility ) {

  EXPECT_EQ( puzzle.maxUtility( ), puzzle.utility( ) );
  
}

TEST_F( PuzzleUtilityTest, oneRotationLosesThreeUtility ) {

  puzzle.rotate( 0, 1 );
  EXPECT_EQ( puzzle.maxUtility( ) - 3, puzzle.utility( ) );
  
}

TEST_F( PuzzleUtilityTest, oneRotationLosesThreeUtility2 ) {

  puzzle.rotate( 0, 2 );
  EXPECT_EQ( puzzle.maxUtility( ) - 3, puzzle.utility( ) );
  
}

TEST_F( PuzzleUtilityTest, fullRotationLosesNoUtility ) {

  puzzle.rotate( 0, 3 );
  EXPECT_EQ( puzzle.maxUtility( ), puzzle.utility( ) );
  
}

TEST_F( PuzzleUtilityTest, oneSwapLosesSixUtility ) {

  puzzle.swap( 1, 3 );
  EXPECT_EQ( puzzle.maxUtility( ) - 6, puzzle.utility( ) );
  
}

