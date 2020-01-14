#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorTableOperatorTest : public ::testing::Test {
protected:
  ColorTableOperatorTest( )
    : color_table( 13 ),
      expected_default_color{ 0, 0, 0 },
      expected_changed_color{ 23, 29, 31 },
      expected_unchanged_color{ 67, 68, 69 },
      expected_error_color{ -1, -1, -1 },
      expected_num_color( 13 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  ColorTable color_table;
  Color expected_default_color;
  Color expected_changed_color;
  Color expected_unchanged_color;
  Color expected_error_color;
  size_t expected_num_color;
};

TEST_F( ColorTableOperatorTest, fetchesConstantColor ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const ColorTable& color_table_const = color_table;
  const Color& actual_color = color_table_const[ 2 ];

  /* Comparison */
  EXPECT_EQ( expected_default_color, actual_color );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableOperatorTest, fetchesMutableColor ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Color& actual_color = color_table[ 2 ];

  /* Comparison */
  EXPECT_EQ( expected_default_color, actual_color );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableOperatorTest, changesMutableColor ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table[ 2 ] = expected_changed_color;

  /* Comparison */
  EXPECT_EQ( expected_changed_color, color_table[ 2 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableOperatorTest, changesMutableColorDoesNotChangeOtherColors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  size_t i;
  for( i = 0 ; i < expected_num_color ; i ++ ) {
    color_table[ i ] = expected_unchanged_color;
  }
  color_table[ 2 ] = expected_changed_color;

  /* Comparison */
  EXPECT_EQ( expected_changed_color, color_table[ 2 ] ) << " This color at index = 2 should have changed.";
  for( i = 0 ; i < expected_num_color ; i ++ ) {
    if( i != 2 ){
      EXPECT_EQ( expected_unchanged_color, color_table[ i ] ) << " This color not at index = 2 should not have changed.";
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableOperatorTest, fetchesConstantErrorColorIndexTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const ColorTable& color_table_const = color_table;
  const Color& actual_color = color_table_const[ -1 ];

  /* Comparison */
  EXPECT_EQ( expected_error_color, actual_color );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableOperatorTest, fetchesConstantErrorColorIndexTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const ColorTable& color_table_const = color_table;
  const Color& actual_color = color_table_const[ expected_num_color ];

  /* Comparison */
  EXPECT_EQ( expected_error_color, actual_color );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableOperatorTest, fetchesMutableErrorColorIndexTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Color& actual_color = color_table[ -1 ];

  /* Comparison */
  EXPECT_EQ( expected_error_color, actual_color );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableOperatorTest, fetchesMutableErrorColorIndexTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  Color& actual_color = color_table[ expected_num_color ];

  /* Comparison */
  EXPECT_EQ( expected_error_color, actual_color );

  /* Tear-down */
  // Done automatically
}
