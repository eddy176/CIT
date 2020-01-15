config enable_prompt 0
echo 
config apply_solution 1
config cube_display 1
config depth_limit 6
config generation_limit 1e7
config storage_limit 1e7
config solution_display 1
config heuristic 5


run petrus_moves.cmd
run petrus_cubes.cmd

run petrus1.cmd