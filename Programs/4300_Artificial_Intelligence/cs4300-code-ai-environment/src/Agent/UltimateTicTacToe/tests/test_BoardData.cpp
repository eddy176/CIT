#include "ai_ultimatetictactoe.h"
#include "gtest/gtest.h"

class UltimateTicTacToeBoardDataTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    board.Reset( );
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::UltimateTicTacToe::BoardData board;
};




TEST_F( UltimateTicTacToeBoardDataTest, Resets ) {

  /* Setup */
  // Automatic
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( 0, board.num_players );
  EXPECT_EQ( 1, board.player_turn );
  EXPECT_EQ( -1, board.next_board_x );
  EXPECT_EQ( -1, board.next_board_y );
  
  /* Tear-down */
  // Done automatically
}


