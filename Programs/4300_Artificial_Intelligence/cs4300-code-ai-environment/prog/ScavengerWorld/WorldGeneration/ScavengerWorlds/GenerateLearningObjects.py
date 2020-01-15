#!/usr/bin/env python
#
# Creates objects for use in statistical learning
# environment.  Objects are created according
# to a simple Bayes network.
#
#  n_origins: e.g. native, mimick, earth
#  n_colors:  e.g. dayglo-orange, cyan, olivedrab
#  n_shapes:  e.g. rock, bush, triped
#  n_sizes:   e.g. tiny, small, medium
#  n_luminescences e.g. none, 5candela, blinding
#


import sys, getopt, random
from world import Object, Origin, Trait, Color, Shape, Size, Luminescence, ObjectBN


def randomCPTrow(CPT):
    n = len(CPT)
    for i in range(n):
        CPT[i] = 1./n
    for x in range(1000):
        i = random.randrange(n)
        j = random.randrange(n)
        f = random.random() / 10.
        if CPT[j] > f:
            CPT[i] += f
            CPT[j] -= f
    return

def list_from_stats2(num, stats, cls):
    return [ cls(stats[i][0], stats[i][1]) for i in range(num) ]

def empty_CPT_row(num):
    return [ 0.0 for i in range(num) ]


def initialize(num_origins, num_colors, num_shapes, num_sizes, num_luminescences, origin_values):
    origins       = [ Origin("native", 50.),
                      Origin("mimick", 10.),
                      Origin("earth", -50.),
                      Origin("other", 25.),
                      ]
    origins       = origins[:num_origins]
    for i in range(min(len(origin_values), len(origins))):
        origins[i].setValue(origin_values[i])
    origin_CPT    = empty_CPT_row(num_origins)
    randomCPTrow(origin_CPT)    

    colors        = [ Color("dayglo-orange", "d"),
                      Color("cyan", "c"),
                      Color("olivedrab", "V"),
                      Color("fuchsia", "f"),
                      Color("silver", "s"),
                      Color("aqua", "a"),
                      Color("khaki", "k"),
                      Color("indigo", "i"),
                      Color("pink", "p"),
                      ]
    random.shuffle(colors)
    colors        = colors[:num_colors]
    color_CPT     = [ empty_CPT_row(num_colors) for j in range(num_origins) ]
    for row in color_CPT:
        randomCPTrow(row)

    shapes        = [ Shape("rock",   "mineral", "r"),
                      Shape("bush",   "flora",   "B"),
                      Shape("triped", "fauna",   "3"),
                      Shape("pyramid", "mineral", "P" ),
                      Shape("cube", "mineral", "Q"),
                      Shape("tree", "vegetable", "t"),
                      Shape("moped", "animal", "1"),
                      ]
    random.shuffle(shapes)
    shapes        = shapes[:num_shapes]
    shape_CPT     = [ empty_CPT_row(num_shapes) for j in range(num_origins) ]
    for row in shape_CPT:
        randomCPTrow(row)


    sizes         = [ Size("tiny",   0.1,  1.0,  0.1,  2.0, "t"),
                      Size("small",  1.0,  8.0,  1.0, 15.0, "s"),
                      Size("medium", 5.0, 15.0, 10.0, 30.0, "m"),
                      ]
    sizes         = sizes[:num_sizes]
    size_CPT      = [ empty_CPT_row(num_sizes) for j in range(num_origins) ]
    for row in size_CPT:
        randomCPTrow(row)


    luminescences    = [ Luminescence("none",     "n"),
                         Luminescence("5candela", "5"),
                         Luminescence("blinding", "b"),
                         Luminescence("2candela", "2"),
                         Luminescence("10candela", "10"),
                         Luminescence("1candela", "1"),
                         ]
    luminescences    = luminescences[:num_luminescences]
    luminescence_CPT = [ empty_CPT_row(num_luminescences) for j in range(num_origins) ]
    for row in luminescence_CPT:
        randomCPTrow(row)

    return (origins, origin_CPT,
            colors, color_CPT,
            shapes, shape_CPT,
            sizes, size_CPT,
            luminescences, luminescence_CPT)


g_short_opts = 'hn:lo:O:C:H:S:L:V:'
g_long_opts = ["help",
               "num-objects=",
               "use-luminescence",
               "output=",
               "num-origins=",
               "num-colors=",
               "num-shapes=",
               "num-sizes=",
               "num-luminescences=",
               "origin-values=",
               ]

#    num_origins   = 3
#    num_colors    = 3
#    num_shapes    = 3
#    num_sizes     = 3
#    num_luminescences = 3    

def usage():
    print "usage: %s %s %s" % (sys.argv[0], g_short_opts, g_long_opts)

def getArgs():
    my_args = { 'show-help': False,
                'num-objects': 1,
                'use-luminescence': False,
                'output': "-",
                'num-origins'       : 3,
                'num-colors'        : 3,
                'num-shapes'        : 3,
                'num-sizes'         : 3,
                'num-luminescences' : 3,
                'origin-values'     : [],
                }
    
    try:
        opts, args = getopt.getopt(sys.argv[1:], g_short_opts, g_long_opts)
    except getopt.GetoptError, err:
        print str(err)
        usage()
        sys.exit(1)

    for o, a in opts:
        if o in ("-n", "--num-objects"):
            my_args['num-objects'] = int(a)
        elif o in ("-l", "--use-luminescence"):
            my_args['use-luminescence'] = True
        elif o in ("-o", "--output"):
            my_args['output'] = a
        elif o in ("-O", "--num-origins"):
            my_args['num-origins'] = int(a)
        elif o in ("-C", "--num-colors"):
            my_args['num-colors'] = int(a)
        elif o in ("-H", "--num-shapes"):
            my_args['num-shapes'] = int(a)
        elif o in ("-S", "--num-sizes"):
            my_args['num-sizes'] = int(a)
        elif o in ("-L", "--num-luminescences"):
            my_args['num-luminescences'] = int(a)
        elif o in ("-V", "--origin-values"):
            my_args['origin-values'] = [ float(x) for x in a.split(",") ]
        elif o in ("-h", "--help"):
            usage()
            sys.exit(1)
        else:
            assert False, "Unhandled option: '%s:%s'" % (o, a)
            
    return my_args
    
def main():
    args = getArgs()
    (origins, origin_CPT,
     colors, color_CPT,
     shapes, shape_CPT,
     sizes, size_CPT,
     luminescences, luminescence_CPT) = initialize(args['num-origins'],
                                                   args['num-colors'],
                                                   args['num-shapes'],
                                                   args['num-sizes'],
                                                   args['num-luminescences'],
                                                   args['origin-values'])
    bn = ObjectBN(origins, origin_CPT,
                  colors, color_CPT,
                  shapes, shape_CPT,
                  sizes, size_CPT,
                  luminescences, luminescence_CPT)

    if args['output'] != '-':
        fout = open(args['output'], "w")
    else:
        fout = sys.stdout
    for i in range(int(args['num-objects'])):
        obj = bn.createObject( bool(args['use-luminescence']) )
        print >>fout, obj
    if args['output'] != '-':
        fout.close()
    
    return

if __name__ == "__main__":
    main()
