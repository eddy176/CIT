#!/bin/bash

prefix="${1}-"
world_file="${prefix}world.txt"

./GenesisLearning.py \
    --output "${world_file}" \
    --num-objects "0" \
    --num-base-objects "0" \
    --num-base "1" \
    --width "30" --height "30" \
    --num-continents "200" \
    --min-radius "5" --max-radius "12"
