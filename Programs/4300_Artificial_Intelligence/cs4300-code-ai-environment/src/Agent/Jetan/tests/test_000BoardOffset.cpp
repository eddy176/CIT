#include "ai_jetan.h"
#include "gtest/gtest.h"

class JetanBoardOffsetTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    board_offset.dx = -1;
    board_offset.dy = -2;
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::Jetan::BoardOffset board_offset;
};


TEST_F( JetanBoardOffsetTest, StoresValues ) {

  /* Setup */
  board_offset.dx = -1;
  board_offset.dy = -2;

  
  /* Stimulus */
  int dx = board_offset.dx;
  int dy = board_offset.dy;
  
  /* Comparison */
  EXPECT_EQ( -1, dx );
  EXPECT_EQ( -2, dy );

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanBoardOffsetTest, StoresPositiveValues ) {

  /* Setup */
  board_offset.dx = 2;
  board_offset.dy = 1;

  
  /* Stimulus */
  int dx = board_offset.dx;
  int dy = board_offset.dy;
  
  /* Comparison */
  EXPECT_EQ( 2, dx );
  EXPECT_EQ( 1, dy );

  /* Tear-down */
  // Done automatically
}
