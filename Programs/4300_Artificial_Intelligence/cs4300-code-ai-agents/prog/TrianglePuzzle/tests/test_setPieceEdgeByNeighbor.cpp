#include "TrianglePuzzle.h"
#include "gtest/gtest.h"

class PuzzleSetPieceEdgeByNeighborTest : public ::testing::Test {
protected:

  PuzzleSetPieceEdgeByNeighborTest( )
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

TEST_F( PuzzleSetPieceEdgeByNeighborTest, setsCorrectPieceTopRow ) {
  
  // Stimulus
  puzzle.setPieceEdgeByNeighbor( 0, 0, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 2 )[ 0 ] );
}

TEST_F( PuzzleSetPieceEdgeByNeighborTest, setsCorrectPieceFirstRowBottomEdge ) {
  
  // Stimulus
  puzzle.setPieceEdgeByNeighbor( 1, 0, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 5 )[ 0 ] );
}

TEST_F( PuzzleSetPieceEdgeByNeighborTest, setsCorrectPieceSecondtRowSideEdge ) {
  
  // Stimulus
  puzzle.setPieceEdgeByNeighbor( 4, 2, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 5 )[ 2 ] );
}

TEST_F( PuzzleSetPieceEdgeByNeighborTest, setsCorrectPieceSecondtRowSideEdgeUpsideDown ) {
  
  // Stimulus
  puzzle.setPieceEdgeByNeighbor( 5, 1, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 6 )[ 1 ] );
}

TEST_F( PuzzleSetPieceEdgeByNeighborTest, setsCorrectPieceSecondtRowEnd ) {
  
  // Stimulus
  puzzle.setPieceEdgeByNeighbor( 7, 1, 'Z' );

  // Test
  EXPECT_EQ( 'Z', puzzle.getPiece( 8 )[ 1 ] );
}

