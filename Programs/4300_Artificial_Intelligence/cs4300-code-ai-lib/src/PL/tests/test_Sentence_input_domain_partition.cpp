#include "ai_pl.h"
#include "gtest/gtest.h"


/* Sentence class
 * 
 * Methods:
 *
 * Sentence(bool value_in);                        // create T_TRUE or T_FALSE
 *   domain1: true
 *   domain2: false
 *
 * Sentence(SentenceType type_in);                 // for parsing: (,) only
 *   domain1: [ T_LEFT_PAREN, T_RIGHT_PAREN ]
 *   domain2: { Not above }
 *
 * Sentence(SentenceType type_in, OperatorType op_in); // for parsing: UNARY/NOT, BINARY/AND,OR,IMPLIES,IFF
 *   domain1: type_in = [ T_TRUE, ..., T_RIGHT_PAREN ]
 *   domain2: type_in = { Not above }
 *   domain3: op_in = [ O_NOT, O_IFF ]
 *   domain4: op_in = { Not above }
 *
 * Sentence(Symbol *symbol_in);                    // create T_SYMBOL
 *   domain1: symbol_in = pointer from heap
 *   domain2: symbol_in = null pointer
 *
 * Sentence(OperatorType op_in, Sentence *rhs_in); // create T_UNARY, O_NOT
 *   domain1: op_in = O_NOT
 *   domain2: op_in != O_NOT
 *   domain3: rhs_in = pointer from heap
 *   domain4: rhs_in = null pointer
 *
 * Sentence(Sentence *lhs_in, OperatorType op_in, Sentence *rhs_in); // create T_BINARY
 *   domain1: lhs_in = pointer from heap
 *   domain2: lhs_in = null pointer
 *   domain3: op_in in [ O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain4: op_in not in [ O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain5: rhs_in = pointer from heap
 *   domain6: rhs_in = null pointer
 *
 * Sentence(const Sentence &rhs_in);               // copy constructor
 *   domain1: rhs_in.type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: rhs_in.type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: rhs_in.symbol pointer from heap
 *   domain4: rhs_in.symbol null pointer
 *   domain5: rhs_in.lhs pointer from heap
 *   domain6: rhs_in.lhs null pointer
 *   domain7: rhs_in.op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: rhs_in.op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: rhs_in.rhs pointer from heap
 *   domain10: rhs_in.rhs null pointer
 *
 * Sentence &operator=(const Sentence &rhs_in);
 *   domain1: rhs_in.type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: rhs_in.type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: rhs_in.symbol pointer from heap
 *   domain4: rhs_in.symbol null pointer
 *   domain5: rhs_in.lhs pointer from heap
 *   domain6: rhs_in.lhs null pointer
 *   domain7: rhs_in.op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: rhs_in.op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: rhs_in.rhs pointer from heap
 *   domain10: rhs_in.rhs null pointer
 *   domain11: this->type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain12: this->type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain13: this->symbol pointer from heap
 *   domain14: this->symbol null pointer
 *   domain15: this->lhs pointer from heap
 *   domain16: this->lhs null pointer
 *   domain17: this->op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain18: this->op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain19: this->rhs pointer from heap
 *   domain20: this->rhs null pointer
 *
 * ~Sentence();
 *   domain1: this->type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: this->type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: this->symbol pointer from heap
 *   domain4: this->symbol null pointer
 *   domain5: this->lhs pointer from heap
 *   domain6: this->lhs null pointer
 *   domain7: this->op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: this->op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: this->rhs pointer from heap
 *   domain10: this->rhs null pointer
 *
 * void Delete();
 *   domain1: this->type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: this->type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: this->symbol pointer from heap
 *   domain4: this->symbol null pointer
 *   domain5: this->lhs pointer from heap
 *   domain6: this->lhs null pointer
 *   domain7: this->op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: this->op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: this->rhs pointer from heap
 *   domain10: this->rhs null pointer
 *
 * void SetLHS(Sentence *lhs_in);
 *   domain1: lhs_in pointer from heap
 *   domain2: lhs_in null pointer
 *   domain3: this->lhs pointer from heap
 *   domain4: this->lhs null pointer
 *
 * void SetRHS(Sentence *rhs_in);
 *   domain1: rhs_in pointer from heap
 *   domain2: rhs_in null pointer
 *   domain3: this->rhs pointer from heap
 *   domain4: this->rhs null pointer
 *
 * Symbol::State Evaluate() const;
 *   domain1: this->type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: this->type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: this->symbol pointer from heap
 *   domain4: this->symbol null pointer
 *   domain5: this->lhs pointer from heap
 *   domain6: this->lhs null pointer
 *   domain7: this->op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: this->op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: this->rhs pointer from heap
 *   domain10: this->rhs null pointer
 *
 * SentenceType    GetType() const;
 *   domain1: this->type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: this->type not in [ T_TRUE, T_RIGHT_PAREN ]
 *
 * const Symbol   *GetSymbol() const;
 *   domain1: this->symbol pointer from heap
 *   domain2: this->symbol null pointer
 *
 * OperatorType    GetOperator() const;
 *   domain1: this->op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain2: this->op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *
 * const Sentence *GetLHS() const;
 *   domain1: this->lhs pointer from heap
 *   domain2: this->lhs null pointer
 *
 * const Sentence *GetRHS() const;
 *   domain1: this->rhs pointer from heap
 *   domain2: this->rhs null pointer
 *
 * std::string ToString() const;
 *   domain1: this->type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: this->type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: this->symbol pointer from heap
 *   domain4: this->symbol null pointer
 *   domain5: this->lhs pointer from heap
 *   domain6: this->lhs null pointer
 *   domain7: this->op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: this->op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: this->rhs pointer from heap
 *   domain10: this->rhs null pointer
 *
 * void CNF(); // convert to conjuntive normal form
 *   domain1: this->type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: this->type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: this->symbol pointer from heap
 *   domain4: this->symbol null pointer
 *   domain5: this->lhs pointer from heap
 *   domain6: this->lhs null pointer
 *   domain7: this->op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: this->op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: this->rhs pointer from heap
 *   domain10: this->rhs null pointer
 *
 * static void SplitClauses(Sentence *s_in, std::vector<Sentence *> &clauses);
 *   domain1: s_in pointer from heap
 *   domain2: s_in null pointer
 *   domain3: s_in has 1 clause
 *   domain4: s_in has 2 clauses
 *   domain5: s_in has many clauses
 *
 * void FindPure(std::vector<Symbol *> &asserted, std::vector<Symbol *> &negated);
 *   domain1: this contains no symbols
 *   domain2: this contains symbols, none pure
 *   domain3: this contains symbols, 1+ asserted
 *   domain4: this contains symbols, 1+ negated
 *   domain5: this contains symbols, 1+ asserted, 1+ negated
 *
 * bool IsUnitClause(Symbol *&sym_out);
 *   domain1: this is a unit clause
 *   domain2: this is not a unit clause
 *
 * Functions:
 *
 * std::ostream & operator<<(std::ostream &os, const Sentence &s);
 *   domain1: s.type in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain2: s.type not in [ T_TRUE, T_RIGHT_PAREN ]
 *   domain3: s.symbol pointer from heap
 *   domain4: s.symbol null pointer
 *   domain5: s.lhs pointer from heap
 *   domain6: s.lhs null pointer
 *   domain7: s.op in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain8: s.op not in [ O_NOT, O_AND, O_OR, O_IMPLIES, O_IFF ]
 *   domain9: s.rhs pointer from heap
 *   domain10: s.rhs null pointer
 * 
 */

