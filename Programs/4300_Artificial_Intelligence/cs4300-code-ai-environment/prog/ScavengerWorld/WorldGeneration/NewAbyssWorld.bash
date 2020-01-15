#!/bin/bash

if [ "x" == "x" ]; then
    WORLD_SIZE=8
    NUM_CONTINENTS=30
    MAX_OBJECTS=5
    OBJECT_POWER=3
    MIN_SIZE=3
    MAX_SIZE=10
    NUM_BASE=1
    FRACTION_COLOR_BAD=.5
    USE_LUM="1"
    PLAIN_PERCENT=.7
    MUD_PERCENT=.3
    ICE_PERCENT=.0
fi


prefix=$1
full_object_file="${prefix}_objects_full.txt"
pickup_file="${prefix}_objects_pickup.csv"
value_file="${prefix}_objects_value.csv"
world_file="${prefix}_world.txt"

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
if [ -e $value_file ]; then
    echo "$value_file already exists."
    usage
    exit 1
fi
if [ -e $world_file ]; then
    echo "$world_file already exists."
    usage
    exit 1
fi

./GenerateObjects.pl -L $USE_LUM -C $FRACTION_COLOR_BAD > $full_object_file
cat $full_object_file | ./ProcessObjectsPickup.pl -p 0.30 > $pickup_file
cat $full_object_file | ./ProcessObjectsValue.pl  -p 1.00 > $value_file
./Genesis.pl -w $WORLD_SIZE -h $WORLD_SIZE -n $NUM_CONTINENTS -o $MAX_OBJECTS -P $OBJECT_POWER -m $MIN_SIZE -M $MAX_SIZE -f $full_object_file -F $world_file -B $NUM_BASE -p $PLAIN_PERCENT -u $MUD_PERCENT -i $ICE_PERCENT

