#!/bin/bash

# generates 4 sample images with stripes to be compared with the expected images.

make

./main >>/dev/null <<EOF
s 1024
a 0 0 0 0
t 1 1022 100 200 100
q

768 768
-0.2 0.0
0.2 0.4
-0.835 -0.2321
julia-color.ppm
EOF

./main >>/dev/null <<EOF
s 100
t  0 20 255 255 255
t 21 30 255 0 255
t 31 60 100 255 100
t 61 99 0 255 0
q

768 768
-2.0 2.0
-2.0 2.0
0.285 0.01
julia-green.ppm
EOF


./main >>/dev/null <<EOF
s 67
t 0 5 13 167 76
t 6 15 167 76 13
t 16 35 76 13 167
t 36 41 13 167 76
t 42 51 167 76 13
t 52 67 76 13 167
q

768 768
0.0 2.0
-2.0 0.0
0.0 0.8
julia-bottom-right.ppm
EOF


./main >>/dev/null <<EOF
s 194
t 0 193 200 100 50
q

768 768
-0.5 0.0
0.0 0.5
-0.4 0.6
julia-top-left.ppm
EOF

eog *.ppm

#rm -f main *.o *.ppm
make clean
