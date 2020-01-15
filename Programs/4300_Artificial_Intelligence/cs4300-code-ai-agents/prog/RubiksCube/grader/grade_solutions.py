#!/usr/bin/env python3

import sys, re, os
import tempfile
import subprocess
import time

def process_one_run( input_stream ):
    full_cost = 0
    total_nodes_generated = 0
    max_nodes_stored = 0
    all_moves = ""
    for line in input_stream:
        line = line.strip()
        if not re.match( '^search ', line ):
            continue
        if not re.match( '^search (tree|graph)', line ):
            print( "Warning: You have an output line that begins with search, but does not look like the search report the grader relies on." )
            print( "Warning: " + line )
            continue
        #              solved generated stored cost
        #search graph astar T 5 5 12 rotate  L L D' F B' L L F' B D' L L
        #search graph astar F 1000008 986143
        match = re.match( 'search ([^ ]+) ([^ ]+) ([TF]) ([0-9]+) ([0-9]+)( ([0-9\.]+) rotate(.*)|.*)$', line )
        if not match:
            #raise Exception( "The search line does not match the approved pattern.\n" + line )
            print( "Warning: The search line does not match the approved pattern." )
            print( "Warning: " + line )
            print( "Warning: This search output will not be trusted." )
            total_nodes_generated += 1000000000
            full_cost             += 1.0e9
            all_moves             += "  z R z' "
        else:

            total_nodes_generated += int( match.group(4) )
            nodes_stored = int( match.group( 5 ) )
            if nodes_stored > max_nodes_stored:
                max_nodes_stored = nodes_stored
            if match.group( 3 ) == 'T':
                cost = float(match.group( 7 ))
                moves = match.group( 8 ).strip()
            else:
                cost = 0
                moves = ''

            full_cost += cost
            if len(moves) > 0:
                moves += " "
            all_moves += moves

    return ( total_nodes_generated, max_nodes_stored, full_cost, "rotate " + all_moves )

def process_one_check( input_stream ):
    cube = ""
    for line in input_stream:
        line = line.strip()
        if not re.match( '^Cube: ', line ):
            continue
        words = line.split()
        if len(words) != 2:
            continue
        cube = words[1]
    return cube == 'wwwwwwwwwgggggggggrrrrrrrrrbbbbbbbbboooooooooyyyyyyyyy'

def usage( argv0 ):
    print( "usage: " + argv0 + " command_script cube_file [cube_solver_program] [cube_solver_checker]" )
    print( "command_script is the command file with instructions search for solutions.\n",
           "   Its name and any file it runs must have a path relative to the current\n",
           "   working directory.")
    print( "cube_file is a file with one scrambled cube per line." )
    print( "cube_solver_program is assumed to be ./RubiksCubeSolver, if not specified.\n",
           "   The path specified must be relative to the current working directory.")
    print( "cube_solver_checker is assumed to be the same as cube_solver_program, unless\n"
           "   both are specified.  The path specified must be relative to the current\n"
           "   working directory.")
    sys.exit(1)
    return

def parse_args( argv ):
    if len(argv) < 3:
        usage(argv[0])

    command_script = argv[1]
    cube_file = argv[2]
    if len(argv) > 3:
        cube_solver_program = argv[3]
    else:
        cube_solver_program = "./RubiksCubeSolver"
    if len(argv) > 4:
        cube_solver_checker = argv[4]
    else:
        cube_solver_checker = cube_solver_program
    if cube_solver_program.find( "/" ) == -1:
        cube_solver_program = "./" + cube_solver_program
    if cube_solver_checker.find( "/" ) == -1:
        cube_solver_checker = "./" + cube_solver_checker

    error = 0
    if not os.path.exists( command_script ):
        print( command_script + " does not exist." )
        error += 1
    if not os.path.exists( cube_file ):
        print( cube_file + " does not exist." )
        error += 1
    if not os.path.exists( cube_solver_program ):
        print( cube_solver_program + " does not exist." )
        error += 1
    if not os.path.exists( cube_solver_checker ):
        print( cube_solver_checker + " does not exist." )
        error += 1
    if error > 0:
        usage(argv[0])        

    return command_script, cube_file, cube_solver_program, cube_solver_checker

def build_solve_script( command_script, cube ):

    s = """
config enable_prompt 0
echo
#
#
init cube """ + cube + """
#
#
run """ + command_script + """
#
config cube_display 3
show cube
"""
    return s

