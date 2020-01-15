#include "cglPlaceHolder.h"
#include "gtest/gtest.h"

TEST(isOdd, findsOdd) {
  /* Setup */
  int x = 19;
  bool expected_result = true;
  
  /* Stimulus */
  bool result = cgl::isOdd( x );
  
  /* Comparison */
  EXPECT_EQ( expected_result, result );
}

TEST(isOdd, findsNonOdd) {
  /* Setup */
  int x = 212442348;
  bool expected_result = false;
  
  /* Stimulus */
  bool result = cgl::isOdd( x );
  
  /* Comparison */
  EXPECT_EQ( expected_result, result );
}
