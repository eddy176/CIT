#!/usr/bin/env python
#
# Creates objects for use in the pre-specified
# desirable object environment.  Objects are created 
# randomly, and the specified combinations are given
# positive values.  All others are given negative
# values.
#
#

import sys, getopt, random
from world import Object, Trait, Color, Shape, Size, Luminescence, ObjectEnumeration

def initialize(num_colors, num_shapes, num_sizes, num_luminescences, combo_values, seed):
    random.seed(seed)
    
    colors = [ Color("red", "r"),
               Color("green", "g"),
               Color("blue", "b"),
               Color("magenta", "m"),
               Color("yellow", "y"),
               Color("cyan", "c"),
               Color("black", "B"),
               Color("white", "w"),
               Color("gold", "G"),
               Color("silver", "s"),
               Color("brown", "W"),
               Color("orange", "o"),
               Color("rust", "R"),
               Color("dayglo-orange", "d"),
               Color("aqua", "a"),
               Color("bisque", "q"),
               Color("crimson", "C"),
               Color("chocolate", "h"),
               Color("khaki", "k"),
               Color("fuchsia", "f"),
               Color("indigo", "i"),
               Color("pink", "p"),
               Color("orchid", "O"),
               Color("tomato", "t"),
               Color("wheat", "H"),
               Color("forestgreen", "F"),
               Color("lawngreen", "l"),
               Color("olivedrab", "V"),
               Color("snow", "n"),
               Color("violet", "v"),
               Color("slategrey", "Y"),
               Color("steelblue", "e"),
               Color("plum", "M"),
               Color("peachpuff", "P"),
               Color("limegreen", "L"),
               Color("dsu-red-white-blue", "D"),
           ]
    random.shuffle(colors)
    colors     = colors[:num_colors]
    num_colors = len(colors)
    
    shapes = [ Shape("rock", "mineral", "r"),
               Shape("sphere", "mineral", "S"),
               Shape("cylinder", "mineral", "C"),
               Shape("cone", "mineral", "c"),
               Shape("cube", "mineral", "Q"),
               Shape("pyramid", "mineral", "P"),
               Shape("box", "mineral", "q"),

               Shape("grass", "vegetable", "g"),
               Shape("pod", "vegetable", "p"),
               Shape("bush", "vegetable", "B"),
               Shape("tree", "vegetable", "t"),
               Shape("stalk", "vegetable", "s"),
               Shape("vine", "vegetable", "v"),

               Shape("mandelbrot", "animal", "m"),
               Shape("blob", "animal", "b"),
               Shape("quadruped", "animal", "4"),
               Shape("triped", "animal", "3"),
               Shape("biped", "animal", "2"),
               Shape("moped", "animal", "1"),
               Shape("noped", "animal", "0"),
           ]
    random.shuffle(shapes)
    shapes     = shapes[:num_shapes]
    num_shapes = len(shapes)
    
    sizes = [ Size("tiny",   0.1,  1.0,  0.1,  2.0, "t"),
              Size("small",  1.0,  8.0,  1.0, 15.0, "s"),
              Size("medium", 5.0, 15.0, 10.0, 30.0, "m"),
              Size("large", 10.0, 24.9, 30.0, 99.9, "l"),
              Size("huge",  20.0, 80.0,100.1,150.0, "h"),
          ]
    #random.shuffle(sizes)
    sizes     = sizes[:num_sizes]
    num_sizes = len(sizes)


    luminescences = [ Luminescence("none",     "n"),
                      Luminescence("5candela", "5"),
                      Luminescence("blinding", "b"),
                      Luminescence("2candela", "2"),
                      Luminescence("10candela", "10"),
                      Luminescence("1candela", "1"),
                  ]
    #random.shuffle(luminescences)
    luminescences     = luminescences[:num_luminescences]
    num_luminescences = len(luminescences)

    num_combo_values = len(combo_values)
    
    return (colors, num_colors,
            shapes, num_shapes,
            sizes, num_sizes,
            luminescences, num_luminescences,
            combo_values, num_combo_values)

g_short_opts = 'hn:lo:C:H:S:L:V:Z:'
g_long_opts = ["help",
               "num-objects=",
               "use-luminescence",
               "output=",
               "num-colors=",
               "num-shapes=",
               "num-sizes=",
               "num-luminescences=",
               "combo-values=",
               "seed="
               ]

def usage():
    print "usage: %s %s %s" % (sys.argv[0], g_short_opts, g_long_opts)

def getArgs():
    my_args = { 'show-help': False,
                'num-objects': 1,
                'use-luminescence': False,
                'output': "-",
                'num-colors'        : 3,
                'num-shapes'        : 3,
                'num-sizes'         : 3,
                'num-luminescences' : 3,
                'combo-values'      : [ (0,0,0,0,1.0), (1,1,0,0,10.0), (2,2,0,0,25.0), (0,1,2,0,50.0) ],
                'seed'              : "ai rocks!",
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
        elif o in ("-C", "--num-colors"):
            my_args['num-colors'] = int(a)
        elif o in ("-H", "--num-shapes"):
            my_args['num-shapes'] = int(a)
        elif o in ("-S", "--num-sizes"):
            my_args['num-sizes'] = int(a)
        elif o in ("-L", "--num-luminescences"):
            my_args['num-luminescences'] = int(a)
        elif o in ("-V", "--combo-values"):
            my_args['combo-values'] = []
            for y in a.split(':'):
                values = a.split(",")
                combo = []
                for x in combo[:4]:
                    combo.append( int(x) )
                combo.append( float(combo[4]) )
                my_args['combo-values'].append(combo)
        elif o in ("-Z", "--seed"):
            my_args['seed'] = a
        elif o in ("-h", "--help"):
            usage()
            sys.exit(1)
        else:
            assert False, "Unhandled option: '%s:%s'" % (o, a)
            
    return my_args
    
def main():
    args = getArgs()
    (colors, num_colors,
     shapes, num_shapes,
     sizes, num_sizes,
     luminescences, num_luminescences,
     combo_values, num_combo_values) = initialize(args['num-colors'],
                                                  args['num-shapes'],
                                                  args['num-sizes'],
                                                  args['num-luminescences'],
                                                  args['combo-values'],
                                                  args['seed'])

    of = ObjectEnumeration(colors, shapes, sizes,
                           luminescences, combo_values)

    if args['output'] != '-':
        fout = open(args['output'], "w")
    else:
        fout = sys.stdout

    for i in range(int(args['num-objects'])):
        obj = of.createObject(bool(args['use-luminescence']))
        print >>fout, obj
    if args['output'] != '-':
        fout.close()
    
    return

if __name__ == "__main__":
    main()
