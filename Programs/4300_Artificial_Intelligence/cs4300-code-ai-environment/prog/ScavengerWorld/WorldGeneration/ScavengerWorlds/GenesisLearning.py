#!/usr/bin/env python

import sys, getopt
from world import World, Object

g_short_opts = 'hi:o:n:N:b:P:M:I:w:h:c:r:R:'
g_long_opts = ["help",
               "input=",
               "output=",
               "num-objects=",
               "num-base-objects=",
               "num-base=",
               "percent-plain=",
               "percent-mud=",
               "percent-ice=",
               "width=",
               "height=",
               "num-continents=",
               "min-radius=",
               "max-radius=",
               ]

def usage():
    print "usage: %s %s %s" % (sys.argv[0], g_short_opts, g_long_opts)
    
def getArgs():
    my_args = { 'show-help': False,
                'input': None,
                'output': "-",
                'num-objects': 1,
                'num-base-objects': 1,
                'num-base': 1,
                'percent-plain': 0.70,
                'percent-mud': 0.20,
                'percent-ice': 0.00,
                'width': 10,
                'height': 10,
                'num-continents': 5,
                'min-radius': 3,
                'max-radius': 10,
                }
    
    try:
        opts, args = getopt.getopt(sys.argv[1:], g_short_opts, g_long_opts)
    except getopt.GetoptError, err:
        print str(err)
        usage()
        sys.exit(1)
        
    for o, a in opts:
        if o in ("-i", "--input"):
            my_args['input'] = a
        elif o in ("-o", "--output"):
            my_args['output'] = a
        elif o in ("-n", "--num-objects"):
            my_args['num-objects'] = int(a)
        elif o in ("-N", "--num-base-objects"):
            my_args['num-base-objects'] = int(a)
        elif o in ("-b", "--num-base"):
            my_args['num-base'] = int(a)
        elif o in ("-P", "--percent-plain"):
            my_args['percent-plain'] = float(a)
        elif o in ("-M", "--percent-mud"):
            my_args['percent-mud'] = float(a)
        elif o in ("-I", "--percent-ice"):
            my_args['percent-ice'] = float(a)
        elif o in ("-w", "--width"):
            my_args['width'] = int(a)
        elif o in ("-h", "--height"):
            my_args['height'] = int(a)
        elif o in ("-c", "--num-continents"):
            my_args['num-continents'] = int(a)
        elif o in ("-r", "--min-radius"):
            my_args['min-radius'] = int(a)
        elif o in ("-R", "--max-radius"):
            my_args['max-radius'] = int(a)
        elif o in ("-h", "--help"):
            usage()
            sys.exit(1)
        else:
            assert False, "Unhandled option: '%s:%s'" % (o, a)
            
    return my_args


def main():
    args = getArgs()
    if args['input']:
        objs = Object.readFile(args['input'])
    else:
        objs = []
        
    w = World(args['width'], args['height'], objs)
    w.setNumBase(args['num-base'])
    w.setNumObjects(args['num-objects'])
    w.setNumBaseObjects(args['num-base-objects'])
    w.setPercentPlain(args['percent-plain'])
    w.setPercentMud(args['percent-mud'])
    w.setPercentIce(args['percent-ice'])
    w.setRadii(args['min-radius'], args['max-radius'])
    for i in range(args['num-continents']):
        w.addRandomContinent()

    if args['output'] != '-':
        fout = open(args['output'], "w")
    else:
        fout = sys.stdout
    print >>fout, w
    if args['output'] != '-':
        fout.close()
    return

if __name__ == "__main__":
    main()
    
