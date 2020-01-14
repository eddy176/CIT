#include "JuliaSet.h"
#include "JuliaSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetConstructorTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 400;
    default_height = 400;
    default_min_x = -2.0;
    default_max_x =  2.0;
    default_min_y = -2.0;
    default_max_y =  2.0;
    default_a = 0.0;
    default_b = 0.0;
    default_max_escape_count = 255;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  JuliaSet js;
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  double default_a, default_b;
  int default_max_escape_count;
};



TEST_F( JuliaSetConstructorTest, setsDefaultWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMinX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMinY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultA ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_a, js_const.getA( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultB ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMaxEscapeCount ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_max_escape_count, js_const.getMaxEscapeCount( ) );

  /* Tear-down */
  // Done automatically
}
