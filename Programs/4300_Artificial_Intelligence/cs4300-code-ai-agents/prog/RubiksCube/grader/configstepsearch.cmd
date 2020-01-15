config enable_prompt 0
echo 
config apply_solution 1
config cube_display 3
config depth_limit 6
config generation_limit 1e7
config storage_limit 1e7
config solution_display 1


run definecubes1.cmd
run defineMoves.cmd
init cube ggwowbobbrgwggwbbobororrgwgywgwbyobbrryooyoywygwyyrrry 


run step00.cmd
