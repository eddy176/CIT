#include "TrianglePuzzle.h"
#include "gtest/gtest.h"

class PuzzleSetPieceEdgeByBoardTest : public ::testing::Test {
protected:

  PuzzleSetPieceEdgeByBoardTest( )
    : num_sides( 4 ),
      num_animal_types( 3 ),
      puzzle( num_sides, num_animal_types ) {
  }
  
  virtual void SetUp( ) {
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  int num_sides;
  int num_animal_types;
  ai::TrianglePuzzle puzzle;
};

TEST_F( PuzzleSetPieceEdgeByBoardTest, setsCorrectPieceLeftTop ) {
  
  // Stimulus
  puzzle.setPieceEdgeByBoard( 0, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 0 )[ 1 ] );
}

TEST_F( PuzzleSetPieceEdgeByBoardTest, setsCorrectPieceLeftBottom ) {
  
  // Stimulus
  puzzle.setPieceEdgeByBoard( 3, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 9 )[ 1 ] );
}

TEST_F( PuzzleSetPieceEdgeByBoardTest, setsCorrectPieceRightTop ) {
  
  // Stimulus
  puzzle.setPieceEdgeByBoard( 4, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 0 )[ 2 ] );
}

TEST_F( PuzzleSetPieceEdgeByBoardTest, setsCorrectPieceRightBottom ) {
  
  // Stimulus
  puzzle.setPieceEdgeByBoard( 7, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 15 )[ 2 ] );
}

TEST_F( PuzzleSetPieceEdgeByBoardTest, setsCorrectPieceBottomLeft ) {
  
  // Stimulus
  puzzle.setPieceEdgeByBoard( 8, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 9 )[ 0 ] );
}

TEST_F( PuzzleSetPieceEdgeByBoardTest, setsCorrectPieceBottomRight ) {
  
  // Stimulus
  puzzle.setPieceEdgeByBoard( 11, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 15 )[ 0 ] );
}
