#include "JuliaSet.h"
#include "JuliaSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetCoordinatesTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 400;
    default_height = 400;
    default_min_x = -2.0;
    default_max_x =  2.0;
    default_min_y = -2.0;
    default_max_y =  2.0;
    default_max_escape_count = 255;

    expected_width = 300;
    expected_height = 250;
    expected_min_x = -1.0;
    expected_max_x =  1.5;
    expected_min_y = -0.2;
    expected_max_y =  1.2;
    expected_max_escape_count = 123;
    js.setPixelSize( expected_width, expected_height );
    js.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
    js.setMaxEscapeCount( expected_max_escape_count );

    expected_delta_x = 2.5 / 299;
    expected_delta_y = 1.4 / 249;
    row = 135;
    column = 5;
    expected_x = -0.95819397993311036790;
    expected_y = 0.44096385542168674830;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  JuliaSet js;
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  int default_max_escape_count;

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  int expected_max_escape_count;

  double expected_delta_x, expected_delta_y;
  int row, column;
  double expected_x, expected_y;
};



TEST_F( JuliaSetCoordinatesTest, calculatesDeltaX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.calculateDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesDeltaXSameSignPositive ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x =  0.5;
  expected_max_x =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.7 / 299;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.calculateDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesDeltaXSameSignNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x = -1.5;
  expected_max_x = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.9 / 299;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.calculateDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesDeltaY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.calculateDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesDeltaYSameSignPositive ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y =  0.2;
  expected_max_y =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 1.0 / 249;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.calculateDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesDeltaYSameSignNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y = -1.2;
  expected_max_y = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 0.6 / 249;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.calculateDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesPlaneX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesPlaneX2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x =  0.5;
  expected_max_x =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.7 / 299;
  column = 13;
  expected_x = column * expected_delta_x + expected_min_x;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesPlaneX3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x = -1.5;
  expected_max_x = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.9 / 299;
  column = 217;
  expected_x = column * expected_delta_x + expected_min_x;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, rejectsTooLowColumn ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneXFromPixelColumn( -1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, rejectsTooHighColumn ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneXFromPixelColumn( expected_width ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesPlaneY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesPlaneY2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y =  0.2;
  expected_max_y =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 1.0 / 249;
  row = 111;
  expected_y = expected_max_y - row * expected_delta_y;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesPlaneY3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y = -1.2;
  expected_max_y = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 0.6 / 249;
  row = 83;
  expected_y = expected_max_y - row * expected_delta_y;
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, rejectsTooLowRow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneYFromPixelRow( -1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, rejectsTooHighRow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneYFromPixelRow( expected_height ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, calculatesPixelToPlane ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x, y;
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( row, column, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, x );
  EXPECT_DOUBLE_EQ( expected_y, y );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, rejectsColumnOrRowTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x, y;
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( -1, column, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Stimulus */
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( row, -1, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetCoordinatesTest, rejectsColumnOrRowTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  double x, y;
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( expected_height, column, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Stimulus */
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( row, expected_width, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Tear-down */
  // Done automatically
}
