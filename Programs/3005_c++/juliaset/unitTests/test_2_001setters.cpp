#include "JuliaSet.h"
#include "JuliaSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetSetterTest : public ::testing::Test {
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

    expected_width = 300;
    expected_height = 250;
    expected_min_x = -1.0;
    expected_max_x =  1.5;
    expected_min_y = -0.2;
    expected_max_y =  1.2;
    expected_a =  0.314;
    expected_b = -0.271;
    expected_max_escape_count = 123;
    js.setPixelSize( expected_width, expected_height );
    js.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
    js.setParameters( expected_a, expected_b );
    js.setMaxEscapeCount( expected_max_escape_count );
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

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  double expected_a, expected_b;
  int expected_max_escape_count;
};



TEST_F( JuliaSetSetterTest, setsValidWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPixelSize( 1, expected_height-1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPixelSize( expected_width-1, 1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMinX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, reordersMinXMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( expected_max_x, expected_min_x,
                   expected_min_y, expected_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMinY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, reordersMinYMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_max_y, expected_min_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidA ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_a, js_const.getA( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidB ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMaxEscapeCount ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxEscapeCount( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidMaxEscapeCount ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setMaxEscapeCount( -1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxEscapeCount( ) );

  /* Tear-down */
  // Done automatically
}
