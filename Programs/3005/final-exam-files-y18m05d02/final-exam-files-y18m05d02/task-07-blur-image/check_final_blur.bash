#!/bin/bash

make

./main >>/dev/null <<EOF
u
mario-grainy.ppm
mario-blur.ppm
EOF

eog *.ppm

#rm -f main *.o *.ppm
make clean
