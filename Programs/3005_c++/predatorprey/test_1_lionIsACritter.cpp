#include "lion.h"
#include "lion.h"

#include "gtest/gtest.h"

class LionISACritterTest : public ::testing::Test {

protected:

    LionISACritterTest( )
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

TEST_F( LionISACritterTest, constructorSetsX ) {

/* Setup */
// Done automatically

/* Stimulus */
const Lion& lion_const = lion;

/* Comparison */
EXPECT_EQ( expected_x, lion_const.getX( ) );

/* Tear-down */
// Done automatically
}

TEST_F( LionISACritterTest, constructorSetsY ) {

/* Setup */
// Done automatically

/* Stimulus */
const Lion& lion_const = lion;

/* Comparison */
EXPECT_EQ( expected_y, lion_const.getY( ) );

/* Tear-down */
// Done automatically
}

TEST_F( LionISACritterTest, constructorSetsLionLevel ) {

/* Setup */
// Done automatically

/* Stimulus */
const Lion& lion_const = lion;

/* Comparison */
EXPECT_EQ( expected_level, lion_const.getFoodChainLevel( ) );

/* Tear-down */
// Done automatically
}

TEST_F( LionISACritterTest, constructorSetsLowestX ) {

/* Setup */
// Done automatically

/* Stimulus */
Lion lion_local( 0, 1 );

/* Comparison */
EXPECT_EQ( 0, lion_local.getX( ) );

/* Tear-down */
// Done automatically
}

TEST_F( LionISACritterTest, constructorSetsLowestY ) {

/* Setup */
// Done automatically

/* Stimulus */
Lion lion_local( 1, 0 );

/* Comparison */
EXPECT_EQ( 0, lion_local.getY( ) );

/* Tear-down */
// Done automatically
}

TEST_F( LionISACritterTest, constructorDoesNotSetBadX ) {

/* Setup */
// Done automatically

/* Stimulus */
Lion lion_local( -1, 1 );

/* Comparison */
EXPECT_EQ( 0, lion_local.getX( ) );

/* Tear-down */
// Done automatically
}

TEST_F( LionISACritterTest, constructorDoesNotSetBadY ) {

/* Setup */
// Done automatically

/* Stimulus */
Lion lion_local( 1, -1 );

/* Comparison */
EXPECT_EQ( 0, lion_local.getY( ) );

/* Tear-down */
// Done automatically
}

TEST_F( LionISACritterTest, constructorSetsAlive ) {

/* Setup */
// Done automatically

/* Stimulus */
const Lion& lion_const = lion;

/* Comparison */
EXPECT_EQ( true, lion_const.isAlive( ) );

/* Tear-down */
// Done automatically
}
