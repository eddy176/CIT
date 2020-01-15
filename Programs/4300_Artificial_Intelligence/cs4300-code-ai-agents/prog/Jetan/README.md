Jetan (Barsoomian Chess)
========================

Game Overview
-------------

Jetan is a two player, chess-like game.  It was created by Edgar Rice
Burroughs for the 5th novel in his John Carter of Mars series, published
in 1922.  The game was described as part of the story and in an appendix.
The full text is available at Project Gutenberg. The appendix
has been reproduced below.  In the series, the Martians refer to their
planet as Barsoom.

It is worth noting that Mr. Burroughs' description is somewhat
ambiguous.  There are several areas where individual interpretations
are possible.  The Wikipedia page's talk tab has an extended discussion
on different viewpoints of interpretation.  The rules described here
are *my* interpretation and are the ones implemented in the provided
software model. You must use them.

Board
-----

The Jetan board is a 10x10 checkered board.  Each player begins with
20 pieces on their side of the board.  That's 2 full rows.  The pieces
are named after the standard military and social customs of Barsoom.

Pieces and Movements
--------------------

The piece types are listed here, with *my* movement interpretation.
Note that non-jumping pieces must have an unblocked path, with the
correct combination of steps, to the destination.  Also note that
pieces may not visit the same square twice on the same move.

Moving a piece into the same square as an opponent's piece, as the
last step of the turn's move, will remove the opponent's piece.  Only
one piece may be on the same square at any given time.

Warrior: 2 feathers; 2 spaces straight in any direction or combination.

    ..x..
    .x.x.
    x.W.x
    .x.x.
    ..x..

Padwar: 2 feathers; 2 spaces diagonal in any direction or combination.

    x.x.x
    .....
    x.P.x
    .....
    x.x.x

Dwar: 3 feathers; 3 spaces straight in any direction or combination.

    ...x...
    ..x.x..
    .x.x.x.
    x.xDx.x
    .x.x.x.
    ..x.x..
    ...x...

Flier: 3 bladed propellor; 3 spaces diagonal in any direction or combination; and may jump intervening pieces.

    x.x.x.x
    .......
    x.x.x.x
    ...F...
    x.x.x.x
    .......
    x.x.x.x

Chief: Diadem with ten jewels; 3 spaces in any direction; straight or diagonal or combination.

    xxxxxxx
    xxxxxxx
    xxxxxxx
    xxxCxxx
    xxxxxxx
    xxxxxxx
    xxxxxxx

Princess: Diadem with one jewel; same as Chief, except may jump intervening pieces.  May not move into an attacked location.  May not attack other pieces.  Once per game, may use "the escape", a 10 space move.  The escape may only be used if the princess is under attack.

    xxxxxxx
    xxxxxxx
    xxxxxxx
    xxxPxxx
    xxxxxxx
    xxxxxxx
    xxxxxxx

Thoat: Mounted warrior 2 feathers; 2 spaces, one straight and one diagonal in any direction.

    .x.x.
    x.x.x
    .xTx.
    x.x.x
    .x.x.

Panthan: 1 feather; 1 space, forward, side, or diagonal, but not backward.

    xxx
    xPx
    ...

The initial board layout is like so:

    WPDFRCFDPW
    TppppppppT
    ..........
    ..........
    ..........
    ..........
    ..........
    ..........
    TppppppppT
    WPDFCRFDPW

End Game
--------

The game may end in several ways.

- Princess captured by any piece.  If the princess is captured, the
  capturing player wins, and the captured player loses.
- Chief captures chief. If the chief is captured by the opposing chief,
  the capturing player wins, and the captured player loses.
- Weakened forces.  If both players have three or fewer non-Panthan
  pieces, and the game has no change in pieces for 10 turns, 
  5 for each player, the game is a tie.  This rule is not implemented
  directly in the model.  Instead, the server will terminate
  a game of the each player has a limited number of moves.  If the
  game has not concluded, it will be considered a tie at that point.

