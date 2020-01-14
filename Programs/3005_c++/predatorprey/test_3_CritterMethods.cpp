#include "zebra.h"
#include "zebra.h"

#include "gtest/gtest.h"

class CritterMethodsTest : public ::testing::Test {

protected:

  CritterMethodsTest( )
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

TEST_F( CritterMethodsTest, constructorSetsAlive ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( true, zebra_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( CritterMethodsTest, killKillsLiveCritter ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  bool killed = zebra.kill( );
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( true, killed );
  EXPECT_EQ( false, zebra_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( CritterMethodsTest, killDoesNotKillDeadCritter ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  zebra.kill( );
  bool killed = zebra.kill( );
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( false, killed );
  EXPECT_EQ( false, zebra_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( CritterMethodsTest, setPositionChangesXAndY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  zebra.setPosition( 7, 11 );
  const Zebra& zebra_const = zebra;

  /* Comparison */
  EXPECT_EQ( 7, zebra_const.getX( ) );
  EXPECT_EQ( 11, zebra_const.getY( ) );

  /* Tear-down */
  // Done automatically
}
