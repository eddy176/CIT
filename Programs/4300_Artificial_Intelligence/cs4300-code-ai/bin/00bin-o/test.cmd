config enable_prompt 0
config apply_solution 1
config cube_display 3
config depth_limit 6
config generation_limit 1e7
config storage_limit 1e7
config solution_display 1
config heuristic 1
init cube yyyywrbwbrowggbogwrryorwooyoygbbygbrogbboogggbwrryrwww

run definecubes.cmd

init goal wgo2x2x2 wob2x2x2 ygr2x2x2 yrb2x2x2
run search.cmd