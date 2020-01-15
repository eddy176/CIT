#include "ai_jetan.h"
#include "gtest/gtest.h"

class JetanSetOfBoardLocationsTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
  }
  
  virtual void TearDown( ) {
  }

  /* data members */
  ai::Jetan::SetOfBoardLocations board_locations;
};


TEST_F( JetanSetOfBoardLocationsTest, ConstructsEmpty ) {

  /* Setup */

  
  /* Stimulus */
  
  /* Comparison */
  ai::Jetan::BoardLocation loc;
  int x, y;
  for( y = 0; y < 10; y++ ) {
    for( x = 0; x < 10; x++ ) {
      loc.x = x;
      loc.y = y;
      EXPECT_EQ( 0, board_locations.count( loc ) ) 
        << " x = " << x << " y = " << y << std::endl;;
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanSetOfBoardLocationsTest, StoresLocation ) {

  /* Setup */
  ai::Jetan::BoardLocation loc;
  loc.x = 1;
  loc.y = 9;
  
  /* Stimulus */
  board_locations.insert( loc );
  
  /* Comparison */
  int x, y;
  for( y = 0; y < 10; y++ ) {
    for( x = 0; x < 10; x++ ) {
      loc.x = x;
      loc.y = y;
      if( x == 1 && y == 9 ) {
        EXPECT_EQ( 1, board_locations.count( loc ) ) 
          << " x = " << x << " y = " << y << std::endl;;
      } else {
        EXPECT_EQ( 0, board_locations.count( loc ) ) 
          << " x = " << x << " y = " << y << std::endl;;
      }
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanSetOfBoardLocationsTest, DoesNotStoreLocationNegativeX ) {

  /* Setup */
  ai::Jetan::BoardLocation loc;
  loc.x = -1;
  loc.y =  9;
  
  /* Stimulus */
  board_locations.insert( loc );
  
  /* Comparison */
  int x, y;
  for( y = 0; y < 10; y++ ) {
    for( x = 0; x < 10; x++ ) {
      loc.x = x;
      loc.y = y;
      EXPECT_EQ( 0, board_locations.count( loc ) ) 
        << " x = " << x << " y = " << y << std::endl;;
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanSetOfBoardLocationsTest, DoesNotStoreLocationNegativeY ) {

  /* Setup */
  ai::Jetan::BoardLocation loc;
  loc.x = 1;
  loc.y = -9;
  
  /* Stimulus */
  board_locations.insert( loc );
  
  /* Comparison */
  int x, y;
  for( y = 0; y < 10; y++ ) {
    for( x = 0; x < 10; x++ ) {
      loc.x = x;
      loc.y = y;
      EXPECT_EQ( 0, board_locations.count( loc ) ) 
        << " x = " << x << " y = " << y << std::endl;;
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanSetOfBoardLocationsTest, DoesNotStoreLocationLargeX ) {

  /* Setup */
  ai::Jetan::BoardLocation loc;
  loc.x = 10;
  loc.y = 9;
  
  /* Stimulus */
  board_locations.insert( loc );
  
  /* Comparison */
  int x, y;
  for( y = 0; y < 10; y++ ) {
    for( x = 0; x < 10; x++ ) {
      loc.x = x;
      loc.y = y;
      EXPECT_EQ( 0, board_locations.count( loc ) ) 
        << " x = " << x << " y = " << y << std::endl;;
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanSetOfBoardLocationsTest, DoesNotStoreLocationLargeY ) {

  /* Setup */
  ai::Jetan::BoardLocation loc;
  loc.x = 1;
  loc.y = 10;
  
  /* Stimulus */
  board_locations.insert( loc );
  
  /* Comparison */
  int x, y;
  for( y = 0; y < 10; y++ ) {
    for( x = 0; x < 10; x++ ) {
      loc.x = x;
      loc.y = y;
      EXPECT_EQ( 0, board_locations.count( loc ) ) 
        << " x = " << x << " y = " << y << std::endl;;
    }
  }

  /* Tear-down */
  // Done automatically
}

TEST_F( JetanSetOfBoardLocationsTest, StoresMultipleLocations ) {

  /* Setup */
  ai::Jetan::BoardLocation loc;
  
  /* Stimulus */
  loc.x = 1;
  loc.y = 9;
  board_locations.insert( loc );
  loc.x = 2;
  loc.y = 8;
  board_locations.insert( loc );
  loc.x = 3;
  loc.y = 7;
  board_locations.insert( loc );
  loc.x = 4;
  loc.y = 6;
  board_locations.insert( loc );
  loc.x = 5;
  loc.y = 5;
  board_locations.insert( loc );
  loc.x = 6;
  loc.y = 4;
  board_locations.insert( loc );
  loc.x = 7;
  loc.y = 3;
  board_locations.insert( loc );
  loc.x = 8;
  loc.y = 2;
  board_locations.insert( loc );
  loc.x = 9;
  loc.y = 1;
  board_locations.insert( loc );
  
  /* Comparison */
  int x, y;
  for( y = 0; y < 10; y++ ) {
    for( x = 0; x < 10; x++ ) {
      loc.x = x;
      loc.y = y;
      if( x + y == 10 ) {
        EXPECT_EQ( 1, board_locations.count( loc ) ) 
          << " x = " << x << " y = " << y << std::endl;;
      } else {
        EXPECT_EQ( 0, board_locations.count( loc ) ) 
          << " x = " << x << " y = " << y << std::endl;;
      }
    }
  }

  /* Tear-down */
  // Done automatically
}

