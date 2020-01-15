#!/bin/bash

prefix="${1}-"

num_objects="27"
#use_luminescence="--use-luminescence"
use_luminescence=""
objects_file="${prefix}objects.txt"
world_file="${prefix}world.txt"

./GenerateOnlineObjects.py \
    --num-objects "${num_objects}" \
    --output "${objects_file}" \
    "${use_luminescence}" 

./GenesisLearning.py \
    --input "${objects_file}" \
    --output "${world_file}" \
    --num-objects "5" \
    --num-base-objects "5" \
    --num-base "4" \
    --width "30" --height "30" \
    --num-continents "200" \
    --min-radius "5" --max-radius "12"