Software Overview
-----------------

The software is implemented in the following directories.

- [Headers](cs4300-code-ai-environment/include/Agent/Jetan/)
- [Implementation](cs4300-code-ai-environment/src/Agent/Jetan/)
- [Agent](cs4300-code-ai-agents/prog/Jetan)

The executable programs are:

- [Environment Server](cs4300-code-ai/bin/00bin-o/JetanServer)
- [Environment Display](cs4300-code-ai/bin/00bin-o/JetanDisplay)
- [Environment Agent](cs4300-code-ai/bin/00bin-o/JetanAgent)

To run a game, you must launch the server, a display, and two agents.
Each process can run on any internet connected system.

Server Options
--------------

- --agents , -a : The number of agents to connect [1]
- --delay , -d : Number of seconds to delay per step [1.0]
- --displays , -D : Number of display connections to accept [1]
- --max-time , -M : Maximum number of seconds each agent is allowed to think [300.0]
- --port , -p : TCP listening port for all connections [7777]
- --runs , -R : Number of runs [1]
- --seed , -z : Random seed [time]
- --sleep , -S : Number of seconds to sleep between runs [1.0]
- --steps , -s : Number of steps per agent [1000]
- --tourney , -T : Enable/disable tournament mode [0]
- --trace , -t : Enable/disable agent tracing [1]

A typical invocation of the server may look like this:

    ./JetanToeServer -a 2 -D 1 -T 1 -R 1 -d 0 -S 5 -s 100 -t 1

Expect 2 agents and 1 display.  Run a tournament, with 1 game in each
direction. Do not add artificial delays between agent turns, but delay
5 seconds between games.  Only allow a total of 100 moves for each of the
agents.  Display trace information.

Display Options
---------------

- --display , -d : Type of display, (0) redraw on messages or (1) redraw all the time [0]
- --height , -H : Height of display [700]
- --host , -h : Environment hostname or IP address [localhost]
- --port , -p : Environment TCP port [7777]
- --width , -W : Width of display [700]

A typical invocation of the display may look like this:

    ./JetanDisplay

This assumes the server and display are running on the same computer,
using the default port number.

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

    ./JetanAgent -a r -t 0

This assumes the agent program and the server are running on the
same system, using the default port number.  Select the agent
identified by `r` and disable trace display.  Do not pass
any user defined options.

Building Your Agent
-------------------

To create your own agent, you need to inherit from
`ai::Agent::AgentProgram`, implementing the constructor, destructor,
and `Program` method.  See `aiSampleRandom.h` and `aiSampleRandom.cpp`
as examples.

After creating your `.h` and `.cpp` files for your agent, edit
`AgentPrograms.pm` to add a clause for your agent.  Choose a name and
key that aren't already used. The key is the letter you will use to
select your agent with `./JetanAgent -a ?`.  For header specify the
name of your header file.  For cpp, specify a comma separated list of
all cpp files needed by your agent.  If there is just one fine.
Finally, the constructor field specifies the C++ syntax for calling your
constructor from the global scope.

You only need to change `AgentPrograms.pm` if you add a cpp file or,
change your mind on the other specifications.

To build, run `make` in `cs4300-code-ai-agents/build/linux/prog/Jetan`.
The makefiles there automatically process `AgentPrograms.pm` to figure
out which of your files need to be compiled and linked into `JetanAgent`.

Assignment 1
------------

Build an agent.  The agent should at least be using the minimax algorithm.
A simple evaluation function will also be required.  If this agent doesn't
beat the random agent, you're doing something wrong.  Make the depth of
search be configurable from the command line.  Experiment with depth of
search.  Set the default value for depth to be the maximum depth that
completes games in less than 600 seconds on a lab computer.

Assignment 2
------------

