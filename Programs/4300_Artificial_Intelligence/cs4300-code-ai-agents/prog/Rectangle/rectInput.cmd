# turn of the prompt when running this file as the "main" script
config enable_prompt 0
echo

# 0 to leave the model alone after a search
# 1 to apply the steps of a solution to the model after a search
config apply_solution 1

# 0 for human readable display
# 1 for computer readable display
config solution_display 0

# limit search time to 1*10^6 states created
config generation_limit 1e6
# limit frontier size to 1*10^6 states stored
config storage_limit 1e6

# dimensions of the desired rectangle
config rectangle_width 20
config rectangle_height 3

# uncomment this line to use the multiple of 5 restriction
config flood_fill 1

#
# start with a clean model, no pieces placed
#
# init model empty

#
# display the model
#
show model


#
# place a few pieces manually
# uncomment this line to see how a few well placed pieces can reduce the search time
# place h@9,2:3:1 i@13,0:0:1

#
# attempt to find a solution by searching the state space tree with a depth first frontier
#
search tree dfs

#
# display the model, now
# if a solution was found, the model shown should be solved, because of apply_solution
#
echo ================================================================
show model
echo ================================================================

# if the puzzle is solved, stop
exit_if solved

echo The puzzle was not solved.


