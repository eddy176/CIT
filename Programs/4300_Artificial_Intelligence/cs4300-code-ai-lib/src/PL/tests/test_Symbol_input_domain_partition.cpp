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
 * Per Data Member Input Domains: 
 *
 *   name: 
 *      domain1: string matching regex [a-zA-Z][a-zA-Z0-9_]*
 *      domain2: string NOT matching regex [a-zA-Z][a-zA-Z0-9_]*
 *
 *   value: 
 *      domain1: ai::PL::Symbol::State::KNOWN_TRUE, 
 *               ai::PL::Symbol::State::KNOWN_FALSE,
 *               ai::PL::Symbol::State::UNKNOWN
 *      domain2: ai::PL::Symbol::State::STATE_MIN, 
 *               ai::PL::Symbol::State::STATE_MAX
 *      domain3: < ai::PL::Symbol::State::STATE_MIN
 *      domain4: > ai::PL::Symbol::State::STATE_MAX
 *
 *   FIXME: No tests on Symbol.number data member at this time
 *   number:
 *      domain1: 1 to INT_MAX
 *      domain2: -INT_MAX to -1
 *      domain3: 0
 */


/****************************************************************
 * Name tests 
 ****************************************************************/

TEST(SymbolInputDomainPartition, nameValidConstructor) {
  /* Setup */
  std::string valid_name = "Hello_World_1";
  ASSERT_NO_THROW( ai::PL::Symbol symbol( valid_name ) );
  
  /* Stimulus */
  ai::PL::Symbol symbol( valid_name );
  
  /* Comparison */
  EXPECT_EQ( valid_name, symbol.GetName( ) );
}

TEST(SymbolInputDomainPartition, nameValidSet) {
  /* Setup */
  std::string init_name = "X";
  std::string valid_name = "Hello_World_1";
  ASSERT_NO_THROW( ai::PL::Symbol symbol( init_name ) );
  ai::PL::Symbol symbol( init_name );
  
  /* Stimulus */
  ASSERT_NO_THROW( symbol.SetName( valid_name ) );
  
  /* Comparison */
  EXPECT_EQ( valid_name, symbol.GetName( ) );
}

TEST(SymbolInputDomainPartition, nameInvalidConstructor) {
  /* Setup */
  std::string invalid_name = "_Hello_World_1";
  
  /* Stimulus */ /* Comparison */
  EXPECT_THROW( ai::PL::Symbol symbol( invalid_name ), std::domain_error );
}

TEST(SymbolInputDomainPartition, nameInvalidSet) {
  /* Setup */
  std::string init_name = "X";
  std::string invalid_name = "_Hello_World_1";
  ASSERT_NO_THROW( ai::PL::Symbol symbol( init_name ) );
  ai::PL::Symbol symbol( init_name );

  /* Stimulus */ /* Comparison */
  EXPECT_THROW( symbol.SetName( invalid_name ), std::domain_error );
}


/****************************************************************
 * Value tests 
 ****************************************************************/

TEST(SymbolInputDomainPartition, valueValidSet) {
  /* Setup */
  std::string init_name = "X";
  ai::PL::Symbol::State valid_value = ai::PL::Symbol::State::KNOWN_FALSE;
  ai::PL::Symbol symbol( init_name );
  
  /* Stimulus */
  ASSERT_NO_THROW( symbol.SetValue( valid_value ) );
  
  /* Comparison */
  EXPECT_EQ( valid_value, symbol.GetValue( ) );
}

TEST(SymbolInputDomainPartition, valueInvalidSet2) {
  /* Setup */
  std::string init_name = "X";
  ai::PL::Symbol::State invalid_value = ai::PL::Symbol::State::STATE_MAX;
  ai::PL::Symbol symbol( init_name );

  /* Stimulus */ /* Comparison */
  EXPECT_THROW( symbol.SetValue( invalid_value ), std::domain_error );
}

TEST(SymbolInputDomainPartition, valueInvalidSet3) {
  /* Setup */
  std::string init_name = "X";
  ai::PL::Symbol::State invalid_value = (ai::PL::Symbol::State) ( ( (int)ai::PL::Symbol::State::STATE_MIN ) - 100 );
  ai::PL::Symbol symbol( init_name );

  /* Stimulus */ /* Comparison */
  EXPECT_THROW( symbol.SetValue( invalid_value ), std::domain_error );
}

TEST(SymbolInputDomainPartition, valueInvalidSet4) {
  /* Setup */
  std::string init_name = "X";
  ai::PL::Symbol::State invalid_value = (ai::PL::Symbol::State) ( ( (int)ai::PL::Symbol::State::STATE_MAX ) + 100 );
  ai::PL::Symbol symbol( init_name );

  /* Stimulus */ /* Comparison */
  EXPECT_THROW( symbol.SetValue( invalid_value ), std::domain_error );
}