def build_check_script( cube, commands ):
    # make sure all moves used are allowed
    words = commands.strip().split()
    if words[0] == "rotate":
        words = words[1:]
    words = list(set(words))
    moves = " ".join(words)
    s = """
config enable_prompt 0
echo
#
#
moves """ + moves + """
#
#
init cube """ + cube + """
#
#
""" + commands + """
#
config cube_display 2
show cube
"""
    return s

g_timeout_count = 0

def run_solve_script( command_script, cube, cube_solver_program ):
    global g_timeout_count
    solve_commands = build_solve_script( command_script, cube )
    args = [ cube_solver_program ]
    if g_timeout_count > 2:
        lines = [ ]
    else:
        try:
            results = subprocess.run(args, input=solve_commands.encode('utf-8'), stdout=subprocess.PIPE, timeout=180)
            lines = results.stdout.decode('utf-8').split('\n')
        except:
            print( "script took too long" )
            lines = [ ]
            g_timeout_count += 1
    return process_one_run( lines )

def run_solution( cube, commands, cube_solver_checker ):
    check_commands = build_check_script( cube, commands )
    
    args = [ cube_solver_checker ]
    results = subprocess.run(args, input=check_commands.encode('utf-8'), stdout=subprocess.PIPE)
    lines = results.stdout.decode('utf-8').split('\n')
    return process_one_check( lines )

def process_one_cube( command_script, cube, cube_solver_program, cube_solver_checker ):
    t0 = time.time( )
    total_nodes_generated, max_nodes_stored, full_cost, commands = run_solve_script( command_script, cube, cube_solver_program )
    t1 = time.time( )
    dt = t1 - t0
    solved = run_solution( cube, commands, cube_solver_checker )
    if not solved:
        failed_fraction = 1.0
        print( "cube not solved by commands: " + cube )
    else:
        failed_fraction = 0.0
        
    score, score1, score2 = calculate_score( full_cost, dt, total_nodes_generated, failed_fraction )
    print( "%.2f" % (score,), "%.2f" % (dt,), total_nodes_generated, max_nodes_stored, full_cost, commands )
    
    return total_nodes_generated, max_nodes_stored, full_cost, solved

def calculate_score( avg_cost, avg_dt, avg_generated, failed_fraction ):
    failed_penalty = 60*10    # 10 minutes
    seconds_per_node = 10**-5 # 1 second per 100,000 node
    seconds_per_move = 1.0    # 1 second per move
    score1 = avg_cost * seconds_per_move + avg_dt                           + failed_fraction * failed_penalty
    score2 = avg_cost * seconds_per_move + avg_generated * seconds_per_node + failed_fraction * failed_penalty
    score = min( score1, score2 )
    return score, score1, score2

def process_all_cubes( command_script, cube_file, cube_solver_program, cube_solver_checker ):
    t0 = time.time()
    generated = 0
    stored = 0
    cost = 0
    solved = 0
    count = 0
    fin = open(cube_file, "r")
    for line in fin:
        cube = line.strip()
        total_nodes_generated, max_nodes_stored, cost0, solved0 = process_one_cube( command_script, cube, cube_solver_program, cube_solver_checker )
        generated += total_nodes_generated
        stored += max_nodes_stored
        if solved0:
            cost += cost0
            solved += 1
        count += 1
    fin.close()
    t1 = time.time()

    dt = t1 - t0
    failed_fraction = 1.0 - (solved/count)
    if solved > 0:
        avg_cost = cost / solved
    else:
        avg_cost = 600 # see failed_penalty in calculate_score()
    score, score1, score2 = calculate_score( avg_cost, dt/count, generated/count, failed_fraction )
    print( "Average generated: " + str(generated/count) )
    print( "Average stored: " + str(stored/count) )
    print( "Average cost: " + str(cost/count) )
    print( "Average time: " + str(dt/count) )
    print( "Solve fraction: " + str(solved/count) )
    print( "Scores: " + str(score) + " " + str(score1) + " " + str(score2) )
    return

def main( argv ):
    command_script, cube_file, cube_solver_program, cube_solver_checker = parse_args( argv )
    process_all_cubes( command_script, cube_file, cube_solver_program, cube_solver_checker )
    return

if __name__ == "__main__":
    main( sys.argv )
