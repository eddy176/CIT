#include "VertexCoverModel.h"
#include "gtest/gtest.h"

TEST( GraphAdjacencyMatrix, storesUniqueValues ) {
  /* Setup */
  int size = 7;
  example::VertexCover::GraphAdjacencyMatrix g( 7 );
  
  /* Stimulus */
  int u, v, w;
  int u0, v0;
  for( u = 0; u < size; u++ ) {
    for( v = 0; v < size; v++ ) {
      if( u <= v ) {
        u0 = u;
        v0 = v;
      } else {
        u0 = v;
        v0 = u;
      }
      w = u0 * size + v0;
      g.addEdge( u, v, w );
    }
  }
  
  /* Comparison */
  for( u = 0; u < size; u++ ) {
    for( v = 0; v < size; v++ ) {
      if( u <= v ) {
        u0 = u;
        v0 = v;
      } else {
        u0 = v;
        v0 = u;
      }
      w = u0 * size + v0;
      EXPECT_EQ( w, g.getEdge( u, v ) )
        << "(u,v): (" << u << "," << v << ")" << std::endl;
    }
  }
}
