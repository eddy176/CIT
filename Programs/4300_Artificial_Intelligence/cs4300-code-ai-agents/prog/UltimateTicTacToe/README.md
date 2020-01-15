Ultimate Tic Tac Toe
====================

Game Overview
-------------

This is a game where two players try to be the first to when three tic tac toe
games in a row, column or diagonal of a larger board.  The board is a 3x3
collection of normal 3x3 tic tac toe boards.

The first move is unrestricted.  The X player places a single X in any position
of any sub-board.  The next moves will be restricted.  The player can only play
in the sub-board that is in the position of the main board identified by the
position in the sub-board played by the previous player.  For example, if X
plays in the upper-right corner of a sub-board, then O must play in the upper-right
sub-board.  The only modification is if the upper-right board has already been completed.
In this case, O can play in any sub-board that has not been completed.  A completed
sub-board is one where either X or O has won, or all cells have been played.

The first player to win three sub-boards in a column, row or diagonal wins.  If
all sub-boards are completed, and no player wins, the game ends in a tie.


Software Overview
-----------------

The software is implemented in the following directories.

- [Headers](cs4300-code-ai-environment/include/Agent/UltimateTicTacToe/)
- [Implementation](cs4300-code-ai-environment/src/Agent/UltimateTicTacToe/)
- [Agent](cs4300-code-ai-agents/prog/UltimateTicTacToe)

The executable programs are:

- [Environment Server](cs4300-code-ai/bin/00bin-o/UltimateTicTacToeServer) 
- [Environment Display](cs4300-code-ai/bin/00bin-o/UltimateTicTacToeDisplay) 
- [Environment Agent](cs4300-code-ai/bin/00bin-o/UltimateTicTacToeAgent) 

To run a game, you must launch the server, a display, and two agents.  Every
process can run on any internet connected system.

Server Options
--------------

- --agents , -a : The number of agents to connect [1]
- --delay , -d : Number of seconds to delay per step [1]
- --displays , -D : Number of display connections to accept [1]
- --port , -p : TCP listening port for all connections [7777]
- --runs , -R : Number of runs [1]
- --seed , -z : Random seed [time]
- --sleep , -S : Number of seconds to sleep between runs [1]
- --steps , -s : Number of steps allowed per agent [1000]
- --tourney , -T : Enable/disable tournament mode [0]
- --trace , -t : Enable/disable agent tracing [1]

A typical invocation of the server may look like this:

    ./UltimateTicTacToeServer -a 2 -D 1 -T 1 -R 1 -d 0 -S 5 -s 100 -t 1

Expect 2 agents and 1 display.  Run a tournament, with 1 game in each direction.
Do not add artificial delays between agent turns, but delay 5 seconds between games.
Only allow a total of 100 moves between the agents.  Display trace information.


Display Options
---------------

- --display , -d : Type of display, (0) redraw on messages or (1) redraw all the time [0]
- --height , -H : Height of display [700]
- --host , -h : Environment hostname or IP address [localhost]
- --port , -p : Environment TCP port [7777]
- --width , -W : Width of display [700]

A typical invocation of the display may look like this:

    ./UltimateTicTacToeDisplay
    
This assumes the server and display are running on the same computer, using
the default port number.


Agent Options
-------------

- --agent , -a : Agent program [?]
- --host , -h : Environment hostname or IP address [localhost]
- --port , -p : Environment TCP port [7777]
- --trace , -t : Enable/disable tracing [1]
- --user1 , -U : User variable 1 [0]
- --user2 , -V : User variable 2 [0]
- --user3 , -W : User variable 3 [0]
- --user4 , -X : User variable 4 [0]
- --user5 , -Y : User variable 5 [0]
- --user6 , -Z : User variable 6 [0]

A typical invocation of the agent may look like this:

    ./UltimateTicTacToeAgent -a r -t 0
    
This assumes the agent program and the server are running on the
same system, using the default port number.  Select the agent 
identified by `r` and disable trace display.  Do not pass
any user defined options.


Building Your Agent
-------------------

To create your own agent, you need to inherit from `ai::Agent::AgentProgram`,
implementing the constructor, destructor, and `Program` method.  See 
`aiSampleRandom.h` and `aiSampleRandom.cpp` as examples.  

After creating your `.h` and `.cpp` files for your agent, edit `AgentPrograms.pm`
to add a clause for your agent.  Choose a name and key that aren't already used.
The key is the letter you will use to select your agent with 
`./UltimateTicTacToeAgent -a ?`.  For header specify the name of
your header file.  For cpp, specify a comma separated list of all cpp files needed
by your agent.  If there is just one fine.  Finally, the constructor field specifies
the C++ syntax for calling your constructor from the global scope.

You only need to change `AgentPrograms.pm` if you add a cpp file or, change your
mind on the other specifications.

To build, run `make` in `cs4300-code-ai-agents/build/linux/prog/UltimateTicTacToe`.
The makefiles there automatically process `AgentPrograms.pm` to figure out which
of your files need to be compiled and linked into `UltimateTicTacToeAgent`.

Assignment 1
------------

Build an agent.  The agent should at least be using the minimax algorithm.  A simple
evaluation function will also be required.  If this agent doesn't beat the random
agent, you're doing something wrong.  Make the depth of search be configurable
from the command line.  Experiment with depth of search.  Set the default value
for depth to be the maximum depth that completes games in less than 60 seconds 
on your computer.

Assignment 2
------------

Build a new agent by cloning the previous one.  This agent should 
at least be using the alpha-beta algorithm.  A simple evaluation function will also
be required.  If this agent doesn't beat the random agent, you're doing something wrong.
This agent should play the same as the minimax agent, but take less time doing it.
If it has an improved evaluation function, it will play better than minimax.
Experiment with depth of search.  Set the default value for depth to be the maximum 
depth that completes games in less than 60 seconds on your computer.

Assignment 3
------------

Create at least three different evaluation functions.  They can have some common elements,
but they must not be identical.  These functions must at least be available in the
alpha-beta agent.  Allow the evaluation function to be selected from the command line.
Play each evaluation function against the other evaluation functions, and keep record
of which wins.  Make the best of the evaluation functions be the default for your 
agent.  If more complex evaluation functions cause the default max depth to take
more than 60 seconds per game, update the default max depth.



References
----------

- [Wikipedia Page](https://en.wikipedia.org/wiki/Ultimate_tic-tac-toe)
