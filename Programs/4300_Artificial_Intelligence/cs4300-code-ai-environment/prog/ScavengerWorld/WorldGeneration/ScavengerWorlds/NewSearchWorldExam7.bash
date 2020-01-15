#!/bin/bash

prefix="${1}-"

num_objects="0"
use_luminescence=""
objects_file="${prefix}objects.txt"
world_file="${prefix}world.txt"

./GenerateLearningObjects.py --num-objects "${num_objects}" --output "${objects_file}" "${use_luminescence}" 
./GenesisLearning.py \
    --input "${objects_file}" \
    --output "${world_file}" \
    --num-objects "0" \
    --num-base-objects "0" \
    --num-base "1" \
    --width "30" --height "30" \
    --num-continents "100" \
    --min-radius "5" --max-radius "10"
