MY_SCRIPT := solver_commands.cmd

all: grade_test grade

grade_test:
	time ./grade_solutions.py $(MY_SCRIPT) scrambled_cubes_short.txt RubiksCubeSolver RubiksCubeSolver

grade:
	time ./grade_solutions.py $(MY_SCRIPT) scrambled_cubes.txt RubiksCubeSolver RubiksCubeSolver
