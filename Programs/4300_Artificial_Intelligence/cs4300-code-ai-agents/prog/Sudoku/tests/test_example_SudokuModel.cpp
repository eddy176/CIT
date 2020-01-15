#include "SudokuModel.h"
#include "gtest/gtest.h"
#include <sstream>

TEST(BoardSizeConstructor, setsSize9) {
  /* Setup */
  int size = 9;
  int expected_size = size;
  int expected_box_size = 3;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  
  /* Comparison */
  EXPECT_EQ( expected_size, board.GetSize( ) );
  EXPECT_EQ( expected_box_size, board.GetBoxSize( ) );
}

TEST(BoardSizeConstructor, setsSize4) {
  /* Setup */
  int size = 4;
  int expected_size = size;
  int expected_box_size = 2;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  
  /* Comparison */
  EXPECT_EQ( expected_size, board.GetSize( ) );
  EXPECT_EQ( expected_box_size, board.GetBoxSize( ) );
}

TEST(BoardSizeConstructor, setsSize16) {
  /* Setup */
  int size = 16;
  int expected_size = size;
  int expected_box_size = 4;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  
  /* Comparison */
  EXPECT_EQ( expected_size, board.GetSize( ) );
  EXPECT_EQ( expected_box_size, board.GetBoxSize( ) );
}

TEST(BoardSizeConstructor, setsSize25) {
  /* Setup */
  int size = 25;
  int expected_size = size;
  int expected_box_size = 5;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  
  /* Comparison */
  EXPECT_EQ( expected_size, board.GetSize( ) );
  EXPECT_EQ( expected_box_size, board.GetBoxSize( ) );
}

TEST(BoardSizeConstructor, setsWildcards) {
  /* Setup */
  int size = 9;
  int expected_value = 0;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  
  /* Comparison */
  int row, col;
  for( row = 0; row < size; row++ ) {
    for( col = 0; col < size; col++ ) {
      EXPECT_EQ( expected_value, board.GetValue( row, col ) )
        << " row: " << row << " col: " << col << std::endl;
    }
  }
}


TEST(Fill, setsAllValues) {
  /* Setup */
  int size = 4;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  std::stringstream input_stream;
  input_stream.clear( );
  input_stream.str( "1 2 3 4\n. . . .\n3 . 4 9\na z . A\n" );
  board.Fill( input_stream );
  
  /* Comparison */
  EXPECT_EQ( 1, board.GetValue( 0, 0 ) );
  EXPECT_EQ( 2, board.GetValue( 0, 1 ) );
  EXPECT_EQ( 3, board.GetValue( 0, 2 ) );
  EXPECT_EQ( 4, board.GetValue( 0, 3 ) );
  
  EXPECT_EQ( 0, board.GetValue( 1, 0 ) );
  EXPECT_EQ( 0, board.GetValue( 1, 1 ) );
  EXPECT_EQ( 0, board.GetValue( 1, 2 ) );
  EXPECT_EQ( 0, board.GetValue( 1, 3 ) );
  
  EXPECT_EQ( 3, board.GetValue( 2, 0 ) );
  EXPECT_EQ( 0, board.GetValue( 2, 1 ) );
  EXPECT_EQ( 4, board.GetValue( 2, 2 ) );
  EXPECT_EQ( 9, board.GetValue( 2, 3 ) );
  
  EXPECT_EQ( 10, board.GetValue( 3, 0 ) );
  EXPECT_EQ( 35, board.GetValue( 3, 1 ) );
  EXPECT_EQ( 0, board.GetValue( 3, 2 ) );
  EXPECT_EQ( 36, board.GetValue( 3, 3 ) );
}

TEST(ToString, convertsAllValues) {
  /* Setup */
  int size = 4;
  std::string expected_string = "1234....3.49az.A";
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  std::stringstream input_stream;
  input_stream.clear( );
  input_stream.str( "1 2 3 4\n. . . .\n3 . 4 9\na z . A\n" );
  board.Fill( input_stream );
  std::string actual_string = board.ToString( );
  
  /* Comparison */
  EXPECT_EQ( expected_string, actual_string );
}

TEST(FillBox, replacesAllWildcards) {
  /* Setup */
  int size = 4;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  std::stringstream input_stream;
  input_stream.clear( );
  input_stream.str( ". . . .\n. . . .\n. . . .\n. . . .\n" );
  board.Fill( input_stream );
  board.FillBoxes( );
  
  /* Comparison */
  int row, col;
  for( row = 0; row < size; row++ ) {
    for( col = 0; col < size; col++ ) {
      EXPECT_NE( 0, board.GetValue( row, col ) )
        << " row: " << row << " col: " << col << std::endl;
    }
  }
}

TEST(FillBox, choosesCorrectValue) {
  /* Setup */
  int size = 4;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  std::stringstream input_stream;
  input_stream.clear( );
  input_stream.str( "1 . 3 4\n4 3 2 .\n. 2 1 4\n1 3 . 2\n" );
  board.Fill( input_stream );
  board.FillBoxes( );
  
  /* Comparison */
  int row, col;
  int expected_value;
  row = 0; col = 1; expected_value = 2;
  EXPECT_EQ( expected_value, board.GetValue( row, col ) )
    << " row: " << row << " col: " << col << std::endl;

  row = 1; col = 3; expected_value = 1;
  EXPECT_EQ( expected_value, board.GetValue( row, col ) )
    << " row: " << row << " col: " << col << std::endl;

  row = 2; col = 0; expected_value = 4;
  EXPECT_EQ( expected_value, board.GetValue( row, col ) )
    << " row: " << row << " col: " << col << std::endl;

  row = 3; col = 2; expected_value = 3;
  EXPECT_EQ( expected_value, board.GetValue( row, col ) )
    << " row: " << row << " col: " << col << std::endl;
}



TEST(CountConflicts, countsRowConflicts) {
  /* Setup */
  int size = 4;
  
  /* Stimulus */
  example::Sudoku::Board board( size );
  std::stringstream input_stream;
  input_stream.clear( );
  input_stream.str( "9 2 3 9\n4 a a a\n3 b b 8\nc 7 d 2\n" );
  int expected_value = 10;
  board.Fill( input_stream );
  
  /* Comparison */
  EXPECT_EQ( expected_value, board.CountConflicts( ) );
}

