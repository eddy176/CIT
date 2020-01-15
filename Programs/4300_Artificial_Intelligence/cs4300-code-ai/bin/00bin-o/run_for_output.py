# this is a Python3 file written to input a statistical analysis cmd file
# and should run the rubiks cube solver-accepting input from the cmd file
# it should then do the math necessary for analyzing the solver's efficiency
import subprocess
import re
import time

def main():
    stats_cmd = "assignment3.cmd"
    new_output = "assignment_3_output.txt"

    fin = open(stats_cmd, 'r')

    # run the rubiks cube solver and start taking inputs
    PIPE = subprocess.PIPE
    # ls_output=subprocess.Popen(["ls", "-a"], stdout=subprocess.PIPE)
    rubiks_solver=subprocess.Popen("./RubiksCubeSolver", bufsize=1, universal_newlines=True, stdin=PIPE,stdout=PIPE)
    

    time_taken = 0.0
    solved = 0
    failed = 0
    solution_cost = 0
    nodes_generated = 0
    nodes_stored = 0
    first = True

    input_string = ""

    for line in fin:
        if len(line) == 0:
            continue
        line = line.strip()

        line += '\n'
        input_string += line
        # if first:
        #     print(line)
        #     first = False
        # Popen.poll()

    # with Popen(["ifconfig"], stdout=PIPE) as proc:
    # log.write(proc.stdout.read())
    err = rubiks_solver.poll()
    if err != None:
        return print("an error has occurred, solver not running:", err)
    # Check if child process has terminated. Set and return returncode attribute. Otherwise, returns None.
    # rubiks_solver.text_mode
    start_time = time.time()
    for stdout_data, stderr_data in rubiks_solver.communicate(input=input_string,timeout=None):
        if stderr_data != None:
            return print("an error has occurred in communication:", stderr_data)
        if stdout_data[0:6] == "search":
            
            stop_time = time.time()
            time_taken += stop_time - start_time
            start_time = stop_time

            print(time_taken)
            j = 0
            # parse the stdout_data to find time, solved, failed, solution_cost, nodes_generated, nodes_stored
            for i in range(len(stdout_data)):
                if not stdout_data[i].isnumeric():
                    print("first if statement in for loop:", stdout_data)
                    continue
                for j in range(i, len(stdout_data)):
                    if not stdout_data[j].isnumeric():
                        nodes_generated += float(stdout_data[i:j])
                        break
                nodes_stored += float(stdout_data[j:])
                print("Time taken:", time_taken, "Nodes generated:", nodes_generated, "Nodes stored:", nodes_stored)
                break

        # else:
        #     stdout_data, stderr_data = rubiks_solver.communicate(input=line,timeout=1)


            # # time
            # i = 0
            # j = 0
            # for i in range(len(stdout_data)):
            #     if stdout_data[i].isnumeric():
            #         continue
            #     this_num += float(stdout_data[0:i])
            #     break
            # for j in range(i+1, len(stdout_data)):
            #     if stdout_data[j].isnumeric():
            #         continue
            #     this_num += float(stdout_data[i+1:j])
            #     break
            # time_taken += this_num
            # # end time

            # solved
    


            # end solved

    
    print("Average time: " + time_taken/100)
    print("Average Nodes generated: " + nodes_generated // 100)
    print("Average Nodes stored: " + nodes_stored // 100)

 

    fin.close()

main()