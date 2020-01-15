#!/usr/bin/env python3

import make_graph_faster

import sys, os, getopt
g_short_opts = 'hv:g:r:s:t:d:o:HFA'
g_long_opts = ["help", "vertex-count=", "generation-limit=", "restart-count=",
               "start-temperature=", "min-temperature=", "temperature-reduction=",
               "resolution=", 
               "hillclimb", "firstchoice", "annealing" ]

def usage():
    print( "usage: %s %s %s" % (sys.argv[0], g_short_opts, g_long_opts) )

def parse_args():
    arguments = { 'vertex-count':  5,
                  'generation-limit': 1000000,
                  'restart-count': 10,
                  'start-temperature': 10.0,
                  'min-temperature': 0.01,
                  'temperature-reduction': 100.0,
                  'resolution': 1000000,
                  'method': 'hillclimb'
                  }
    try:
        opts, args = getopt.getopt(sys.argv[1:], g_short_opts, g_long_opts)
    except getopt.GetoptError as err:
        print( str(err) )
        usage()
        sys.exit(1)

    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit(1)
            
        elif o in ("-v", "--vertex-count"):
            arguments['vertex-count'] = int( a )
            
        elif o in ("-g", "--generation-limit"):
            arguments['generation-limit'] = int( a )
            
        elif o in ("-r", "--restart-count"):
            arguments['restart-count'] = int( a )
            
        elif o in ("-s", "--start-temperature"):
            arguments['start-temperature'] = float( a )
            
        elif o in ("-t", "--min-temperature"):
            arguments['min-temperature'] = float( a )
            
        elif o in ("-d", "--temperature-reduction"):
            arguments['temperature-reduction'] = float( a )
            
        elif o in ("-o", "--resolution"):
            arguments['resolution'] = float( a )
            
        elif o in ("-H", "--hillclimb"):
            arguments['method'] = 'hillclimb'
            
        elif o in ("-F", "--firstchoice"):
            arguments['method'] = 'firstchoice'
            
        elif o in ("-A", "--annealing"):
            arguments['method'] = 'annealing'
            
        else:
            assert False, "Unhandled option: '%s:%s'" % (o, a)

    return arguments
        



def main( ):
    args = parse_args()

    sys.setrecursionlimit( int( args[ 'vertex-count' ] )*2 )
    G, edge_list = make_graph_faster.create_graph( int( args[ 'vertex-count' ] ), int( 1 ) )
    print( "# auto-generated vertex-cover problem" )
    print( "config generation_limit " + str( args[ 'generation-limit' ] ) )
    print( "config restart " + str( args[ 'restart-count' ] ) )
    print( "config start_temperature " + str( args[ 'start-temperature' ] ) )
    print( "config min_temperature " + str( args[ 'min-temperature' ] ) )
    print( "config temperature_reduction " + str( args[ 'temperature-reduction' ] ) )
    print( "config resolution " + str( args[ 'resolution' ] ) )
    print( "" )
    print( "initial" )
    make_graph_faster.display_graph(sys.stdout, G, edge_list)
    print( "" )
    print( "local " + str( args[ 'method' ] ) )
    print( "" )
    
    return

if __name__ == "__main__":
    main( )
