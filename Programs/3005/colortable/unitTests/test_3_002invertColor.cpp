#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorInvertTest : public ::testing::Test {
protected:
  ColorInvertTest( )
    : color( 13, 17, 19 ), parameterized_red( 13 ), parameterized_green( 17 ), parameterized_blue( 19 ),
      max_color_value( 100 ),
      inverted_red( 87 ), inverted_green( 83 ), inverted_blue( 81 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Color color;
  int parameterized_red;
  int parameterized_green;
  int parameterized_blue;
  int max_color_value;
  int inverted_red;
  int inverted_green;
  int inverted_blue;
};

TEST_F( ColorInvertTest, invertsRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( max_color_value );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( inverted_red, color_const.getRed( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, invertsGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( max_color_value );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( inverted_green, color_const.getGreen( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, invertsBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( max_color_value );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( inverted_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, doesNotInvertTooSmall ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( 18 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

class ColorCompareTest : public ::testing::Test {
protected:
  ColorCompareTest( )
    : color( 13, 17, 19 ),
      color_same( 13, 17, 19 ),
      color_diff_red( 23, 17, 19 ),
      color_diff_green( 13, 27, 19 ),
      color_diff_blue( 13, 17, 29 ),
      color_diff_all( 23, 27, 29 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Color color;
  Color color_same;
  Color color_diff_red;
  Color color_diff_green;
  Color color_diff_blue;
  Color color_diff_all;
};


TEST_F( ColorCompareTest, comparesSame ) {

  /* Setup */
  // Done automatically

  /* Stimulus */

  /* Comparison */
  EXPECT_EQ( color_same, color );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorCompareTest, comparesConstant ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;
  const Color& color_same_const = color_same;
  bool are_same = color_const == color_same_const;

  /* Comparison */
  EXPECT_EQ( are_same, true );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorCompareTest, diffRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */

  /* Comparison */
  EXPECT_EQ( color == color_diff_red, false );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorCompareTest, diffGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */

  /* Comparison */
  EXPECT_EQ( color == color_diff_green, false );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorCompareTest, diffBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */

  /* Comparison */
  EXPECT_EQ( color == color_diff_blue, false );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorCompareTest, diffAll ) {

  /* Setup */
  // Done automatically

  /* Stimulus */

  /* Comparison */
  EXPECT_EQ( color == color_diff_all, false );

  /* Tear-down */
  // Done automatically
}
