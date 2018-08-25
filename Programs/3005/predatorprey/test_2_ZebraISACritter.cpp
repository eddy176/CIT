#include "zebra.h"
#include "zebra.h"

#include "gtest/gtest.h"

class ZebraISACritterTest : public ::testing::Test {

protected:

  ZebraISACritterTest( )
    : zebra( 3, 4 ), expected_x( 3 ), expected_y( 4 ), expected_level( 5 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Zebra zebra;
  int expected_x;
  int expected_y;
  int expected_level;
};

TEST_F( ZebraISACritterTest, constructorSetsX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( expected_x, zebra_const.getX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ZebraISACritterTest, constructorSetsY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( expected_y, zebra_const.getY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ZebraISACritterTest, constructorSetsZebraLevel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( expected_level, zebra_const.getFoodChainLevel( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ZebraISACritterTest, constructorSetsLowestX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Zebra zebra_local( 0, 1 );

  /* Comparison */
  EXPECT_EQ( 0, zebra_local.getX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ZebraISACritterTest, constructorSetsLowestY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Zebra zebra_local( 1, 0 );

  /* Comparison */
  EXPECT_EQ( 0, zebra_local.getY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ZebraISACritterTest, constructorDoesNotSetBadX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Zebra zebra_local( -1, 1 );

  /* Comparison */
  EXPECT_EQ( 0, zebra_local.getX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ZebraISACritterTest, constructorDoesNotSetBadY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Zebra zebra_local( 1, -1 );

  /* Comparison */
  EXPECT_EQ( 0, zebra_local.getY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ZebraISACritterTest, constructorSetsAlive ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( true, zebra_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}
