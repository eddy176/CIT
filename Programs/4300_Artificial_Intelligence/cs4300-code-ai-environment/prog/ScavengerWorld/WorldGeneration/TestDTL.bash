#!/bin/bash

prefix=$1
full_object_file="${prefix}_objects_full.txt"
pickup_file="${prefix}_objects_pickup.csv"
full_pickup_file="${prefix}_objects_pickup_100.csv"
value_file="${prefix}_objects_value.csv"
full_value_file="${prefix}_objects_value_100.csv"
tmp_file_pickup="${prefix}_objects_pickup_TEMP.csv"
tmp_file_value="${prefix}_objects_value_TEMP.csv"

usage() {
    echo "usage: $0 file_prefix"
}

if [ "$prefix" == "" ]; then
    echo "No file_prefix given."
    usage
    exit 1
fi
if [ -e $full_object_file ]; then
    echo "$full_object_file already exists."
    usage
    exit 1
fi
if [ -e $pickup_file ]; then
    echo "$pickup_file already exists."
    usage
    exit 1
fi
if [ -e $full_pickup_file ]; then
    echo "$full_pickup_file already exists."
    usage
    exit 1
fi
if [ -e $value_file ]; then
    echo "$value_file already exists."
    usage
    exit 1
fi
if [ -e $full_value_file ]; then
    echo "$full_value_file already exists."
    usage
    exit 1
fi

for p in `seq .1 .1 1.`; do
    count=10
    rm -f $tmp_file_pickup
    rm -f $tmp_file_value
    for i in `seq 1 $count`; do
	./GenerateObjects.pl > $full_object_file 2>/dev/null
	tail -n +2 $full_object_file | ./ProcessObjectsPickup.pl -p $p > $pickup_file 2>/dev/null
	tail -n +2 $full_object_file | ./ProcessObjectsPickup.pl -p 1. > $full_pickup_file 2>/dev/null
	./RunProg ./DTL_Test -e $pickup_file -f $full_pickup_file | egrep '^(Total|Correct|Ratio)' | egrep Ratio >> $tmp_file_pickup

	tail -n +2 $full_object_file | ./ProcessObjectsValue.pl -p $p > $value_file 2>/dev/null
	tail -n +2 $full_object_file | ./ProcessObjectsValue.pl -p 1. > $full_value_file 2>/dev/null
	./RunProg ./DTL_Test -e $value_file -f $full_value_file | egrep '^(Total|Correct|Ratio)' | egrep Ratio >> $tmp_file_value
	rm $full_object_file
	rm $pickup_file
	rm $full_pickup_file
	rm $value_file
	rm $full_value_file
    done
    echo -n "Pickup Ratio: $p "
    cat $tmp_file_pickup | awk 'BEGIN{sum=0;n=0;} {sum += $2; n++;} END{printf("%f\n",sum/n);}'
    rm $tmp_file_pickup
    
    echo -n "Value Ratio: $p "
    cat $tmp_file_value | awk 'BEGIN{sum=0;n=0;} {sum += $2; n++;} END{printf("%f\n",sum/n);}'
    rm $tmp_file_value
done
