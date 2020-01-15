#!/bin/bash

function solve_one( ) {
    local shuffle_count="$1"
    local file="solve_many_${shuffle_count}_dl.cmd"
    time $g_cmd < $file
}

function run_one( ) {
    local shuffle_count="$1"
    local output=$(mktemp)
    solve_one $shuffle_count >& $output
    
    local time=$( egrep ^real $output | awk '{ print $2; }' )
    local solved=$( egrep '^TRUE$' $output | wc -l )
    local failed=$( egrep '^FALSE$' $output | wc -l )
    local solution_cost=$( egrep '^search tree dl' $output | awk 'BEGIN{total=0;n=0;}{total+=$7;n+=1;}END{if(n>0){a=total/n;}else{a=0} print a;}' )
    local nodes_generated=$( egrep '^search tree dl' $output | awk 'BEGIN{total=0;n=0;}{total+=$5;n+=1;}END{if(n>0){a=total/n;}else{a=0} print a;}' )
    local nodes_stored=$( egrep '^search tree dl' $output | awk 'BEGIN{total=0;n=0;}{total+=$6;n+=1;}END{if(n>0){a=total/n;}else{a=0} print a;}' )

    echo $shuffle_count $time $solved $failed $nodes_generated $nodes_stored $solution_cost
    rm -f $output
}

function find_solver( ) {
    local cmd=./RubiksCubeSolver

    if [ ! -x "$cmd" ]; then
        cmd="../../../../cs4300-code-ai/bin/00bin-o/RubiksCubeSolver"
    fi
    if [ ! -x "$cmd" ]; then
        echo "Can't find RubiksCubeSolver.  Did you build it?"
        exit 1
    fi
    echo $cmd
}

g_cmd=$( find_solver )

for i in $(seq 1 6 ); do
    run_one $i
done
