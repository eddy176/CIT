#include "lion.h"
#include "lion.h"
#include "zebra.h"
#include "zebra.h"

#include "gtest/gtest.h"

class ZebraEatsTest : public ::testing::Test {

protected:

  ZebraEatsTest( )
    : zebra( 3, 4 ), expected_x( 3 ), expected_y( 4 ), expected_level( 10 ) {
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

TEST_F( ZebraEatsTest, zebraDoesNotEat ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  std::vector< Critter* > critters;
  Zebra *zebra_ptr = new Zebra( zebra.getX( ) - 1, zebra.getY( ) );
  Lion *lion_ptr = new Lion( zebra.getX( ) + 1, zebra.getY( ) );
  critters.push_back( zebra_ptr );
  critters.push_back( lion_ptr );

  /* Comparison */
  EXPECT_EQ( false, zebra.eat( critters ) );

  /* Tear-down */
  delete zebra_ptr;
  delete lion_ptr;
  // Done automatically
}
