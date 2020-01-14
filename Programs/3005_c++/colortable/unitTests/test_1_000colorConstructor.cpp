#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorDefaultConstructorTest : public ::testing::Test {
protected:
  ColorDefaultConstructorTest( )
    : color( ), default_red( 0 ), default_green( 0 ), default_blue( 0 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Color color;
  int default_red;
  int default_green;
  int default_blue;
};

TEST_F( ColorDefaultConstructorTest, setsDefaultRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( default_red, color_const.getRed( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorDefaultConstructorTest, setsDefaultGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( default_green, color_const.getGreen( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorDefaultConstructorTest, setsDefaultBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( default_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorDefaultConstructorTest, getChannelFetchesAllColors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( default_red, color_const.getChannel( 0 ) );
  EXPECT_EQ( default_green, color_const.getChannel( 1 ) );
  EXPECT_EQ( default_blue, color_const.getChannel( 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorDefaultConstructorTest, getChannelDoesNotFetchTooLowChannel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( -1, color_const.getChannel( -1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorDefaultConstructorTest, getChannelDoesNotFetchTooHighChannel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( -1, color_const.getChannel( 3 ) );

  /* Tear-down */
  // Done automatically
}




class ColorParameterizedConstructorTest : public ::testing::Test {
protected:
  ColorParameterizedConstructorTest( )
    : color( 13, 17, 19 ), parameterized_red( 13 ), parameterized_green( 17 ), parameterized_blue( 19 ) {
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

TEST_F( ColorParameterizedConstructorTest, setsParameterizedRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorParameterizedConstructorTest, setsParameterizedGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorParameterizedConstructorTest, setsParameterizedBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorParameterizedConstructorTest, getChannelFetchesAllColors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getChannel( 0 ) );
  EXPECT_EQ( parameterized_green, color_const.getChannel( 1 ) );
  EXPECT_EQ( parameterized_blue, color_const.getChannel( 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorParameterizedConstructorTest, getChannelDoesNotFetchTooLowChannel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( -1, color_const.getChannel( -1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorParameterizedConstructorTest, getChannelDoesNotFetchTooHighChannel ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( -1, color_const.getChannel( 3 ) );

  /* Tear-down */
  // Done automatically
}
