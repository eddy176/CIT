#!/bin/bash

prefix="${1}-"

num_objects="2000"
#use_luminescence="--use-luminescence"
use_luminescence=""
objects_file="${prefix}objects.txt"
world_file="${prefix}world.txt"

./GenerateLearningObjects.py --num-objects "${num_objects}" --output "${objects_file}" "${use_luminescence}" 
./GenesisLearning.py \
    --input "${objects_file}" \
    --output "${world_file}" \
    --num-objects "5" \
    --num-base-objects "2000" \
    --num-base "1" \
    --width "1" --height "1" \
    --num-continents "1" \
    --min-radius "1" --max-radius "1"
