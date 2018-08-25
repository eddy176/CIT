#!/bin/bash

make

./main >>/dev/null <<EOF
i
dark-dull-and-boring.ppm
bright-and-exciting.ppm
EOF

./main >>/dev/null <<EOF
i
dark-dull-berlin.ppm
bright-berlin.ppm
EOF

eog *.ppm

#rm -f main *.o *.ppm
make clean
