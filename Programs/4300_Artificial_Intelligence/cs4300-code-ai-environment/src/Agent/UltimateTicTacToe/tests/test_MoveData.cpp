#include "ai_ultimatetictactoe.h"
#include "gtest/gtest.h"

class UltimateTicTacToeMoveDataTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    a.setData( 0, 0, 0, 0 );
    b.setData( 1, 2, 2, 1 );
    c.setData( 1, 2, 2, 1 );
    d.setData( 1, 2, 2, 2 );
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::UltimateTicTacToe::MoveData a;
  ai::UltimateTicTacToe::MoveData b;
  ai::UltimateTicTacToe::MoveData c;
  ai::UltimateTicTacToe::MoveData d;
};




TEST_F( UltimateTicTacToeMoveDataTest, lessThan1 ) {

  /* Setup */
  // Done automatically
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, a < b );
  EXPECT_EQ( true, a < c );
  EXPECT_EQ( true, a < d );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeMoveDataTest, lessThan2 ) {

  /* Setup */
  // Done automatically
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, b < d );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeMoveDataTest, lessThan3 ) {

  /* Setup */
  // Done automatically
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( true, c < d );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeMoveDataTest, notLessThan1 ) {

  /* Setup */
  // Done automatically
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( false, a < a );
  EXPECT_EQ( false, b < a );
  EXPECT_EQ( false, c < a );
  EXPECT_EQ( false, d < a );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeMoveDataTest, notLessThan2 ) {

  /* Setup */
  // Done automatically
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( false, b < b );
  EXPECT_EQ( false, c < b );
  EXPECT_EQ( false, d < b );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeMoveDataTest, notLessThan3 ) {

  /* Setup */
  // Done automatically
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( false, b < c );
  EXPECT_EQ( false, c < c );
  EXPECT_EQ( false, d < c );
  
  /* Tear-down */
  // Done automatically
}

TEST_F( UltimateTicTacToeMoveDataTest, notLessThan4 ) {

  /* Setup */
  // Done automatically
  
  /* Stimulus */
  //
  
  /* Comparison */
  EXPECT_EQ( false, d < d );
  
  /* Tear-down */
  // Done automatically
}

