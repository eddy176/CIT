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
    --num-base-objects "500" \
    --num-base "1" \
    --width "5" --height "5" \
    --num-continents "5" \
    --min-radius "2" --max-radius "5"
