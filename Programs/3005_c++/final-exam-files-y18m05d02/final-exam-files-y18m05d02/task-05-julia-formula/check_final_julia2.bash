#!/bin/bash

# running this script should generate 8 ppms to compare against the expected images.

make

./main >>/dev/null <<EOF
s 1024
a 0 0 0 0
a 1023 255 255 255
r 1 
r 2 
r 3
r 4
g
5
0
0
255

105
255
0
0

g
106
0
255
0

1022
255
0
255

q

768
768
-0.2
0.0
0.2
0.4
-0.835
-0.2321
1
julia1-color.ppm
EOF

./main >>/dev/null <<EOF
s
100

a
0
255
255
255

a
99
255
0
255

r
1

g
2
0
255
0

49
0
0
0

g
50
0
0
0

98
0
255
0

q

512
512
-2.0
2.0
-2.0
2.0
0.285
0.01
1
julia1-green.ppm
EOF


./main >>/dev/null <<EOF
s 67
a 0 255 255 255
a 1 0   255 255
a 2 255 0   255
a 3 255 255 0
a 4 0   0   255
a 5 0   255 0
a 6 255 0   0
a 7 0   0   0
r 8
g 9 255 0   0  65 0 0 255
a 66 255 255 255
q

512 512
0.0 2.0
-2.0 0.0
0.0 0.8
1
julia1-bottom-right.ppm
EOF


./main >>/dev/null <<EOF
s 194
r 0
r 1
r 2
g 3 255 255 0 43 128 0 127
g 101 255 255 0 166 128 0 127
g 167 128 0 127 193 255 255 0
q

512 512
-0.5 0.0
0.0 0.5
-0.4 0.6
1
julia1-top-left.ppm
EOF


./main >>/dev/null <<EOF
s 1024
g 0 10 10 10   20  10 10 200
g 21 0 0 200   40 200  0   0
g 41 200 0 0   60 50 200 50 
g 61 50 200 50   80 200 50 200
g 81 200 50 200  1022 255 255 255
a 1023 255 255 255
q

768
768
-1.25 1.25
-1.25 1.25
-0.400 -0.00
2
julia2-color.ppm
EOF

./main >>/dev/null <<EOF
s 100
a 0 255 255 255
a 1 0 0 0
g 2 0 255 0  49 0 0 0
g 50 0 0 0  90 0 255 0
g 90 0 255 0 99 255 0 255
q

768 768
-1.25 0.0
-0.75 0.5
0.4 0.0
2
julia2-green.ppm
EOF


./main >>/dev/null <<EOF
s 67
a 0 255 255 255
a 1 0   255 255
a 2 255 0   255
a 3 255 255 0
a 4 0   0   255
a 5 0   255 0
a 6 255 0   0
a 7 0   0   0
a 8 25  255 255
g 9 255 0   0  65 0 0 255
a 66 255 255 255
q

768 768
0.25 0.85
-1.10 -0.5
0.4 0.0
2
julia2-bottom-right.ppm
EOF


./main >>/dev/null <<EOF
s 194
g 0 128 0 127 2 128 128 0
g 3 255 255 0 43 128 0 127
g 44 255 255 0 100 128 0 127
g 101 255 255 0 166 128 0 127
g 167 128 0 127 193 255 255 0
q

768 768
-0.39 -0.19
0.825 1.025
-0.4 0.0
2
julia2-top-left.ppm
EOF

eog *.ppm

#rm -f main *.o *.ppm
make clean
