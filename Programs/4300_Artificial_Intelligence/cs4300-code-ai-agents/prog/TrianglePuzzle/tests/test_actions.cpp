#include "TrianglePuzzle.h"
#include "gtest/gtest.h"

class PuzzleActionsTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    /* configure a board with 4 pieces, and 9 unique animals */
    puzzle.setSize( 2 );
    puzzle.setAnimalSize( 9 );
    
    rotations = puzzle.getRotateActions( );
    swaps = puzzle.getSwapActions( );
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::TrianglePuzzle puzzle;
  std::vector< std::pair< size_t, size_t > > rotations;
  std::vector< std::pair< size_t, size_t > > swaps;
};


TEST_F( PuzzleActionsTest, givesCorrectNumberOfRotationActions ) {

  EXPECT_EQ( (size_t) 8, rotations.size( ) );
  
}

TEST_F( PuzzleActionsTest, rotationsContainsFirst ) {

  std::pair< size_t, size_t > ans( 0, 1 );
  EXPECT_EQ( ans, rotations[ 0 ] );
  
}

TEST_F( PuzzleActionsTest, rotationsContainsLast ) {

  std::pair< size_t, size_t > ans( 3, 2 );
  EXPECT_EQ( ans, rotations[ 7 ] );
  
}

TEST_F( PuzzleActionsTest, givesCorrectNumberOfSwapActions ) {

  EXPECT_EQ( (size_t) 6, swaps.size( ) );
  
}

TEST_F( PuzzleActionsTest, swapsContainsFirst ) {

  std::pair< size_t, size_t > ans( 0, 1 );
  EXPECT_EQ( ans, swaps[ 0 ] );
  
}

TEST_F( PuzzleActionsTest, swapsContainsLast ) {

  std::pair< size_t, size_t > ans( 2, 3 );
  EXPECT_EQ( ans, swaps[ 5 ] );
  
}


