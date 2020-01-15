CubeSolver Program
------------------

This program is a mini-scripting environment for working 
with the Rubik's Cube model provided here.  It has the ability
to track a cube's configuration and apply rotation moves.

It has the ability to define moves that are composites
of basic moves.  Making it easier and more efficient to 
repeat common collections of moves.

Also for convenience, it can be used to define various
cube configurations, such as desirable intermediate cube
configurations.

Finally, after you add the search code, it will have the
ability to search for goal states given initial starting
cube states.

Use the 'help' command to learn more about the available
commands.



Adding Search Functionality
---------------------------

First, you need `Action`, `State`, and `Problem` classes for
the Cube solving problem.  These classes need to inherit
from the base classes provided by the ai::Search library.

The `Action` class needs to store enough information to 
correctly specify the desired action.  For the rectangle problem
this was which piece to place, where to place it, which rotation,
and which flip to give it.  For the cube problem, we need to
know which faces to rotate and how much.  Conveniently,
`CubeModel.h` defines a class, `Move`, with all of the necessary
information.  Note that you would like to make each `Action`
object as small as possible, due to possibly large search
trees.

The `State` class needs to store enough information to
correctly specify the state of the environment.  For the rectangle
problem this was an instance of the `Model` class.  For the
cube problem, the `Cube` class should contain all required
information.  Note that the `State` class should also create
objects as small as possible.  The memory required by the search
is size_of_tree * ( size_of_Action + size_of_State ).  Both
the `Move` and `Cube` classes of the model were created with this
in mind.

The `Problem` class is where we implement the problem-specific
methods required for the generic search algorithms.  

* `Problem( ai::Search::State *initial_state_in, const std::vector< Cube >& goal_cube_in )` is used to construct a problem instance.  Note that the second
  parameter is used to configure a data member of desired goal states.
* `GoalTest` is used to check if a goal state has been reached.  For the
  cube problem, we will implement this by checking if the cube in the current
  state matches any one of the goal cubes configured for the problem.
  Since goal cubes may contain wild cards, this need to be a solved cube.
* `Actions` is used to generate the list of legal actions given a particular
  state.
* `Result` is used to generate the resulting state for applying an action in
  a given state.
* `StepCost` is used to find the cost of taking an action.
* `void setAllowedMoves( const std::map< std::string, Move >& allowed_moves )` is a method specific to the cube problem.  This allows the solver program to
  configure allowed moves to be considered by the `Actions` method. This
  is best implemented by a data member to store the map, and using a
  loop in `Actions` to loop over all allowed moves.


The `search_aux` function of `CubeSearch.cpp` should be created by first
copying it and all of the support functions from `Rectangle/RectangleSearch.cpp`.
Follow up by making cube-specific changes such as:

* Update #includes and namepace
* Throughout the file, be sure to reference the rubiks cube namespace
  and types instead of the ones from rectangle.
* `search_init` should construct the correct types of objects for the
  initial state and problem.  It should use `setAllowedMoves()` to set 
  the allowed moves from `AppData`'s `move_set`.
* When showing the actions for a solution, use the keyword `rotate` instead
  of `place`.
