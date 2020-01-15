#include "ai_pl.h"
#include "gtest/gtest.h"


/* Symbol class
 * 
 * Methods, dependency ordered:
 *
 * static void ValidateName( const std::string &potential_name );
 *    Throw
 *    No Throw
 *
 * Symbol(const std::string &name_in);
 *    Throw
 *    No Throw
 *
 * void SetName(const std::string &name_in);
 *    Throw
 *    No Throw
 *
 * std::string GetName() const;
 *    Only one exit
 *
 * State       GetValue() const;
 *    Only one exit
 *
 * void SetValue(State value_in);
 *    Throw
 *    No Throw
 *
 * FIXME: No tests on Symbol.number data member at this time
 * int         GetNumber() const;
 *    Only one exit
 *
 * void        SetNumber(int number_in);
 *    Only one exit
 *
 *
 * Functions:
 *
 * Symbol::State operator++(Symbol::State &lhs, int x);
 *    Throw
 *    No Throw
 *
 * std::ostream & operator<<(std::ostream &os, const Symbol::State &rhs);
 *    Throw
 *    No Throw
 *
 * bool operator==(const Symbol &lhs, const Symbol &rhs);
 *    Only one exit
 *
 * bool operator==(const Symbol &lhs, const std::string &rhs);
 *    Only one exit
 *
 * bool operator==(const std::string &lhs, const Symbol &rhs);
 *    Only one exit
 *
 * std::ostream & operator<<(std::ostream &os, const Symbol &s);
 *    Throw
 *    No Throw
 *
 */

TEST(SymbolPathExit, validateName) {
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

TEST(SymbolPathExit, constructorGetSetName) {
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

TEST(SymbolPathExit, GetSetValue) {
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


TEST(SymbolPathExit, IncrementState) {
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

TEST(SymbolPathExit, StateStreamInsertion) {
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

TEST(SymbolPathExit, CompareSymbolToSymbol) {
  
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

TEST(SymbolPathExit, CompareSymbolToString) {
  
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

TEST(SymbolPathExit, CompareStringToSymbol) {
  
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

TEST(SymbolPathExit, SymbolStreamInsertion) {
  /* Setup */
  typedef ai::PL::Symbol::State T;
  std::vector< std::pair< std::pair< std::string, std::string >, std::pair< T, bool > > > pairs = {
    /* name_in, string_out, state_in, should_throw */
    { { "HELLO_WORLD", "HELLO_WORLD = True[0]" }, { T::KNOWN_TRUE, false } },
    { { "HELLO_WORLD", "HELLO_WORLD = Unknown[0]" }, { T::UNKNOWN, false } },
    /* FIXME: Can not set up state that causes a throw */
  };
  
  for( auto it = pairs.begin( ) ; it != pairs.end( ) ; it++ ) {
    /* Setup */
    std::string test_name_in = it->first.first;
    std::string test_string_out = it->first.second;
    T           test_value_in = it->second.first;
    ai::PL::Symbol symbol( test_name_in );
    symbol.SetValue( test_value_in );
    std::stringstream ss;
    
    /* Stimulus */
    ss << symbol;
    
    /* Comparison */
    EXPECT_EQ( test_string_out, ss.str( ) );
  }
}
