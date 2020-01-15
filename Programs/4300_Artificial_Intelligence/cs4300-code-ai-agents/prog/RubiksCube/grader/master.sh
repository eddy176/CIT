#!/bin/bash
function solve_one( ){
    # run python program to make a temporary file to be passed into g_cmd
    # it must consist of config.cmd and one of the init lines from initcubes.cmd
    time "$g_cmd" < "$1"
}

function run_one(){
    local output time solved solution_cost nodes_generated nodes_stored
    output=$(mktemp)
    solve_one "$1" >& "$output"
    # cat "$output"
    time=$( grep -E ^real "$output" | awk '{ print $2; }' )
    solved=$( grep -E ' T ' "$output" | wc -l )
    failed=$( grep -EL ' T ' "$output" | wc -l )
    solution_cost=$( grep -E '^search graph astar' "$output" | awk 'BEGIN{total=0;n=0;}{total+=$7;n+=1;}END{if(n>0){a=total/n;}else{a=0} print a;}' )
    nodes_generated=$( grep -E '^search graph astar' "$output" | awk 'BEGIN{total=0;n=0;}{total+=$5;n+=1;}END{if(n>0){a=total/n;}else{a=0} print a;}' )
    nodes_stored=$( grep -E '^search graph astar' "$output" | awk 'BEGIN{total=0;n=0;}{total+=$6;n+=1;}END{if(n>0){a=total/n;}else{a=0} print a;}' )

    echo "$time" "$solved" "$failed" "$nodes_generated" "$nodes_stored" "$solution_cost"

    rm -f "$output"
}

function find_solver(){
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


filename="scrambled_cubes_short.txt"
g_cmd=$( find_solver )
rm -f "out.txt"
outs="out.txt"
while read -r line; do
    input=$(mktemp)
    echo "init cube $line"  >> "$input"
    cat "configstepsearch.cmd" >> "$input"
    run_one "$input" >> "$outs"
    rm -f "$input"
done < "$filename"
