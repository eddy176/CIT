#include "ai_jetan.h"
#include "gtest/gtest.h"

class JetanPiecePathsTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }
  
  virtual void TearDown( ) {
  }

};


TEST_F( JetanPiecePathsTest, ConstructsWithEmptyData ) {
  /* Setup */
  ai::Jetan::PiecePaths piece_paths( { } );
  
  /* Stimulus */
  
  /* Comparison */
  EXPECT_EQ( (unsigned int)0, piece_paths.getPaths( ).size( ) ) ;

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanPiecePathsTest, ConstructsWithOnePath ) {
  /* Setup */
  ai::Jetan::PiecePaths piece_paths( { { { { 1, 1 }, { 1, 0 }, { 0, 1 }, } }, } );
  
  /* Stimulus */
  
  /* Comparison */
  EXPECT_EQ( (unsigned int)1, piece_paths.getPaths( ).size( ) ) ;
  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 0 ].dx ) ;
  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 1 ].dx ) ;
  EXPECT_EQ( 0, piece_paths.getPaths( )[ 0 ].steps[ 2 ].dx ) ;
  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 0 ].dy ) ;
  EXPECT_EQ( 0, piece_paths.getPaths( )[ 0 ].steps[ 1 ].dy ) ;
  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 2 ].dy ) ;

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanPiecePathsTest, ConstructsWithTwoPaths ) {
  /* Setup */
  ai::Jetan::PiecePaths piece_paths( {
      { { { 1, 1 }, { 1, 0 }, { 0, 1 }, } }, 
      { { {-1, 1 }, { 0, 0 }, { 1,-1 }, } }, 
    } );
  
  /* Stimulus */
  
  /* Comparison */
  EXPECT_EQ( (unsigned int)2, piece_paths.getPaths( ).size( ) ) ;

  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 0 ].dx ) ;
  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 1 ].dx ) ;
  EXPECT_EQ( 0, piece_paths.getPaths( )[ 0 ].steps[ 2 ].dx ) ;
  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 0 ].dy ) ;
  EXPECT_EQ( 0, piece_paths.getPaths( )[ 0 ].steps[ 1 ].dy ) ;
  EXPECT_EQ( 1, piece_paths.getPaths( )[ 0 ].steps[ 2 ].dy ) ;

  EXPECT_EQ( -1, piece_paths.getPaths( )[ 1 ].steps[ 0 ].dx ) ;
  EXPECT_EQ(  0, piece_paths.getPaths( )[ 1 ].steps[ 1 ].dx ) ;
  EXPECT_EQ(  1, piece_paths.getPaths( )[ 1 ].steps[ 2 ].dx ) ;
  EXPECT_EQ(  1, piece_paths.getPaths( )[ 1 ].steps[ 0 ].dy ) ;
  EXPECT_EQ(  0, piece_paths.getPaths( )[ 1 ].steps[ 1 ].dy ) ;
  EXPECT_EQ( -1, piece_paths.getPaths( )[ 1 ].steps[ 2 ].dy ) ;

  /* Tear-down */
  // Done automatically
}

