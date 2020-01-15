#!/bin/bash

year=2015

dir="worlds-${year}/learning-worlds"
if [ ! -d "$dir" ]; then
    mkdir -p "$dir"
fi

filebase1=`date "+y%ym%md%d"`

for p in `seq -w 01 04`; do
    filebase2="-learning-tiny"
    prefix="${dir}/${filebase1}p${p}${filebase2}"
    ./NewLearningWorldOneCell.bash "${prefix}"

    filebase2="-learning-small"
    prefix="${dir}/${filebase1}p${p}${filebase2}"
    ./NewSmallLearningWorld.bash "${prefix}"

    filebase2="-learning-medium"
    prefix="${dir}/${filebase1}p${p}${filebase2}"
    ./NewLearningWorld.bash "${prefix}"

    filebase2="-learning-large"
    prefix="${dir}/${filebase1}p${p}${filebase2}"
    ./NewLearningBigWorld.bash "${prefix}"
done