Build a new agent by cloning the previous one.  This agent should
at least be using the alpha-beta algorithm.  A simple evaluation function
will also be required.  If this agent doesn't beat the random agent,
you're doing something wrong. This agent should play the same as the
minimax agent, but take less time doing it. If it has an improved
evaluation function, it should play better than minimax.  Experiment with
depth of search.  Set the default value for depth to be the maximum 
depth that completes games in less than 600 seconds on a lab computer.

Assignment 3
------------

Create at least three different evaluation functions.  They can have some
common elements, but they must not be identical.  These functions must at
least be available in the alpha-beta agent.  Allow the evaluation function
to be selected from the command line. Play each evaluation function
against the other evaluation functions, and keep record of which wins.
Make the best of the evaluation functions be the default for your agent.
If more complex evaluation functions cause the default max depth to take
more than 600 seconds per game, update the default max depth.

References
----------

- [Chessmen of Mars - Project Gutenberg](https://www.gutenberg.org/ebooks/1153)
- [Chessmen of Mars - Wikipedia](https://en.wikipedia.org/wiki/The_Chessmen_of_Mars)
- [Jetan - Wikipedia](https://en.wikipedia.org/wiki/Jetan)

The appendix from the Book
---------------------------

JETAN, OR MARTIAN CHESS

For those who care for such things, and would like to try the game, I
give the rules of Jetan as they were given me by John Carter. By
writing the names and moves of the various pieces on bits of paper and
pasting them on ordinary checkermen the game may be played quite as
well as with the ornate pieces used upon Mars.

THE BOARD: Square board consisting of one hundred alternate black and
orange squares.

THE PIECES: In order, as they stand upon the board in the first row,
from left to right of each player.

Warrior: 2 feathers; 2 spaces straight in any direction or combination.

Padwar: 2 feathers; 2 spaces diagonal in any direction or combination.

Dwar: 3 feathers; 3 spaces straight in any direction or combination.

Flier: 3 bladed propellor; 3 spaces diagonal in any direction or
combination; and may jump intervening pieces.

Chief: Diadem with ten jewels; 3 spaces in any direction; straight or
diagonal or combination.

Princess: Diadem with one jewel; same as Chief, except may jump
intervening pieces.

Flier: See above.

Dwar: See above.

Padwar: See above.

Warrior: See above.

And in the second row from left to right:

Thoat: Mounted warrior 2 feathers; 2 spaces, one straight and one
diagonal in any direction.

Panthans: (8 of them): 1 feather; 1 space, forward, side, or diagonal,
but not backward.

Thoat: See above.

The game is played with twenty black pieces by one player and twenty
orange by his opponent, and is presumed to have originally represented
a battle between the Black race of the south and the Yellow race of the
north. On Mars the board is usually arranged so that the Black pieces
are played from the south and the Orange from the north.

The game is won when any piece is placed on same square with opponent's
Princess, or a Chief takes a Chief.

The game is drawn when either Chief is taken by a piece other than the
opposing Chief, or when both sides are reduced to three pieces, or
less, of equal value and the game is not won in the ensuing ten moves,
five apiece.

The Princess may not move onto a threatened square, nor may she take an
opposing piece. She is entitled to one ten-space move at any time
during the game. This move is called the escape.

Two pieces may not occupy the same square except in the final move of a
game where the Princess is taken.

When a player, moving properly and in order, places one of his pieces
upon a square occupied by an opponent piece, the opponent piece is
considered to have been killed and is removed from the game.

The moves explained. Straight moves mean due north, south, east, or
west; diagonal moves mean northeast, southeast, southwest, or
northwest. A Dwar might move straight north three spaces, or north one
space and east two spaces, or any similar combination of straight
moves, so long as he did not cross the same square twice in a single
move. This example explains combination moves.

The first move may be decided in any way that is agreeable to both
players; after the first game the winner of the preceding game moves
first if he chooses, or may instruct his opponent to make the first
move.
