from collections import deque


class Stack:

    def __init__(self):
        self.stack = []

    def push(self, p):
        self.stack.append(p)

    def pop(self):
        p = self.stack.pop()
        return p

    def top(self):
        return self.stack[len(self.stack) - 1]

    def isEmpty(self):
        if len(self.stack) == 0:
            return True
        else:
            return False


class Graph:
    def __init__(self, vertices):
        self.numVertices = vertices
        self.mGraph = []
        for i in range(self.numVertices):
            self.mGraph.append([])

    def addEdges(self, v0, v1):
        for i in range(len(self.mGraph)):
            if v0 == i:
                self.mGraph[i].append(v1)

    def depthFirst(self, v0, v1):
        s = Stack()
        visited = [False] * len(self.mGraph)
        # put v0 in s, and mark it visited
        s.push(v0)
        visited[v0] = True
        path = []
        while not s.isEmpty():
            c = s.top()
            if c == v1:
                # build path and return it
                while not s.isEmpty():
                    path.append(s.pop())
                return path[::-1]
            unvisitedNeighbor = -1
            for n in self.mGraph[c]:
                if not visited[n]:
                    unvisitedNeighbor = n
                    # put n in s and mark it visited
                    s.push(unvisitedNeighbor)
                    visited[unvisitedNeighbor] = True
                    break
            if unvisitedNeighbor == -1:
                s.pop()
        return None

    def breadthFirst(self, v0, v1):
        q = deque()
        path = []
        prev = [-1] * self.numVertices
        prev[v0] = v0
        q.append(v0)
        while q:
            c = q.popleft()
            if c == v1:
                path.append(c)
                i = 0
                while v0 not in path:
                    path.append(prev[path[i]])
                    i += 1
                return path[::-1]
            neighbor = self.mGraph[c]
            for n in neighbor:
                if prev[n] == -1:
                    q.append(n)
                    prev[n] = c
        return None


def main():
    data = []
    fin = open('mygraph.txt', 'r')
    for line in fin:
        line = line.strip()
        data.append(line)

    verts = int(data[0])
    edges = int(data[1])
    t1index = 3 + edges
    t2index = 4 + edges
    t3incex = 5 + edges
    myGraph = Graph(verts)
    for i in range(2, edges + 2):
        # print(data[i][0], data[i][2])
        myGraph.addEdges(int(data[i][0]), int(data[i][2]))
    t1 = myGraph.breadthFirst(int(data[t1index][0]), int(data[t1index][2]))
    t2 = myGraph.breadthFirst(int(data[t2index][0]), int(data[t2index][2]))
    t3 = myGraph.breadthFirst(int(data[t3incex][0]), int(data[t3incex][2]))
    print('BreadthFirst tests:')
    print('breadthFirst Test 1 output should be 0, 3.')
    print('Output: t1', t1)
    print('breadthFirst Test 2 output should be None.')
    print('Output: t2', t2)
    print('breadthFirst Test 3 output should be 4, 1, 2.')
    print('Output: t3', t3)
    print('\n\n')

    print('Now DepthFirst!')
    t1 = myGraph.depthFirst(int(data[t1index][0]), int(data[t1index][2]))
    t2 = myGraph.depthFirst(int(data[t2index][0]), int(data[t2index][2]))
    t3 = myGraph.depthFirst(int(data[t3incex][0]), int(data[t3incex][2]))
    print('depthFirst test 1 output should be 0, 1, 2, 3.')
    print('Output: t1', t1)
    print('depthFirst test 2 output should be None.')
    print('Output: t2', t2)
    print('depthFirst test 3 output should be 4, 1, 2.')
    print('Output: t3', t3)



main()
