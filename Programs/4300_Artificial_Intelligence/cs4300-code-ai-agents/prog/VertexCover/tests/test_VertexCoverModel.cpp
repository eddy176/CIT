#include "VertexCoverModel.h"
#include "gtest/gtest.h"
#include <sstream>

TEST( VertexCoverModel, ReadsGraphMatrix ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  
  /* Stimulus */
  m.readGraph( ss );
  
  /* Comparison */
  int u, v, w;
  for( u = 0; u < size; u++ ) {
    for( v = 0; v < size; v++ ) {
      if( u < v ) {
        w = u + 1;
      } else if ( u == v ) {
        w = 0;
      } else {
        w = v + 1;
      }
      EXPECT_EQ( w, m.getEdge( u, v ) )
        << "(u,v): (" << u << "," << v << ")" << std::endl;
    }
  }
}

TEST( VertexCoverModel, ReadsGraphMatrixStopsOnNegative ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
-1 -1 -1 \
4 4 99 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  
  /* Stimulus */
  m.readGraph( ss );
  
  /* Comparison */
  int u, v, w;
  for( u = 0; u < size; u++ ) {
    for( v = 0; v < size; v++ ) {
      if( u < v ) {
        w = u + 1;
      } else if ( u == v ) {
        w = 0;
      } else {
        w = v + 1;
      }
      EXPECT_EQ( w, m.getEdge( u, v ) )
        << "(u,v): (" << u << "," << v << ")" << std::endl;
    }
  }
}

TEST( VertexCoverModel, ReadsGraphList ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_LIST );
  int size = 5;
  
  /* Stimulus */
  m.readGraph( ss );
  
  /* Comparison */
  int u, v, w;
  for( u = 0; u < size; u++ ) {
    for( v = 0; v < size; v++ ) {
      if( u < v ) {
        w = u + 1;
      } else if ( u == v ) {
        w = 0;
      } else {
        w = v + 1;
      }
      EXPECT_EQ( w, m.getEdge( u, v ) )
        << "(u,v): (" << u << "," << v << ")" << std::endl;
    }
  }
}

TEST( VertexCoverModel, addsVertex ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  m.readGraph( ss );
  
  /* Stimulus */
  int u;
  for( u = 0; u < size; u +=2 ) {
    m.addVertex( u );
  }
  
  /* Comparison */
  for( u = 0; u < size; u++ ) {
    EXPECT_EQ( u % 2 == 0, m.checkVertex( u ) )
      << "(u): (" << u << ")" << std::endl;
  }
}

TEST( VertexCoverModel, removesVertex ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  m.readGraph( ss );
  int u;
  for( u = 0; u < size; u ++ ) {
    m.addVertex( u );
  }
  
  /* Stimulus */
  for( u = 0; u < size; u += 2 ) {
    m.removeVertex( u );
  }
  
  /* Comparison */
  for( u = 0; u < size; u++ ) {
    EXPECT_EQ( u % 2 == 1, m.checkVertex( u ) )
      << "(u): (" << u << ")" << std::endl;
  }
}

TEST( VertexCoverModel, talliesCoverCount ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  m.readGraph( ss );
  int u;
  for( u = 0; u < size; u ++ ) {
    m.addVertex( u );
  }
  
  /* Stimulus */
  for( u = 0; u < size; u += 2 ) {
    m.removeVertex( u );
  }
  
  /* Comparison */
  EXPECT_EQ( 0, m.getCoverCount( 0, 0 ) );
  EXPECT_EQ( 1, m.getCoverCount( 0, 1 ) );
  EXPECT_EQ( 0, m.getCoverCount( 0, 2 ) );
  EXPECT_EQ( 1, m.getCoverCount( 0, 3 ) );
  EXPECT_EQ( 0, m.getCoverCount( 0, 4 ) );
  EXPECT_EQ( 0, m.getCoverCount( 1, 1 ) );
  EXPECT_EQ( 1, m.getCoverCount( 1, 2 ) );
  EXPECT_EQ( 2, m.getCoverCount( 1, 3 ) );
  EXPECT_EQ( 1, m.getCoverCount( 1, 4 ) );
  EXPECT_EQ( 0, m.getCoverCount( 2, 2 ) );
  EXPECT_EQ( 1, m.getCoverCount( 2, 3 ) );
  EXPECT_EQ( 0, m.getCoverCount( 2, 4 ) );
  EXPECT_EQ( 0, m.getCoverCount( 3, 3 ) );
  EXPECT_EQ( 1, m.getCoverCount( 3, 4 ) );
  EXPECT_EQ( 0, m.getCoverCount( 4, 4 ) );

  EXPECT_EQ( 10, m.getTotalEdges( ) );
  EXPECT_EQ( 7, m.getCoveredEdges( ) );
  EXPECT_EQ( 3, m.getUncoveredEdges( ) );
  EXPECT_EQ( 2, m.getCoverSize( ) );
}

