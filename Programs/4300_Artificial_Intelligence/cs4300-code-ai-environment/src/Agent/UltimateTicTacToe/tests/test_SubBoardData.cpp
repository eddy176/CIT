#include "ai_ultimatetictactoe.h"
#include "gtest/gtest.h"

class UltimateTicTacToeSubBoardDataTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    subboard.Reset( );
  }
  
  virtual void TearDown( ) {
  }

  virtual void SetColumnWin( int column, int player ) {
    subboard.grid[0][column] = player;
    subboard.grid[1][column] = player;
    subboard.grid[2][column] = player;
  }

  virtual void SetRowWin( int row, int player ) {
    subboard.grid[row][0] = player;
    subboard.grid[row][1] = player;
    subboard.grid[row][2] = player;
  }

  virtual void SetDiagonalWin( int diag, int player ) {
    if( diag == 0 ) {
      subboard.grid[2][0] = player;
      subboard.grid[1][1] = player;
      subboard.grid[0][2] = player;
    } else if( diag == 1 ) { 
      subboard.grid[0][0] = player;
      subboard.grid[1][1] = player;
      subboard.grid[2][2] = player;
    }
  }

  virtual void SetAllFull( ) {
    subboard.grid[0][0] = 2;
    subboard.grid[0][1] = 1;
    subboard.grid[0][2] = 2;
    
    subboard.grid[1][0] = 1;
    subboard.grid[1][1] = 2;
    subboard.grid[1][2] = 2;
    
    subboard.grid[2][0] = 1;
    subboard.grid[2][1] = 2;
    subboard.grid[2][2] = 1;
  }

  virtual void SetAlmostFull( ) {
    subboard.grid[0][0] = 2;
    subboard.grid[0][1] = 1;
    subboard.grid[0][2] = 2;
    
    subboard.grid[1][0] = 1;
    subboard.grid[1][1] = 0;
    subboard.grid[1][2] = 2;
    
    subboard.grid[2][0] = 1;
    subboard.grid[2][1] = 2;
    subboard.grid[2][2] = 1;
  }

  /* data members */
  ai::UltimateTicTacToe::SubBoardData subboard;
};




TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneColumnOne ) {

  /* Setup */
  SetColumnWin( 0, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneColumnTwo ) {

  /* Setup */
  SetColumnWin( 1, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneColumnThree ) {

  /* Setup */
  SetColumnWin( 2, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}



TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoColumnOne ) {

  /* Setup */
  SetColumnWin( 0, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoColumnTwo ) {

  /* Setup */
  SetColumnWin( 1, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoColumnThree ) {

  /* Setup */
  SetColumnWin( 2, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}




////////////////////////////////////////////////////////////////////////

TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneRowOne ) {

  /* Setup */
  SetRowWin( 0, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneRowTwo ) {

  /* Setup */
  SetRowWin( 1, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneRowThree ) {

  /* Setup */
  SetRowWin( 2, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}



TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoRowOne ) {

  /* Setup */
  SetRowWin( 0, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoRowTwo ) {

  /* Setup */
  SetRowWin( 1, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoRowThree ) {

  /* Setup */
  SetRowWin( 2, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}





////////////////////////////////////////////////////////////////////////

TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneDiagonalOne ) {

  /* Setup */
  SetDiagonalWin( 0, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerOneDiagonalTwo ) {

  /* Setup */
  SetDiagonalWin( 1, 1 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoDiagonalOne ) {

  /* Setup */
  SetDiagonalWin( 0, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


TEST_F( UltimateTicTacToeSubBoardDataTest, WinnerTwoDiagonalTwo ) {

  /* Setup */
  SetDiagonalWin( 1, 2 );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}

///////////////////////////////////////////////////////////////////////

TEST_F( UltimateTicTacToeSubBoardDataTest, NoWinnerComplete ) {

  /* Setup */
  SetAllFull( );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( true, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeSubBoardDataTest, AlmostFullNotComplete ) {

  /* Setup */
  SetAlmostFull( );
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( false, subboard.Winner( 2 ) );
  EXPECT_EQ( false, subboard.Winner( 1 ) );
  EXPECT_EQ( false, subboard.Complete( ) );
  
  /* Tear-down */
  // Done automatically
}