typedef ai::PL::Sentence T;

typedef struct {
  T::SentenceType  expected_type;
  ai::PL::Symbol  *expected_symbol;
  T::OperatorType  expected_operator;
  T               *expected_lhs;
  T               *expected_rhs;
  bool             expect_exception;
} sentence_test_case;


void CompareSentenceTestCase( const sentence_test_case& tcase, const T& sentence ) {
  
  EXPECT_EQ( tcase.expected_type, sentence.GetType( ) );
  
  if( tcase.expected_symbol == 0 ) {
    EXPECT_EQ( tcase.expected_symbol, sentence.GetSymbol( ) );
  } else {
    EXPECT_EQ( *(tcase.expected_symbol), *(sentence.GetSymbol( )) );
  }
  
  EXPECT_EQ( tcase.expected_operator, sentence.GetOperator( ) );
  
  if( tcase.expected_lhs == 0 ) {
    EXPECT_EQ( tcase.expected_lhs, sentence.GetLHS( ) );
  } else {
    EXPECT_EQ( *(tcase.expected_lhs), *(sentence.GetLHS( )) );
  }

  if( tcase.expected_rhs == 0 ) {
    EXPECT_EQ( tcase.expected_rhs, sentence.GetRHS( ) );
  } else {
    EXPECT_EQ( *(tcase.expected_rhs), *(sentence.GetRHS( )) );
  }
}

TEST(SentenceInputDomainPartition, BoolConstructor) {
  /* Setup */
  std::vector< std::pair< bool, sentence_test_case > > cases = {
    { true,  { T::T_TRUE, 0, T::O_NONE, 0, 0 } },
    { false, { T::T_FALSE, 0, T::O_NONE, 0, 0 } },
  };
  
  for( auto it = cases.begin( ) ; it != cases.end( ) ; it++ ) {
    /* Setup */
    ai::PL::Sentence sentence( it->first );
    
    /* Stimulus */ /* Comparison */
    CompareSentenceTestCase( it->second, sentence );
  }
}

TEST(SentenceInputDomainPartition, TypeConstructor) {
  /* Setup */
  std::vector< std::pair< T::SentenceType, sentence_test_case > > cases = {
    { T::T_FALSE,  { T::T_FALSE, 0, T::O_NONE, 0, 0, true } },
    { T::T_LEFT_PAREN,  { T::T_LEFT_PAREN, 0, T::O_NONE, 0, 0, false } },
    { T::T_RIGHT_PAREN,  { T::T_RIGHT_PAREN, 0, T::O_NONE, 0, 0, false } },
  };
  
  for( auto it = cases.begin( ) ; it != cases.end( ) ; it++ ) {
    if( it->second.expect_exception ) {
      /* Setup */ /* Stimulus */ /* Comparison */
      EXPECT_THROW( ai::PL::Sentence sentence( it->first ), std::domain_error );
    } else {
      /* Setup */
      ASSERT_NO_THROW( ai::PL::Sentence sentence( it->first ) );
      ai::PL::Sentence sentence( it->first );
      
      /* Stimulus */ /* Comparison */
      CompareSentenceTestCase( it->second, sentence );
    }
  }
}
