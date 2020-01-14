#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorSetterTest : public ::testing::Test {
protected:
  ColorSetterTest( )
    : color( ), parameterized_red( 13 ), parameterized_green( 17 ), parameterized_blue( 19 ) {
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
};

TEST_F( ColorSetterTest, setsRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.setRed( parameterized_red );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, doesNotSetNegativeRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.setRed( parameterized_red );
  color.setRed( -1 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, setsGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.setGreen( parameterized_green );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, doesNotSetNegativeGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.setGreen( parameterized_green );
  color.setGreen( -1 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, setsBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.setBlue( parameterized_blue );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, doesNotSetNegativeBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.setBlue( parameterized_blue );
  color.setBlue( -1 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, setsChannel0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const int channel = 0;
  color.setChannel( channel, parameterized_red );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getChannel( channel ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, setsChannel1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const int channel = 1;
  color.setChannel( channel, parameterized_green );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_green, color_const.getChannel( channel ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, setsChannel2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const int channel = 2;
  color.setChannel( channel, parameterized_blue );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_blue, color_const.getChannel( channel ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, doesNotSetChannelTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const int channel = -1;
  color.setChannel( channel, parameterized_blue );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_NE( parameterized_blue, color_const.getChannel( channel ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, doesNotSetChannelTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const int channel = 3;
  color.setChannel( channel, parameterized_blue );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_NE( parameterized_blue, color_const.getChannel( channel ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorSetterTest, doesNotSetNegativeValuesViaChannel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.setChannel( 0, parameterized_red );
  color.setChannel( 1, parameterized_green );
  color.setChannel( 2, parameterized_blue );
  color.setChannel( 0, -2 );
  color.setChannel( 1, -1 );
  color.setChannel( 2, -100 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getChannel( 0 ) );
  EXPECT_EQ( parameterized_green, color_const.getChannel( 1 ) );
  EXPECT_EQ( parameterized_blue, color_const.getChannel( 2 ) );

  /* Tear-down */
  // Done automatically
}
