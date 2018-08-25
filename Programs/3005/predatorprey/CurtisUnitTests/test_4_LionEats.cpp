#include "lion.h"
#include "lion.h"
#include "zebra.h"
#include "zebra.h"

#include "gtest/gtest.h"

class LionEatsTest : public ::testing::Test {

protected:

  LionEatsTest( )
    : lion( 3, 4 ), expected_x( 3 ), expected_y( 4 ), expected_level( 10 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Lion lion;
  int expected_x;
  int expected_y;
  int expected_level;
};

TEST_F( LionEatsTest, constructorSetsMissedMeals ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 0, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( LionEatsTest, doesNotEatWithNoNeighborPrey ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  bool result = lion.eat( critters );

  /* Comparison */
  EXPECT_EQ( false, result );

  /* Tear-down */
  // Done automatically
}

TEST_F( LionEatsTest, missesMealWithNoNeighborPrey ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 1, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( LionEatsTest, constructorSetsMissedMealsStill ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 0, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( LionEatsTest, missesManyMealWithNoNeighborPrey ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  lion.eat( critters );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 2, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( LionEatsTest, starvesWithNoNeighborPrey ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  lion.eat( critters );
  lion.eat( critters );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 3, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( false, lion_const.isAlive( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( LionEatsTest, findsPreyNorth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Zebra *zebra_ptr = new Zebra( lion.getX( ), lion.getY( ) - 1 );
  critters.push_back( zebra_ptr );
  const Lion& lion_const = lion;
  Critter *prey = lion_const.findNeighborPrey( critters );

  /* Comparison */
  EXPECT_EQ( zebra_ptr, prey );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, findsPreySouth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Zebra *zebra_ptr = new Zebra( lion.getX( ), lion.getY( ) + 1 );
  critters.push_back( zebra_ptr );
  const Lion& lion_const = lion;
  Critter *prey = lion_const.findNeighborPrey( critters );

  /* Comparison */
  EXPECT_EQ( zebra_ptr, prey );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, findsPreyEast ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Zebra *zebra_ptr = new Zebra( lion.getX( ) + 1, lion.getY( ) );
  critters.push_back( zebra_ptr );
  const Lion& lion_const = lion;
  Critter *prey = lion_const.findNeighborPrey( critters );

  /* Comparison */
  EXPECT_EQ( zebra_ptr, prey );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, findsPreyWest ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Zebra *zebra_ptr = new Zebra( lion.getX( ) - 1, lion.getY( ) );
  critters.push_back( zebra_ptr );
  const Lion& lion_const = lion;
  Critter *prey = lion_const.findNeighborPrey( critters );

  /* Comparison */
  EXPECT_EQ( zebra_ptr, prey );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, doesNotFindDeadPrey ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Zebra *zebra_ptr = new Zebra( lion.getX( ), lion.getY( ) - 1 );
  zebra_ptr->kill( );
  critters.push_back( zebra_ptr );
  const Lion& lion_const = lion;
  Critter *prey = lion_const.findNeighborPrey( critters );

  /* Comparison */
  EXPECT_EQ( 0, prey );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, doesNotFindFarPrey ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Zebra *zebra_ptr = new Zebra( lion.getX( ), lion.getY( ) - 2 );
  critters.push_back( zebra_ptr );
  const Lion& lion_const = lion;
  Critter *prey = lion_const.findNeighborPrey( critters );

  /* Comparison */
  EXPECT_EQ( 0, prey );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, doesNotFindNonPreyAsPrey ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Lion *lion_ptr = new Lion( lion.getX( ), lion.getY( ) - 1 );
  critters.push_back( lion_ptr );
  const Lion& lion_const = lion;
  Critter *prey = lion_const.findNeighborPrey( critters );

  /* Comparison */
  EXPECT_EQ( 0, prey );

  /* Tear-down */
  delete lion_ptr;
  // Done automatically
}



TEST_F( LionEatsTest, eatsNeighborNorth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  lion.eat( critters );
  Zebra *zebra_ptr = new Zebra( lion.getX( ), lion.getY( ) - 1 );
  critters.push_back( zebra_ptr );
  lion.eat( critters );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 0, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );
  EXPECT_EQ( expected_x, lion_const.getX( ) );
  EXPECT_EQ( expected_y-1, lion_const.getY( ) );
  EXPECT_EQ( false, zebra_ptr->isAlive( ) );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, eatsNeighborSouth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  lion.eat( critters );
  Zebra *zebra_ptr = new Zebra( lion.getX( ), lion.getY( ) + 1 );
  critters.push_back( zebra_ptr );
  lion.eat( critters );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 0, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );
  EXPECT_EQ( expected_x, lion_const.getX( ) );
  EXPECT_EQ( expected_y+1, lion_const.getY( ) );
  EXPECT_EQ( false, zebra_ptr->isAlive( ) );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, eatsNeighborEast ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  lion.eat( critters );
  Zebra *zebra_ptr = new Zebra( lion.getX( ) + 1, lion.getY( ) );
  critters.push_back( zebra_ptr );
  lion.eat( critters );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 0, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );
  EXPECT_EQ( expected_x+1, lion_const.getX( ) );
  EXPECT_EQ( expected_y, lion_const.getY( ) );
  EXPECT_EQ( false, zebra_ptr->isAlive( ) );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}

TEST_F( LionEatsTest, eatsNeighborWest ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  lion.eat( critters );
  lion.eat( critters );
  Zebra *zebra_ptr = new Zebra( lion.getX( ) - 1, lion.getY( ) );
  critters.push_back( zebra_ptr );
  lion.eat( critters );
  const Lion& lion_const = lion;

  /* Comparison */
  EXPECT_EQ( 0, lion_const.getMissedMealCount( ) );
  EXPECT_EQ( true, lion_const.isAlive( ) );
  EXPECT_EQ( expected_x-1, lion_const.getX( ) );
  EXPECT_EQ( expected_y, lion_const.getY( ) );
  EXPECT_EQ( false, zebra_ptr->isAlive( ) );

  /* Tear-down */
  delete zebra_ptr;
  // Done automatically
}
