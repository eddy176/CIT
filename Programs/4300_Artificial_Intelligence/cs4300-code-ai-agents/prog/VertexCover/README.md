Vertex Cover
------------

Given an undirected graph G = (V,E), where V is a set of vertices and E is a
set of edges, a vertex cover U is a subset of V such that for all (u,v) in E,
at least one of u or v is in U.

The decision problem of vertex cover is defined as follows:

VERTEX-COVER = { < G, k > | G is an undirected graph and k is an integer,
                            and G has a k-node vertex cover }

VERTEX-COVER is NP-complete.  The proof of NP-completeness is traditionally done
via a reduction from 3SAT.

The optimization problem of vertex cover is defined as follows:

Given: G = (V,E) an undirected graph,
Find: k = |U| the minimum size of a vertex cover for G.

This problem is NP-hard.


Additional Resources
--------------------

- https://en.wikipedia.org/wiki/Vertex_cover
- cs4300-code-ai-lib/include/LocalSearch/*.h
- cs4300-code-ai-lib/src/LocalSearch/*.cpp


VertexCoverSolver Script Language
---------------------------------

The following words are understood:

- # comment to end of the line

- initial
  N
  u v w
  u v w
  ...
  -1 -1 -1

  N   := number of vertices
  u,v := vertex numbers; 0 <= u,v < N
  w   := integer weight of edge;  w > 0

- show
  displays the current model as text

- local hillclimb|firstchoice|annealing
  performs a search of the appropriate type
  See cs4300-code-ai-lib/src/LocalSearch/*.cpp for the algorithms

- config restart|start_temperature|min_temperature|temperature_reduction|resolution float_number
  configure search parameters

  restart := the maximum number of restarts to perform

  start_temperature     := simulated annealing starting temperature
  min_temperature       := simulated annealing minimum temperature
  temperature_reduction := simulated annealing temperature reduction ratio
  resolution            := simulated annealing desired random number precision
  
  The temperature update schedule is : temperature -= temperature/temperature_reduction
  The random chance for going to a worse state is :
      double r = ((double)(std::rand() % ((int)resolution))) / resolution;
  Add more 0s to get higher resolution in the random floating point numbers.


Sample Solve Script
-------------------

# auto-generated vertex-cover problem
config max_try_count 100000
config restart 1000
config start_temperature 10.0
config min_temperature 0.01
config temperature_reduction 100.0
config resolution 1000000

initial
5
0 2 1
2 4 1
1 2 1
1 4 1
0 1 1
0 3 1
2 3 1
0 4 1
-1 -1 -1

local hillclimb
local firstchoice
local annealing


Generating Problem Scripts
--------------------------

tools/make_vertex_cover_problem.py can be used to generate problem
instance scripts.  Options include:

-v vertex_count          : size of random graph to generate
-g generation_limit      : maximum number of states to generate
-r restart_count         : maximum number of random restarts to try
-s start_temperature     : simulated annealing start temperature
-t min_temperature       : simulated annealing minimum temperature
-d temperature_reduction : simulated annealing temperature reduction ratio
-o resolution            : simulated annealing random number resolution
-H                       : do hillclimbing
-F                       : do firstchoice
-A                       : do simulated annealing

Tuning the Solver
-----------------

- The objective function is calculated in example::VertexCover::Model::getValue( ).
  You should consider changes or replacements the objective function calculated
  to help guide the local search algorithms to better peaks more quickly.
  All algorithms try to maximize the objective function, so be sure that
  higher values are associated with better states.  Note the default function
  is negated to achieve this result.

- Hill Climbing uses example::VertexCover::LocalProblem::BestNeighbor( ) to find
  the best neighbor of a state.  The default considers neighbors to
  be all states that can be reached by adding one vertex to the cover set or removing
  one state from the cover set. You should consider strategie that will help hill climbing
  find better peaks faster.

- First Choice and Simulated Annealing use example::VertexCover::LocalProblem::RandomNeighbor( )
  to find a neighbor state to consider using.  As with BestNeighbor( ) you should consider
  if there are better neighbor strategies.

- example::VertexCover::LocalProblem::RandomState( ) generates a starting state at the beginning
  of a random restart.

- example::VertexCover::LocalProblem::GoodEnough( ) can be used to stop the random restarts
  if you are happy with the best peak found so far.

