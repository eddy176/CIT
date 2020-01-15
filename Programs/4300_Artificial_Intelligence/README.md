Prerequisites
-------------

A recent version of Debian/Ubuntu is assumed.  This is true in the Windows System for Linux.
Install the following packages to be sure the code will build.

        $ sudo apt install libglu1-mesa-dev mesa-common-dev libxext-dev g++ libxxf86vm-dev libxi-dev freeglut3-dev libgl1-mesa-dev
        
You may be able to build on OS X.  If you try, please install the freeglut package with brew.

        $ brew install freeglut


Building with make
------------------

You can build all libraries and programs with.
    
    $ make all
    
To clean out compiled code in preparation for a clean rebuild:
    
    $ make clean
    
To purge installed libraries and programs as well as compiled code:
    
    $ make spotless
    

Running Programs
----------------

Installed programs are kept in `cs4300-code-ai/bin/00bin-o`.  Most
are designed to be run from there.
    
    cd cs4300-code-ai/bin/00bin-o
    ./RubiksCubeSolver < your_input_file.in
    

Adding Your Source
------------------

For the RubiksCube project, you can add your source files to the
directory `cs4300-code-ai-agents/prog/RubiksCube/`.  All of the
`.cpp` files in this directory will be automatically built into
your program.  Be sure that your `main` program is in `main.cpp`.
The `make` command should automatically recognize any changes to
source or header file and rebuild your program as necessary.

Unit Tests
----------

Add unit tests to `cs4300-code-ai-agents/prog/RubiksCube/tests/` as
`.cpp` files.  All such files will be considered part of your
unit tests.  Run unit-tests for the `RubiksCube` project by
these commands.

     $ cd cs4300-code-ai-agents/build/linux/prog/RubiksCube
     $ make unit-test


Debugging
---------

Reconfigure the build system for debugging executables with
`make configure-optimize-off configure-debug-on`.  Any future
`make` operations will be building debugging versions of the
libraries and programs.  The executable programs will be found
in `cs4300-code-ai/bin/00bin-g`.

To return to building optimized code `make configure-optimize-on configure-debug-off`.

Profiling
---------

Reconfigure the build system for profiling executables with
`make configure-optimize-off configure-debug-on configure-profile-on`.  Any future
`make` operations will be building profiling versions of the
libraries and programs.  The executable programs will be found
in `cs4300-code-ai/bin/00bin-gp`.

To return to building optimized code
`make configure-optimize-on configure-debug-off configure-profile-off`.

