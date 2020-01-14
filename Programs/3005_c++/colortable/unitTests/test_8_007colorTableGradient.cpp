#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorTableGradientTest : public ::testing::Test {
protected:
  ColorTableGradientTest( )
    : color_table( 8 ),
      expected_color_0{ 255, 254, 253 },
      expected_color_1{ 249, 248, 247 },
      expected_color_2{ 200,   0,  50 },
      expected_color_3{ 170,  15,  49 },
      expected_color_4{ 140,  30,  48 },
      expected_color_5{ 110,  45,  47 },
      expected_color_6{  80,  60,  46 },
      expected_color_7{ 252, 251, 250 },
      gradient_1{ 200,  0, 50 },
      gradient_2{  80, 60, 46 } {
  }

  virtual void SetUp( ) {
    color_table[ 0 ] = expected_color_0;
    color_table[ 1 ] = expected_color_1;
    color_table[ 2 ] = expected_color_1;
    color_table[ 3 ] = expected_color_1;
    color_table[ 4 ] = expected_color_1;
    color_table[ 5 ] = expected_color_1;
    color_table[ 6 ] = expected_color_1;
    color_table[ 7 ] = expected_color_7;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  ColorTable color_table;
  Color expected_color_0;
  Color expected_color_1;
  Color expected_color_2;
  Color expected_color_3;
  Color expected_color_4;
  Color expected_color_5;
  Color expected_color_6;
  Color expected_color_7;
  Color gradient_1, gradient_2;
};

TEST_F( ColorTableGradientTest, setsGradientColors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.insertGradient( gradient_1, gradient_2, 2, 6 );

  /* Comparison */
  EXPECT_EQ( expected_color_2, color_table[ 2 ] );
  EXPECT_EQ( expected_color_3, color_table[ 3 ] );
  EXPECT_EQ( expected_color_4, color_table[ 4 ] );
  EXPECT_EQ( expected_color_5, color_table[ 5 ] );
  EXPECT_EQ( expected_color_6, color_table[ 6 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableGradientTest, doesNotChangeOtherColors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.insertGradient( gradient_1, gradient_2, 2, 6 );

  /* Comparison */
  EXPECT_EQ( expected_color_0, color_table[ 0 ] );
  EXPECT_EQ( expected_color_1, color_table[ 1 ] );
  EXPECT_EQ( expected_color_7, color_table[ 7 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableGradientTest, doesNotChangeIfPositionsOutOfOrder ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.insertGradient( gradient_1, gradient_2, 6, 2 );

  /* Comparison */
  EXPECT_EQ( expected_color_0, color_table[ 0 ] );
  EXPECT_EQ( expected_color_1, color_table[ 1 ] );
  EXPECT_EQ( expected_color_1, color_table[ 2 ] );
  EXPECT_EQ( expected_color_1, color_table[ 3 ] );
  EXPECT_EQ( expected_color_1, color_table[ 4 ] );
  EXPECT_EQ( expected_color_1, color_table[ 5 ] );
  EXPECT_EQ( expected_color_1, color_table[ 6 ] );
  EXPECT_EQ( expected_color_7, color_table[ 7 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableGradientTest, doesNotChangeIfPositionsAreSame ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.insertGradient( gradient_1, gradient_2, 3, 3 );

  /* Comparison */
  EXPECT_EQ( expected_color_0, color_table[ 0 ] );
  EXPECT_EQ( expected_color_1, color_table[ 1 ] );
  EXPECT_EQ( expected_color_1, color_table[ 2 ] );
  EXPECT_EQ( expected_color_1, color_table[ 3 ] );
  EXPECT_EQ( expected_color_1, color_table[ 4 ] );
  EXPECT_EQ( expected_color_1, color_table[ 5 ] );
  EXPECT_EQ( expected_color_1, color_table[ 6 ] );
  EXPECT_EQ( expected_color_7, color_table[ 7 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableGradientTest, setsGradientColorsWithFractionalGapSize ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Color g1( 0, 0, 0 );
  Color g2( 200, 200, 200 );
  int   p1 = 2;
  int   p2 = 5;
  color_table.insertGradient( g1, g2, p1, p2 );
  Color e2( 0, 0, 0 );
  Color e3( 66, 66, 66 );
  Color e4( 133, 133, 133 );
  Color e5( 200, 200, 200 );

  /* Comparison */
  EXPECT_EQ( e2, color_table[ 2 ] );
  EXPECT_EQ( e3, color_table[ 3 ] );
  EXPECT_EQ( e4, color_table[ 4 ] );
  EXPECT_EQ( e5, color_table[ 5 ] );

  /* Tear-down */
  // Done automatically
}
