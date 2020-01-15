#include "ai_ultimatetictactoe.h"
#include "gtest/gtest.h"

class UltimateTicTacToeBoardTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    board.InitBoard( );
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::UltimateTicTacToe::Board board;
};




TEST_F( UltimateTicTacToeBoardTest, StartsWithAllLegalMoves ) {

  /* Setup */
  // Automatic
  
  /* Stimulus */
  int player = 1;
  const std::vector<ai::UltimateTicTacToe::MoveData> &moves = board.DetermineLegalMoves( player );
  
  /* Comparison */
  EXPECT_EQ( 81, (int)moves.size( ) );

  int bx,by,px,py;
  ai::UltimateTicTacToe::MoveData move;
  for( bx = 0; bx < 3; bx++ ) {
    for( by = 0; by < 3; by++ ) {
      for( px = 0; px < 3; px++ ) {
        for( py = 0; py < 3; py++ ) {
          move.setData( bx, by, px, py );
          EXPECT_EQ( true, board.IsLegal( player, move ) ) 
            << "player: " << player 
            << "  move: " << move
            << std::endl;
        }
      }
    }
  }
  
  /* Tear-down */
  // Done automatically
}


