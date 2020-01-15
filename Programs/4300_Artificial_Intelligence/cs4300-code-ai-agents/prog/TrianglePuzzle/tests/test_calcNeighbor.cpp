#include "TrianglePuzzle.h"
#include "gtest/gtest.h"

class PuzzleCalcNeighborTest : public ::testing::Test {
protected:

  PuzzleCalcNeighborTest( )
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

  size_t dst_position, dst_edge;
  bool is_board;

};

TEST_F( PuzzleCalcNeighborTest, calcsTopPieceLeft ) {
  
  // Stimulus
  puzzle.calcNeighbor( 0, 1, dst_position, dst_edge, is_board );

  // Test
  EXPECT_EQ( true, is_board );
  EXPECT_EQ( (size_t)0, dst_position );
}

TEST_F( PuzzleCalcNeighborTest, calcsTopPieceRight ) {
  
  // Stimulus
  puzzle.calcNeighbor( 0, 2, dst_position, dst_edge, is_board );

  // Test
  EXPECT_EQ( true, is_board );
  EXPECT_EQ( (size_t)num_sides, dst_position );
}


TEST_F( PuzzleCalcNeighborTest, calcsTopPieceDown ) {
  
  // Stimulus
  puzzle.calcNeighbor( 0, 0, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)2, dst_position );
  EXPECT_EQ( (size_t)0, dst_edge );
}

TEST_F( PuzzleCalcNeighborTest, calcsLeftPieceLeft ) {
  
  // Stimulus
  puzzle.calcNeighbor( 4, 1, dst_position, dst_edge, is_board );

  // Test
  EXPECT_EQ( true, is_board );
  EXPECT_EQ( (size_t)2, dst_position );
}

TEST_F( PuzzleCalcNeighborTest, calcsLeftPieceRight ) {
  
  // Stimulus
  puzzle.calcNeighbor( 4, 2, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)5, dst_position );
  EXPECT_EQ( (size_t)2, dst_edge );
}

TEST_F( PuzzleCalcNeighborTest, calcsLeftPieceDown ) {
  
  // Stimulus
  puzzle.calcNeighbor( 4, 0, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)10, dst_position );
  EXPECT_EQ( (size_t)0, dst_edge );
}

TEST_F( PuzzleCalcNeighborTest, calcsRightPieceRight ) {
  
  // Stimulus
  puzzle.calcNeighbor( 8, 2, dst_position, dst_edge, is_board );

  // Test
  EXPECT_EQ( true, is_board );
  EXPECT_EQ( (size_t)6, dst_position );
}

TEST_F( PuzzleCalcNeighborTest, calcsRightPieceLeft ) {
  
  // Stimulus
  puzzle.calcNeighbor( 8, 1, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)7, dst_position );
  EXPECT_EQ( (size_t)1, dst_edge );
}

TEST_F( PuzzleCalcNeighborTest, calcsRightPieceDown ) {
  
  // Stimulus
  puzzle.calcNeighbor( 8, 0, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)14, dst_position );
  EXPECT_EQ( (size_t)0, dst_edge );
}


TEST_F( PuzzleCalcNeighborTest, calcsBottomPieceDown ) {
  
  // Stimulus
  puzzle.calcNeighbor( 11, 0, dst_position, dst_edge, is_board );

  // Test
  EXPECT_EQ( true, is_board );
  EXPECT_EQ( (size_t)9, dst_position );
}

TEST_F( PuzzleCalcNeighborTest, calcsPointDownPieceUp ) {
  
  // Stimulus
  puzzle.calcNeighbor( 10, 0, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)4, dst_position );
  EXPECT_EQ( (size_t)0, dst_edge );
}

TEST_F( PuzzleCalcNeighborTest, calcsPointDownPieceLeft ) {
  
  // Stimulus
  puzzle.calcNeighbor( 10, 2, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)9, dst_position );
  EXPECT_EQ( (size_t)2, dst_edge );
}

TEST_F( PuzzleCalcNeighborTest, calcsPointDownPieceRight ) {
  
  // Stimulus
  puzzle.calcNeighbor( 10, 1, dst_position, dst_edge, is_board );

  // Test
  EXPECT_FALSE( is_board );
  EXPECT_EQ( (size_t)11, dst_position );
  EXPECT_EQ( (size_t)1, dst_edge );
}