TEST( VertexCoverModel, displaysToStream ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  m.readGraph( ss );
  int u;
  for( u = 0; u < size; u ++ ) {
    m.addVertex( u );
  }
  for( u = 0; u < size; u += 2 ) {
    m.removeVertex( u );
  }
  std::string expected_string = "7 of 10 edges covered by 2 vertices.\n\
(0,&1) w: 1 c: 1\n\
*(0,2) w: 1 c: 0\n\
(0,&3) w: 1 c: 1\n\
*(0,4) w: 1 c: 0\n\
(&1,2) w: 2 c: 1\n\
(&1,&3) w: 2 c: 2\n\
(&1,4) w: 2 c: 1\n\
(2,&3) w: 3 c: 1\n\
*(2,4) w: 3 c: 0\n\
(&3,4) w: 4 c: 1\n\
";
  
  /* Stimulus */
  std::stringstream os;
  os << m;
    
  /* Comparison */
  EXPECT_EQ( expected_string, os.str( ) );
}

TEST( VertexCoverModel, copyConstructorDuplicatesAll ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  m.readGraph( ss );
  int u;
  for( u = 0; u < size; u ++ ) {
    m.addVertex( u );
  }
  for( u = 0; u < size; u += 2 ) {
    m.removeVertex( u );
  }
  
  /* Stimulus */
  example::VertexCover::Model n( m );
  
  /* Comparison */
  EXPECT_EQ( m.getVertexCount( ), n.getVertexCount( ) );
  EXPECT_EQ( m.getTotalEdges( ), n.getTotalEdges( ) );
  EXPECT_EQ( m.getCoveredEdges( ), n.getCoveredEdges( ) );
  EXPECT_EQ( m.getUncoveredEdges( ), n.getUncoveredEdges( ) );
  EXPECT_EQ( m.getCoverSize( ), n.getCoverSize( ) );

  int v;
  for( u = 0; u < size; u++ ) {
    EXPECT_EQ( m.checkVertex( u ), n.checkVertex( u ) )
      << " u: " << u << std::endl;
    
    for( v = 0; v < size; v++ ) {
      EXPECT_EQ( m.getEdge( u, v ), n.getEdge( u, v ) ) 
        << "(u,v): (" << u << "," << v << ")" << std::endl;
      EXPECT_EQ( m.getCoverCount( u, v ), n.getCoverCount( u, v ) ) 
        << "(u,v): (" << u << "," << v << ")" << std::endl;
    }
  }
}

TEST( VertexCoverModel, displaysToStreamAfterCopy ) {
  /* Setup */
  std::stringstream ss("5 \
0 1 1 \
0 2 1 \
3 0 1 \
0 4 1 \
1 2 2 \
1 3 2 \
4 1 2 \
3 2 3 \
2 4 3 \
3 4 4 \
");
  example::VertexCover::Model m( example::VertexCover::Model::GT_MATRIX );
  int size = 5;
  m.readGraph( ss );
  int u;
  for( u = 0; u < size; u ++ ) {
    m.addVertex( u );
  }
  for( u = 0; u < size; u += 2 ) {
    m.removeVertex( u );
  }
  std::string expected_string = "7 of 10 edges covered by 2 vertices.\n\
(0,&1) w: 1 c: 1\n\
*(0,2) w: 1 c: 0\n\
(0,&3) w: 1 c: 1\n\
*(0,4) w: 1 c: 0\n\
(&1,2) w: 2 c: 1\n\
(&1,&3) w: 2 c: 2\n\
(&1,4) w: 2 c: 1\n\
(2,&3) w: 3 c: 1\n\
*(2,4) w: 3 c: 0\n\
(&3,4) w: 4 c: 1\n\
";
  
  example::VertexCover::Model n( m );
  
  /* Stimulus */
  std::stringstream os;
  os << n;
    
  /* Comparison */
  EXPECT_EQ( expected_string, os.str( ) );
}
