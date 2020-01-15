#include "ai_pl.h"
#include "gtest/gtest.h"


/* Symbol class
 * 
 * Methods, dependency ordered:
 *
 * static void ValidateName( const std::string &potential_name );
 *   potential_name.size() == 0
 *   potential_name[ 0 ] >= 'A'
 *   potential_name[ 0 ] < 'A'
 *   potential_name[ 0 ] <= 'Z'
 *   potential_name[ 0 ] > 'Z'
 *   potential_name[ 0 ] >= 'a'
 *   potential_name[ 0 ] < 'a'
 *   potential_name[ 0 ] <= 'z'
 *   potential_name[ 0 ] > 'z'
 *   i > 0
 *   potential_name[ i ] >= 'A'
 *   potential_name[ i ] < 'A'
 *   potential_name[ i ] <= 'Z'
 *   potential_name[ i ] > 'Z'
 *   potential_name[ i ] >= 'a'
 *   potential_name[ i ] < 'a'
 *   potential_name[ i ] <= 'z'
 *   potential_name[ i ] > 'z'
 *   potential_name[ i ] >= '0'
 *   potential_name[ i ] < '0'
 *   potential_name[ i ] <= '9'
 *   potential_name[ i ] > '9'
 *   potential_name[ i ] == '_'
 *   potential_name[ i ] != '_'
 *
 * Symbol(const std::string &name_in);
 *   No conditions
 *
 * void SetName(const std::string &name_in);
 *   No conditions
 *
 * std::string GetName() const;
 *   No conditions
 *
 * State       GetValue() const;
 *   No conditions
 *
 * void SetValue(State value_in);
 *   value_in <= STATE_MIN
 *   value_in > STATE_MIN
 *   value_in >= STATE_MAX
 *   value_in < STATE_MAX
 *
 * FIXME: No tests on Symbol.number data member at this time
 * int         GetNumber() const;
 *   No conditions
 *
 * void        SetNumber(int number_in);
 *   No conditions
 *
 *
 * Functions:
 *
 * Symbol::State operator++(Symbol::State &lhs, int x);
 *    lhs == STATE_MIN
 *    lhs == KNOWN_TRUE
 *    lhs == KNOWN_FALSE
 *    lhs == UNKNOWN
 *    lhs == STATE_MAX
 *    lhs != { ANY_ABOVE }
 *
 * std::ostream & operator<<(std::ostream &os, const Symbol::State &rhs);
 *    lhs == KNOWN_TRUE
 *    lhs == KNOWN_FALSE
 *    lhs == UNKNOWN
 *    lhs != { ANY_ABOVE }
 *
 * bool operator==(const Symbol &lhs, const Symbol &rhs);
 *    lhs.name == rhs.name
 *    lhs.name != rhs.name
 *
 * bool operator==(const Symbol &lhs, const std::string &rhs);
 *    lhs.name == rhs
 *    lhs.name != rhs
 *
 * bool operator==(const std::string &lhs, const Symbol &rhs);
 *    lhs == rhs.name
 *    lhs != rhs.name
 *
 * std::ostream & operator<<(std::ostream &os, const Symbol &s);
 *   No conditions
 *
 */

