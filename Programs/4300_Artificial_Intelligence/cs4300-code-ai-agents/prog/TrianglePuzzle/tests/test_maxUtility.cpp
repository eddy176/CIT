#include "TrianglePuzzle.h"
#include "gtest/gtest.h"

class PuzzleMaxUtilityTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::TrianglePuzzle puzzle;
};


TEST_F( PuzzleMaxUtilityTest, maxUtilityOfZeroSize ) {

  EXPECT_EQ( 0, puzzle.maxUtility( ) );
  
}

TEST_F( PuzzleMaxUtilityTest, maxUtilityOfOneSize ) {
  
  puzzle.setSize( 1 );
  EXPECT_EQ( 3, puzzle.maxUtility( ) );
  
}

TEST_F( PuzzleMaxUtilityTest, maxUtilityOfTwoSize ) {
  
  puzzle.setSize( 2 );
  EXPECT_EQ( 9, puzzle.maxUtility( ) );
  
}

TEST_F( PuzzleMaxUtilityTest, maxUtilityOfSixSize ) {
  
  puzzle.setSize( 6 );
  EXPECT_EQ( 63, puzzle.maxUtility( ) );
  
}

