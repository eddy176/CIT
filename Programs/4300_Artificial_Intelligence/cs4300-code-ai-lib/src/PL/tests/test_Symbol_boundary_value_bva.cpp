#include "ai_pl.h"
#include "gtest/gtest.h"
#include <vector>


/* Symbol class
 * 
 * Data Members:
 *
 * name   : std::string
 * value  : ai::PL::Symbol::State
 * number : int
 *
 * Per Data Member Boundary Value Analsys
 *
 *   name: 
 *      boundary1: empty - valid regex 
 *      boundary2: invalid regex - valid regex
 *      boundary3: empty - invalid regex
 *
 *   value: 
 *      boundary1: valid enum - lower bound enum
 *      boundary2: valid enum - lower than enum
 *      boundary3: valid enum - upper bound enum
 *      boundary4: valid enum - higher than enum
 *
 *   FIXME: No tests on Symbol.number data member at this time
 *   number:
 *      boundary1: 0 - positive
 *      boundary2: 0 - negative
 */


/****************************************************************
 * Name tests 
 ****************************************************************/

TEST(SymbolBoundaryValueBVA, nameEmptyValid) {
  std::vector< std::pair< std::string, std::string > > pairs = { { "", "A" },
                                                                 { "", "z" },
                                                                 { "", "X_" },
                                                                 { "", "q12" } };
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    std::string empty_name = it->first;
    std::string valid_name = it->second;
    
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( ai::PL::Symbol symbol( empty_name ), std::domain_error );
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( ai::PL::Symbol symbol( valid_name ) );
    
    /* Setup */
    ai::PL::Symbol symbol( init_name );
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetName( empty_name ), std::domain_error );
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( symbol.SetName( valid_name ) );
  }
}

TEST(SymbolBoundaryValueBVA, nameInvalidValid) {
  std::vector< std::pair< std::string, std::string > > pairs = { { "_A", "A" },
                                                                 { "3z", "z" },
                                                                 { "_X", "X_" },
                                                                 { " q12", "q12" } };
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    std::string invalid_name = it->first;
    std::string valid_name = it->second;
    
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( ai::PL::Symbol symbol( invalid_name ), std::domain_error );
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( ai::PL::Symbol symbol( valid_name ) );
    
    /* Setup */
    ai::PL::Symbol symbol( init_name );
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetName( invalid_name ), std::domain_error );
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( symbol.SetName( valid_name ) );
  }
}

TEST(SymbolBoundaryValueBVA, nameEmptyInvalid) {
  std::vector< std::pair< std::string, std::string > > pairs = { { "", "_A" },
                                                                 { "", "3z" },
                                                                 { "", "_X" },
                                                                 { "", " q12" } };
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    std::string empty_name = it->first;
    std::string invalid_name = it->second;
    
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( ai::PL::Symbol symbol( empty_name ), std::domain_error ) << " empty_name: " << empty_name;
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( ai::PL::Symbol symbol( invalid_name ), std::domain_error ) << " invalid_name: " << invalid_name;
    
    /* Setup */
    ai::PL::Symbol symbol( init_name );
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetName( empty_name ), std::domain_error ) << " empty_name: " << empty_name;
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetName( invalid_name ), std::domain_error ) << " invalid_name: " << invalid_name;
  }
}


/****************************************************************
 * Value tests 
 ****************************************************************/

TEST(SymbolBoundaryValueBVA, valueValidLower) {
  typedef ai::PL::Symbol::State T;
  std::vector< std::pair< T, T > > pairs = { { T::KNOWN_TRUE, T::STATE_MIN },
                                             { T::KNOWN_FALSE, T::STATE_MIN },
                                             { T::UNKNOWN, T::STATE_MIN } };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    T valid_value = it->first;
    T invalid_value = it->second;
    ai::PL::Symbol symbol( init_name );
    
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( symbol.SetValue( valid_value ) );
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetValue( invalid_value ), std::domain_error );
    
    EXPECT_EQ( valid_value, symbol.GetValue( ) );
  }
}

TEST(SymbolBoundaryValueBVA, valueValidLessThanLower) {
  typedef ai::PL::Symbol::State T;
  std::vector< std::pair< T, T > > pairs = { { T::KNOWN_TRUE, (T)((int)T::STATE_MIN - 1 )},
                                             { T::KNOWN_FALSE, (T)((int)T::STATE_MIN - 1)},
                                             { T::UNKNOWN, (T)((int)T::STATE_MIN - 1)} };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    T valid_value = it->first;
    T invalid_value = it->second;
    ai::PL::Symbol symbol( init_name );
    
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( symbol.SetValue( valid_value ) );
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetValue( invalid_value ), std::domain_error );
    
    EXPECT_EQ( valid_value, symbol.GetValue( ) );
  }
}

TEST(SymbolBoundaryValueBVA, valueValidUpper) {
  typedef ai::PL::Symbol::State T;
  std::vector< std::pair< T, T > > pairs = { { T::KNOWN_TRUE, T::STATE_MAX },
                                             { T::KNOWN_FALSE, T::STATE_MAX },
                                             { T::UNKNOWN, T::STATE_MAX } };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    T valid_value = it->first;
    T invalid_value = it->second;
    ai::PL::Symbol symbol( init_name );
    
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( symbol.SetValue( valid_value ) );
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetValue( invalid_value ), std::domain_error );
    
    EXPECT_EQ( valid_value, symbol.GetValue( ) );
  }
}

TEST(SymbolBoundaryValueBVA, valueValidMoreThanUpper) {
  typedef ai::PL::Symbol::State T;
  std::vector< std::pair< T, T > > pairs = { { T::KNOWN_TRUE, (T)((int)T::STATE_MAX + 1 )},
                                             { T::KNOWN_FALSE, (T)((int)T::STATE_MAX + 1)},
                                             { T::UNKNOWN, (T)((int)T::STATE_MAX + 1)} };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    T valid_value = it->first;
    T invalid_value = it->second;
    ai::PL::Symbol symbol( init_name );
    
    /* Stimulus */ /* Comparison */
    ASSERT_NO_THROW( symbol.SetValue( valid_value ) );
    /* Stimulus */ /* Comparison */
    ASSERT_THROW( symbol.SetValue( invalid_value ), std::domain_error );
    
    EXPECT_EQ( valid_value, symbol.GetValue( ) );
  }
}
