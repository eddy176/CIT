#!/bin/bash

prefix="${1}-"

num_objects="2000"
#use_luminescence="--use-luminescence"
use_luminescence=""
objects_file="${prefix}objects.txt"
world_file="${prefix}world.txt"
num_colors="--num-colors 4"
num_shapes="--num-shapes 2"
num_sizes="--num-sizes 3"
origin_values="--origin-values 60,20,-100"

./GenerateLearningObjects.py --num-objects "${num_objects}" --output "${objects_file}" ${use_luminescence} ${num_colors} ${num_shapes} ${num_sizes} ${origin_values}
./GenesisLearning.py \
    --input "${objects_file}" \
    --output "${world_file}" \
    --num-objects "0" \
    --num-base-objects "2000" \
    --num-base "1" \
    --width "5" --height "5" \
    --num-continents "5" \
    --min-radius "2" --max-radius "5"
