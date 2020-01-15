#include "ai_pl.h"
#include "gtest/gtest.h"


/* Symbol class
 * 
 * Methods, dependency ordered:
 *
 * static void ValidateName( const std::string &potential_name );
 *   Loop over length of string >= 1
 *     Use size = 1, 2, 3, N
 *
 * Symbol(const std::string &name_in);
 *   No loop
 *
 * void SetName(const std::string &name_in);
 *   No loop
 *
 * std::string GetName() const;
 *   No loop
 *
 * State       GetValue() const;
 *   No loop
 *
 * void SetValue(State value_in);
 *   No loop
 *
 * FIXME: No tests on Symbol.number data member at this time
 * int         GetNumber() const;
 *   No loop
 *
 * void        SetNumber(int number_in);
 *   No loop
 *
 * Functions:
 *
 * Symbol::State operator++(Symbol::State &lhs, int x);
 *   No loop
 *
 * std::ostream & operator<<(std::ostream &os, const Symbol::State &rhs);
 *   No loop
 *
 * bool operator==(const Symbol &lhs, const Symbol &rhs);
 *   No loop
 *
 * bool operator==(const Symbol &lhs, const std::string &rhs);
 *   No loop
 *
 * bool operator==(const std::string &lhs, const Symbol &rhs);
 *   No loop
 *
 * std::ostream & operator<<(std::ostream &os, const Symbol &s);
 *   No loop
 *
 */

TEST(SymbolPathLoop, validateName) {
  /* Setup */
  std::vector< std::pair< std::string, bool > > pairs = {
    /* name, should_throw_exception */
    // size == 0
    { "", true },
    // size == 1
    { "A", false },
    { "@", true },
    { "Z", false },
    { "[", true },
    { "a", false },
    { "`", true },
    { "z", false },
    { "{", true },
    // size == 2
    { "xA", false },
    { "x@", true },
    { "xZ", false },
    { "x[", true },
    { "xa", false },
    { "x`", true },
    { "xz", false },
    { "x{", true },
    { "x0", false },
    { "x/", true },
    { "x9", false },
    { "x:", true },
    { "x_", false },
    { "x^", true },
    // size == 3
    { "xyA", false },
    { "xy@", true },
    { "xyZ", false },
    { "xy[", true },
    { "xya", false },
    { "xy`", true },
    { "xyz", false },
    { "xy{", true },
    { "xy0", false },
    { "xy/", true },
    { "xy9", false },
    { "xy:", true },
    { "xy_", false },
    { "xy^", true },
    // size == N
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535A", false },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535@", true },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535Z", false },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535[", true },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535a", false },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535`", true },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535z", false },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535{", true },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_314159265350", false },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535/", true },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_314159265359", false },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535:", true },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535_", false },
    { "this_is_a_long_name_that_should_really_exercise_the_loop_YES_31415926535^", true },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string test_name = it->first;
    bool        should_throw = it->second;
    
    if( should_throw ) {
      /* Stimulus */ /* Comparison */
      ASSERT_THROW( ai::PL::Symbol::ValidateName( test_name ), std::domain_error );
    } else {
      /* Stimulus */ /* Comparison */
      ASSERT_NO_THROW( ai::PL::Symbol::ValidateName( test_name ) );
    }
  }
}
