#include "ai_jetan.h"
#include "gtest/gtest.h"

class JetanMovePathTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::Jetan::MovePath move_path;
};


TEST_F( JetanMovePathTest, ConstructsEmpty ) {
  /* Setup */
  
  /* Stimulus */
  
  /* Comparison */
  EXPECT_EQ( (unsigned int)0, move_path.steps.size( ) ) ;

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanMovePathTest, AddsSteps ) {
  /* Setup */
  
  /* Stimulus */
  ai::Jetan::BoardOffset step1 = { -1, -2 };
  ai::Jetan::BoardOffset step2 = {  3, -1 };
  ai::Jetan::BoardOffset step3 = {  2,  0 };
  ai::Jetan::BoardOffset step4 = {  0,  1 };
  move_path.steps.push_back( step1 );
  move_path.steps.push_back( step2 );
  move_path.steps.push_back( step3 );
  move_path.steps.push_back( step4 );

  /* Comparison */
  EXPECT_EQ(  (unsigned int)4, move_path.steps.size( ) ) ;
  EXPECT_EQ( -1, move_path.steps[ 0 ].dx ) ;
  EXPECT_EQ(  3, move_path.steps[ 1 ].dx ) ;
  EXPECT_EQ(  2, move_path.steps[ 2 ].dx ) ;
  EXPECT_EQ(  0, move_path.steps[ 3 ].dx ) ;
  EXPECT_EQ( -2, move_path.steps[ 0 ].dy ) ;
  EXPECT_EQ( -1, move_path.steps[ 1 ].dy ) ;
  EXPECT_EQ(  0, move_path.steps[ 2 ].dy ) ;
  EXPECT_EQ(  1, move_path.steps[ 3 ].dy ) ;

  /* Tear-down */
  // Done automatically
}
