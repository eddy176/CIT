#!/usr/bin/env python3

steps = [ (-1, -1 ),
          (-1,  0 ), 
          (-1,  1 ), 
          ( 0, -1 ),
          ( 0,  0 ), 
          ( 0,  1 ), 
          ( 1, -1 ),
          ( 1,  0 ), 
          ( 1,  1 ), ]


print( """    class ChiefPiecePaths : public PiecePaths {
      // Chief: Diadem with ten jewels; 3 spaces in any direction; straight or diagonal or combination.
    public:
      ChiefPiecePaths( )
        : paths( 
                {""" )

location = [ 0, 0 ]
visited = set( [ tuple( location ) ] )

def to_str( t ):
    s = "{ %2d, %2d }" % ( t[ 0 ], t[ 1 ] )
    return s

for s in steps:
    location[ 0 ] += s[ 0 ]
    location[ 1 ] += s[ 1 ]
    if tuple( location ) not in visited:

        visited.add( tuple( location ) )
        for t in steps:
            location[ 0 ] += t[ 0 ]
            location[ 1 ] += t[ 1 ]
            if tuple( location ) not in visited:
                visited.add( tuple( location ) )
                for u in steps:
                    location[ 0 ] += u[ 0 ]
                    location[ 1 ] += u[ 1 ]
                    if tuple( location ) not in visited:
                        visited.add( tuple( location ) )
                        #print( visited )

                        stu = "                  { " + to_str( s ) + ", " + to_str( t ) + ", " + to_str( u ) + " }, // " + to_str( location )
                        print( stu )
                        
                        visited.remove( tuple( location ) )
                    location[ 0 ] -= u[ 0 ]
                    location[ 1 ] -= u[ 1 ]

                visited.remove( tuple( location ) )
            location[ 0 ] -= t[ 0 ]
            location[ 1 ] -= t[ 1 ]

        visited.remove( tuple( location ) )
    location[ 0 ] -= s[ 0 ]
    location[ 1 ] -= s[ 1 ]
    
print( """                } ) {
        // empty
      }
    };
""" )
            
