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


for dy in range( -10, 11 ):
    for dx in range( -10, 11 ):
        s = "                  { { { %3d, %3d }, } }," % ( dx, dy )
        print( s )
