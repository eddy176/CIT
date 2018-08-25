#include "JuliaSet.h"
#include "JuliaSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetEscapeTest : public ::testing::Test {
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



TEST_F( JuliaSetEscapeTest, calculatesNextPoint1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0, x1, y1;
  x0 = 1.0;
  y0 = -1.0;
  double expected_x1 = x0*x0 - y0*y0 + expected_a;
  double expected_y1 = 2*x0*y0 + expected_b;
  js_const.calculateNextPoint( x0, y0, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesNextPoint2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0, x1, y1;
  x0 = -1.0;
  y0 = 1.0;
  double expected_x1 = x0*x0 - y0*y0 + expected_a;
  double expected_y1 = 2*x0*y0 + expected_b;
  js_const.calculateNextPoint( x0, y0, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesNextPoint3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0, x1, y1;
  x0 = -0.3;
  y0 = 0.2;
  double expected_x1 = x0*x0 - y0*y0 + expected_a;
  double expected_y1 = 2*x0*y0 + expected_b;
  js_const.calculateNextPoint( x0, y0, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesNextPoint4 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0, x1, y1;
  x0 = 3.1;
  y0 = 2.2;
  double expected_x1 = x0*x0 - y0*y0 + expected_a;
  double expected_y1 = 2*x0*y0 + expected_b;
  js_const.calculateNextPoint( x0, y0, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount0_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 = 0.1;
  y0 = 2.0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount0_1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 = 0.1;
  y0 = -2.0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount0_2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 = -2.0;
  y0 =  0.1;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount0_3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 =  2.0;
  y0 =  0.1;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount1_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 = 0.0;
  y0 = 2.0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount1_1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 = 0.0;
  y0 = -2.0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount1_2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 = -2.0;
  y0 =  0.0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCount1_3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 =  2.0;
  y0 =  0.0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPlaneEscapeCountMax_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x0, y0;
  x0 =  0.0;
  y0 =  0.0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_escape_count, js_const.calculatePlaneEscapeCount( x0, y0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPixelEscapeCount_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = 0, column = 0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPixelEscapeCount_1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = 0, column = expected_width - 1;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPixelEscapeCount_2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = expected_height - 1, column = 0;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 3, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPixelEscapeCount_3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = expected_height - 1, column = expected_width - 1;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPixelEscapeCount_4 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = expected_height/2, column = expected_width/2;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_escape_count, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesPixelEscapeCount_5 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPixelSize( 200, 200 );
  js.setPlaneSize( -2.0, 2.0, -2.0, 2.0 );
  js.setParameters( 0.314, -0.271 );
  js.setMaxEscapeCount( 3 );
  int row = 80, column = 170;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, doesNotCalculatesPixelEscapeCountRowTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = -1, column = expected_width/2;

  /* Comparison */
  EXPECT_DOUBLE_EQ( -1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, doesNotCalculatesPixelEscapeCountRowTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = expected_height, column = expected_width/2;

  /* Comparison */
  EXPECT_DOUBLE_EQ( -1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, doesNotCalculatesPixelEscapeCountColumnTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = expected_height/2, column = -1;

  /* Comparison */
  EXPECT_DOUBLE_EQ( -1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, doesNotCalculatesPixelEscapeCountColumnTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  int row = expected_height/2, column = expected_width;

  /* Comparison */
  EXPECT_DOUBLE_EQ( -1, js_const.calculatePixelEscapeCount( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetEscapeTest, calculatesAllEscapeCounts ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.calculateAllEscapeCounts( );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 1, js_const.getPixelEscapeCount( 0, 0 ) );
  EXPECT_DOUBLE_EQ( 3, js_const.getPixelEscapeCount( expected_height-1, 0 ) );
  EXPECT_DOUBLE_EQ( 1, js_const.getPixelEscapeCount( 0, expected_width-1 ) );
  EXPECT_DOUBLE_EQ( 1, js_const.getPixelEscapeCount( expected_height-1, expected_width-1 ) );
  EXPECT_DOUBLE_EQ( expected_max_escape_count, js_const.getPixelEscapeCount( expected_height/2, expected_width/2 ) );
  EXPECT_DOUBLE_EQ( -1, js_const.getPixelEscapeCount( -1, expected_width/2 ) );
  EXPECT_DOUBLE_EQ( -1, js_const.getPixelEscapeCount( expected_height, expected_width/2 ) );
  EXPECT_DOUBLE_EQ( -1, js_const.getPixelEscapeCount( expected_height/2, -1 ) );
  EXPECT_DOUBLE_EQ( -1, js_const.getPixelEscapeCount( expected_height/2, expected_width ) );

  /* Tear-down */
  // Done automatically
}
