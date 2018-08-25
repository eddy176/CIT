#!/bin/bash

make

./main > nums0_result.txt < finals_nums0.txt
./main > nums1_result.txt < finals_nums1.txt
./main > nums2_result.txt < finals_nums2.txt

#rm -f main *.o *_result.out
make clean
