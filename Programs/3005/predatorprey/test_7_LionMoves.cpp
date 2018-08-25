#include "lion.h"
#include "lion.h"
#include "zebra.h"
#include "zebra.h"

#include "gtest/gtest.h"

class LionMovesTest : public ::testing::Test {

protected:

  LionMovesTest( )
    : lion( 2, 3 ), original_x( 2 ), original_y( 3 ), width( 4 ), height( 5 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Lion lion;
  int original_x, original_y;
  int width, height;
};

TEST_F( LionMovesTest, moves ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( true, did_move );
  if( lion_const.getX( ) == original_x ) {
    EXPECT_NE( original_y, lion_const.getY( ) );
  } else if( lion_const.getY( ) == original_y ) {
    EXPECT_NE( original_x, lion_const.getX( ) );
  } else {
    EXPECT_EQ( true, lion_const.getX( ) == original_x || lion_const.getY( ) == original_y );
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( LionMovesTest, movesNorth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y+1 );
  Lion *l1 = new Lion( original_x+1, original_y );
  Lion *l2 = new Lion( original_x-1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( true, did_move );
  EXPECT_EQ( original_x, lion_const.getX( ) );
  EXPECT_EQ( original_y-1, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, movesSouth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y-1 );
  Lion *l1 = new Lion( original_x+1, original_y );
  Lion *l2 = new Lion( original_x-1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( true, did_move );
  EXPECT_EQ( original_x, lion_const.getX( ) );
  EXPECT_EQ( original_y+1, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, movesEast ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y-1 );
  Lion *l1 = new Lion( original_x, original_y+1 );
  Lion *l2 = new Lion( original_x-1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( true, did_move );
  EXPECT_EQ( original_x+1, lion_const.getX( ) );
  EXPECT_EQ( original_y, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, movesWest ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y-1 );
  Lion *l1 = new Lion( original_x, original_y+1 );
  Lion *l2 = new Lion( original_x+1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( true, did_move );
  EXPECT_EQ( original_x-1, lion_const.getX( ) );
  EXPECT_EQ( original_y, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, doesNotMoveWhenSurrounded ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y-1 );
  Lion *l1 = new Lion( original_x, original_y+1 );
  Lion *l2 = new Lion( original_x+1, original_y );
  Lion *l3 = new Lion( original_x-1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  critters.push_back( l3 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( false, did_move );
  EXPECT_EQ( original_x, lion_const.getX( ) );
  EXPECT_EQ( original_y, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  delete l3;
  // Done automatically
}


TEST_F( LionMovesTest, doesNotMoveNorthOutOfRange ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  original_y = 0;
  lion.setPosition( original_x, original_y );
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y+1 );
  Lion *l1 = new Lion( original_x+1, original_y );
  Lion *l2 = new Lion( original_x-1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( false, did_move );
  EXPECT_EQ( original_x, lion_const.getX( ) );
  EXPECT_EQ( original_y, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, doesNotMoveSouthOutOfRange ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  original_y = height-1;
  lion.setPosition( original_x, original_y );
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y-1 );
  Lion *l1 = new Lion( original_x+1, original_y );
  Lion *l2 = new Lion( original_x-1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( false, did_move );
  EXPECT_EQ( original_x, lion_const.getX( ) );
  EXPECT_EQ( original_y, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, doesNotMoveEastOutOfRange ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  original_x = width-1;
  lion.setPosition( original_x, original_y );
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y+1 );
  Lion *l1 = new Lion( original_x, original_y-1 );
  Lion *l2 = new Lion( original_x-1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( false, did_move );
  EXPECT_EQ( original_x, lion_const.getX( ) );
  EXPECT_EQ( original_y, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, doesNotMoveWestOutOfRange ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  original_x = 0;
  lion.setPosition( original_x, original_y );
  std::vector< Critter* > critters;
  Lion *l0 = new Lion( original_x, original_y+1 );
  Lion *l1 = new Lion( original_x, original_y-1 );
  Lion *l2 = new Lion( original_x+1, original_y );
  critters.push_back( l0 );
  critters.push_back( l1 );
  critters.push_back( l2 );
  bool did_move = lion.move( critters, width, height );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( false, did_move );
  EXPECT_EQ( original_x, lion_const.getX( ) );
  EXPECT_EQ( original_y, lion_const.getY( ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( LionMovesTest, deadLionDoesNotMove ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  lion.eat( critters );
  lion.eat( critters );
  EXPECT_EQ( false, lion.isAlive( ) );
  bool did_move = lion.move( critters, width, height );

  /* Comparison */
  EXPECT_EQ( false, did_move );

  /* Tear-down */
  // Done automatically
}
