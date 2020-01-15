#include "TrianglePuzzle.h"
#include "gtest/gtest.h"

class PuzzleDefaultConstructorTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::TrianglePuzzle empty_puzzle;
};

TEST_F( PuzzleDefaultConstructorTest, createsEmptyPuzzle ) {

  // Nothing to do here.  Would fail to compile without the default
  // constructor
  
}

TEST_F( PuzzleDefaultConstructorTest, setsSizeToZero ) {

  EXPECT_EQ( (size_t)0, empty_puzzle.getSize( ) );
  
}

TEST_F( PuzzleDefaultConstructorTest, setsNumberOfAnimalTypesToZero ) {

  EXPECT_EQ( (size_t)0, empty_puzzle.getAnimalSize( ) );
  
}

class PuzzleSizeConstructorTest : public ::testing::Test {
protected:

  PuzzleSizeConstructorTest( )
    : num_sides( 4 ),
      num_animal_types( 3 ),
      size_puzzle( num_sides, num_animal_types ) {
  }

  virtual void SetUp( ) {
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  size_t num_sides;
  size_t num_animal_types;
  ai::TrianglePuzzle size_puzzle;
};

TEST_F( PuzzleSizeConstructorTest, setsSizeToValue ) {

  EXPECT_EQ( num_sides, size_puzzle.getSize( ) );
  
}

TEST_F( PuzzleSizeConstructorTest, setsNumberOfAnimalTypesToValue ) {

  EXPECT_EQ( num_animal_types, size_puzzle.getAnimalSize( ) );
  
}

TEST_F( PuzzleSizeConstructorTest, setsNumberOfPieces ) {

  EXPECT_EQ( num_sides*num_sides, size_puzzle.getNumberOfPieces( ) );
  
}

