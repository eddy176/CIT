#include "ai_jetan.h"
#include "gtest/gtest.h"

class JetanBoardLocationTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    board_location.x = -1;
    board_location.y = -2;
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::Jetan::BoardLocation board_location;
};


TEST_F( JetanBoardLocationTest, StoresValues ) {

  /* Setup */
  board_location.x = -1;
  board_location.y = -2;

  
  /* Stimulus */
  int x = board_location.x;
  int y = board_location.y;
  
  /* Comparison */
  EXPECT_EQ( -1, x );
  EXPECT_EQ( -2, y );

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanBoardLocationTest, StoresPositiveValues ) {

  /* Setup */
  board_location.x = 2;
  board_location.y = 1;

  
  /* Stimulus */
  int x = board_location.x;
  int y = board_location.y;
  
  /* Comparison */
  EXPECT_EQ( 2, x );
  EXPECT_EQ( 1, y );

  /* Tear-down */
  // Done automatically
}
