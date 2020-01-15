#include "ai_pl.h"
#include "gtest/gtest.h"


/* Symbol class
 * 
 * Data Members:
 *
 * name   : std::string
 * value  : ai::PL::Symbol::State
 * number : int
 *
 * Per Data Member Special Values:
 *
 *   name: 
 *      value1: empty string
 *
 *   value: 
 *      NONE
 *
 *   FIXME: No tests on Symbol.number data member at this time
 *   number:
 *      NONE
 * 
 */

TEST(SymbolInputDomainSpecialValues, nameEmptyStringConstructor) {
  /* Setup */
  // NONE
  
  /* Stimulus */ /* Comparison */
  EXPECT_THROW( ai::PL::Symbol symbol( "" ), std::domain_error );
}

TEST(SymbolInputDomainSpecialValues, nameEmptyStringSet) {
  /* Setup */
  ai::PL::Symbol symbol( "NON_EMPTY" );
  
  /* Stimulus */ /* Comparison */
  EXPECT_THROW( symbol.SetName( "" ), std::domain_error );
}