TEST(SymbolPathCondition, validateName) {
  /* Setup */
  std::vector< std::pair< std::string, bool > > pairs = {
    /* name, should_throw_exception */
    // size == 0
    { "", true },
    // i = 0
    { "A", false },
    { "@", true },
    { "Z", false },
    { "[", true },
    { "a", false },
    { "`", true },
    { "z", false },
    { "{", true },
    // i > 0
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

TEST(SymbolPathCondition, constructorGetSetName) {
  /* Setup */
  std::vector< std::pair< std::string, bool > > pairs = {
    /* name, should_throw_exception */
    // size == 0
    { "", true },
    // i = 0
    { "A", false },
    { "@", true },
    { "Z", false },
    { "[", true },
    { "a", false },
    { "`", true },
    { "z", false },
    { "{", true },
    // i > 0
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
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    std::string test_name = it->first;
    bool        should_throw = it->second;
    
    if( should_throw ) {
      /* Stimulus */ /* Comparison */
      ASSERT_THROW( ai::PL::Symbol symbol( test_name ), std::domain_error );
    } else {
      /* Stimulus */ /* Comparison */
      ASSERT_NO_THROW( ai::PL::Symbol symbol( test_name ) );
    }
    
    /* Setup */
    ai::PL::Symbol symbol( init_name );
    
    if( should_throw ) {
      /* Stimulus */ /* Comparison */
      ASSERT_THROW( symbol.SetName( test_name ), std::domain_error );
    } else {
      /* Stimulus */ /* Comparison */
      ASSERT_NO_THROW( symbol.SetName( test_name ) );
      EXPECT_EQ( test_name, symbol.GetName( ) );
    }
  }
}

TEST(SymbolPathCondition, GetSetValue) {
  typedef ai::PL::Symbol::State T;
  
  /* Setup */
  std::vector< std::pair< T, bool > > pairs = {
    /* value, should_throw_exception */
    { ai::PL::Symbol::State::STATE_MIN , true },
    { (T) ((int)ai::PL::Symbol::State::STATE_MIN+1) , false },
    { ai::PL::Symbol::State::STATE_MAX , true },
    { (T) ((int)ai::PL::Symbol::State::STATE_MAX-1) , false },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string init_name = "X";
    T    test_value = it->first;
    bool should_throw = it->second;
    
    /* Setup */
    ai::PL::Symbol symbol( init_name );
    
    if( should_throw ) {
      /* Stimulus */ /* Comparison */
      ASSERT_THROW( symbol.SetValue( test_value ), std::domain_error );
    } else {
      /* Stimulus */ /* Comparison */
      ASSERT_NO_THROW( symbol.SetValue( test_value ) );
      EXPECT_EQ( test_value, symbol.GetValue( ) );
    }
  }
}


TEST(SymbolPathCondition, IncrementState) {
  typedef ai::PL::Symbol::State T;
  
  /* Setup */
  std::vector< std::pair< std::pair< T, T >, bool > > pairs = {
    /* value_in, value_out, should_throw_exception */
    { { T::STATE_MIN, T::KNOWN_TRUE } , false },
    { { T::KNOWN_TRUE, T::KNOWN_FALSE } , false },
    { { T::KNOWN_FALSE, T::UNKNOWN } , false },
    { { T::UNKNOWN, T::STATE_MAX } , false },
    { { T::STATE_MAX, T::STATE_MAX } , false },
    { { (T)((int)T::STATE_MAX+1), (T)((int)T::STATE_MAX+1) } , true },
    { { (T)((int)T::STATE_MIN-1), (T)((int)T::STATE_MIN-1) } , true },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    T    test_value_in = it->first.first;
    T    test_value_out = it->first.second;
    bool should_throw = it->second;
    
    /* Setup */
    T    test_value_mod = test_value_in;
    
    if( should_throw ) {
      /* Stimulus */ /* Comparison */
      ASSERT_THROW( ai::PL::operator++( test_value_mod, 1 ), std::domain_error );
      EXPECT_EQ( test_value_in, test_value_mod );
    } else {
      /* Stimulus */ /* Comparison */
      ASSERT_NO_THROW( ai::PL::operator++( test_value_mod, 1 ) );
      EXPECT_EQ( test_value_out, test_value_mod );
    }

    /* Setup */
    T s = test_value_in;

    /* Stimulus */ /* Comparison */
    if( should_throw ) {
      /* Stimulus */ /* Comparison */
      ASSERT_THROW( s++, std::domain_error );
      EXPECT_EQ( test_value_in, s );
    } else {
      /* Stimulus */ /* Comparison */
      ASSERT_NO_THROW( s++ );
      EXPECT_EQ( test_value_out, s );
    }
  }
}

TEST(SymbolPathCondition, StateStreamInsertion) {
  typedef ai::PL::Symbol::State T;
  
  /* Setup */
  std::vector< std::pair< std::pair< T, std::string >, bool > > pairs = {
    /* value_in, string_out, should_throw_exception */
    { { (T)((int)T::STATE_MIN-1), "" } , true },
    { { T::STATE_MIN, "" } , true },
    { { T::KNOWN_TRUE, "True" } , false },
    { { T::KNOWN_FALSE, "False" } , false },
    { { T::UNKNOWN, "Unknown" } , false },
    { { T::STATE_MAX, "" } , true },
    { { (T)((int)T::STATE_MAX+1), "" } , true },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    T           test_value_in = it->first.first;
    std::string test_value_out = it->first.second;
    bool        should_throw = it->second;
    
    /* Setup */
    std::stringstream ss;
    T s = test_value_in;
    
    if( should_throw ) {
      /* Stimulus */ /* Comparison */
      ASSERT_THROW( ss << s, std::domain_error ) << " State: " << (int)s;
      EXPECT_EQ( test_value_out, ss.str( ) );
    } else {
      /* Stimulus */ /* Comparison */
      ASSERT_NO_THROW( ss << s );
      EXPECT_EQ( test_value_out, ss.str( ) ) << " State: " << (int)s;
    }
  }
}

TEST(SymbolPathCondition, CompareSymbolToSymbol) {
  
  /* Setup */
  std::vector< std::pair< std::pair< std::string, std::string >, bool > > pairs = {
    /* name1, name2, are_equal */
    { { "HELLO", "WORLD" } , false },
    { { "WORLD", "WORLD" } , true },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string test_value1 = it->first.first;
    std::string test_value2 = it->first.second;
    bool should_equal = it->second;
    
    /* Setup */
    ai::PL::Symbol symbol1( test_value1 );
    ai::PL::Symbol symbol2( test_value2 );
    
    EXPECT_EQ( should_equal, symbol1 == symbol2 );
  }
}

TEST(SymbolPathCondition, CompareSymbolToString) {
  
  /* Setup */
  std::vector< std::pair< std::pair< std::string, std::string >, bool > > pairs = {
    /* name1, name2, are_equal */
    { { "HELLO", "WORLD" } , false },
    { { "WORLD", "WORLD" } , true },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string test_value1 = it->first.first;
    std::string test_value2 = it->first.second;
    bool should_equal = it->second;
    
    /* Setup */
    ai::PL::Symbol symbol1( test_value1 );
    
    EXPECT_EQ( should_equal, symbol1 == test_value2 );
  }
}

TEST(SymbolPathCondition, CompareStringToSymbol) {
  
  /* Setup */
  std::vector< std::pair< std::pair< std::string, std::string >, bool > > pairs = {
    /* name1, name2, are_equal */
    { { "HELLO", "WORLD" } , false },
    { { "WORLD", "WORLD" } , true },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string test_value1 = it->first.first;
    std::string test_value2 = it->first.second;
    bool should_equal = it->second;
    
    /* Setup */
    ai::PL::Symbol symbol2( test_value2 );
    
    EXPECT_EQ( should_equal, test_value1 == symbol2 );
  }
}

TEST(SymbolPathCondition, SymbolStreamInsertion) {
  /* Setup */
  std::vector< std::pair< std::string, std::string > > pairs = {
    /* value_in, value_out */
    { "HELLO_WORLD", "HELLO_WORLD = Unknown[0]" },
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string test_value_in = it->first;
    std::string test_value_out = it->second;
    ai::PL::Symbol symbol( test_value_in );
    std::stringstream ss;
    
    /* Stimulus */
    ss << symbol;
    
    /* Comparison */
    EXPECT_EQ( test_value_out, ss.str( ) );
  }
}
