#!/bin/bash

prefix="${1}-"
world_file="${prefix}world.txt"

./GenesisLearning.py \
    --output "${world_file}" \
    --num-objects "0" \
    --num-base-objects "0" \
    --num-base "1" \
    --width "10" --height "10" \
    --num-continents "30" \
    --min-radius "3" --max-radius "4"
