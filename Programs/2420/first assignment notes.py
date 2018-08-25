
# allows repeats
def createRandomList(size):
    a = []
    for i in range(size):
        a.append()
    return a

def mergeSort(a):
    half = len(a/2)
    lhs = a[:half]
    rhs = a[half:]
    i = 0
    j = 0
    for n in range(len(a)):
        while i != half and j != half: # inner final loop
            if lhs[i]< rhs[j]:
                a[0] = lhs[i]
                i += 1
            else:
                a[0] = rhs[j]
                j += 1
        # go log base 2 of n (the length of the list of random numbers)

