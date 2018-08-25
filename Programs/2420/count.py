import sys
import cmath
from sorts import Sorts

def main():
    sys.setrecursionlimit(5000)
    z = Sorts.getSize()
    print(end = '\t')
    sortal = Sorts.sortingAlgorithms                    ## need to finish sortingAlgorithms method in class Sorts
    for sort in sortal:
        print(sort.__name__,end='\t')
    print(end = '\t')
    for i in range(3,13):
        size = z**i
        print(size, end='\t')
        for sort in sortal:
            a = Sorts.createRandomList(size)
            count = Sorts.counter()                     ## need a counter in class Sorts' sortingAlgorithms
            sort(a, count)
            print(cmath.log(2,count.compares), end='\t')
        print('')