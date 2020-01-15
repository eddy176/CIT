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
    --num-objects "20" \
    --num-base-objects "20" \
    --num-base "4" \
    --width "30" --height "30" \
    --num-continents "30" \
    --min-radius "5" --max-radius "10"
