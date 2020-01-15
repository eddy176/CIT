#!/usr/bin/env python3
import random, sys, math

def explore( g, visited, u):
    (nodes, edges) = g
    visited[u-1] = True
    for v in edges[u]:
        if not visited[v-1]:
            explore( (nodes, edges), visited, v)
    return

def is_connected( g ):
    (nodes, edges) = g
    visited = [ False for n in nodes ]
    explore( (nodes, edges), visited, 1)
    for n in nodes:
        if not visited[n-1]:
            return False
    return True

def create_graph(num_nodes, max_weight):
    nodes = [ i+1 for i in range(num_nodes) ]

    connected = False
    while not connected:
        edges = {}
        edge_list = {}
        for i in range(num_nodes):
            edges[i+1] = {}

        count = num_nodes*(1 + int(math.log(num_nodes)/math.log(10)))
        i = 0
        while i < count or (i % num_nodes) or (not connected ):
            u = random.randint(1,num_nodes)
            v = random.randint(1,num_nodes)
            if u != v:
                w = random.randint(1, max_weight)
                edges[u][v] = w
                edges[v][u] = w
                if u < v:
                    edge_list[ (u,v) ] = w
                else:
                    edge_list[ (v,u) ] = w
                i += 1
                if i >= count and i%(num_nodes/10) == 0:
                    connected = True
                    connected = is_connected( (nodes, edges) )
    return (nodes, edges), edge_list

def display_graph( fout, g, edge_list ):
    (nodes, edges) = g
    print( len(nodes) )
    for (u,v) in edge_list:
        s = "%d %d %d\n" % ( u-1, v-1, edge_list[ (u,v) ] )
        fout.write( s )
    s = "-1 -1 -1\n"
    fout.write( s )
    return

def main():
    if( len( sys.argv ) ) < 3:
        print( "usage: " + str( sys.argv[0] ) + " vertex_count max_weight" )
        sys.exit( 1 )
    sys.setrecursionlimit(int(sys.argv[1])*2)
    G, edge_list = create_graph(int(sys.argv[1]), int(sys.argv[2]))
    display_graph(sys.stdout, G, edge_list)
    return

if __name__ == "__main__":
    main()
