#include "lion.h"
#include "lion.h"
#include "zebra.h"
#include "zebra.h"

#include "gtest/gtest.h"

class PositionAvailableTest : public ::testing::Test {

protected:

  PositionAvailableTest( )
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

TEST_F( PositionAvailableTest, available ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;


  /* Comparison */
  EXPECT_EQ( true, lion.positionAvailable( original_x-1, original_y-1, critters, width, height ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PositionAvailableTest, availableNorth ) {

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

  /* Comparison */
  EXPECT_EQ( true, lion.positionAvailable( original_x, original_y-1, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( PositionAvailableTest, availableSouth ) {

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

  /* Comparison */
  EXPECT_EQ( true, lion.positionAvailable( original_x, original_y+1, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( PositionAvailableTest, availableEast ) {

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

  /* Comparison */
  EXPECT_EQ( true, lion.positionAvailable( original_x+1, original_y, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( PositionAvailableTest, availableWest ) {

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

  /* Comparison */
  EXPECT_EQ( true, lion.positionAvailable( original_x-1, original_y, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( PositionAvailableTest, notAvailableOccupied ) {

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

  /* Comparison */
  EXPECT_EQ( false, lion.positionAvailable( original_x, original_y-1, critters, width, height ) );
  EXPECT_EQ( false, lion.positionAvailable( original_x, original_y+1, critters, width, height ) );
  EXPECT_EQ( false, lion.positionAvailable( original_x+1, original_y, critters, width, height ) );
  EXPECT_EQ( false, lion.positionAvailable( original_x-1, original_y, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  delete l3;
  // Done automatically
}


TEST_F( PositionAvailableTest, notAvailableNorthOutOfRange ) {

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

  /* Comparison */
  EXPECT_EQ( false, lion.positionAvailable( original_x, original_y-1, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( PositionAvailableTest, notAvaiableSouthOutOfRange ) {

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

  /* Comparison */
  EXPECT_EQ( false, lion.positionAvailable( original_x, original_y+1, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( PositionAvailableTest, notAvaiableEastOutOfRange ) {

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

  /* Comparison */
  EXPECT_EQ( false, lion.positionAvailable( original_x+1, original_y, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}

TEST_F( PositionAvailableTest, notAvaiableWestOutOfRange ) {

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

  /* Comparison */
  EXPECT_EQ( false, lion.positionAvailable( original_x-1, original_y, critters, width, height ) );

  /* Tear-down */
  delete l0;
  delete l1;
  delete l2;
  // Done automatically
}
