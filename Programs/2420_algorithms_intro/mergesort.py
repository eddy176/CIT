import random

def getSize():
    size = input('How large do you want your list? ')
    return size

def createRandomList(size):
    a = []
    for i in range(int(size)):
        a.append(random.randrange(0, 10))
    print('Here is your list', a)
    return a

def mergeSort(a1):
    if len(a1) <= 1:
        return
    split = len(a1)//2
    lhs = a1[:split]
    rhs = a1[split:]
    mergeSort(lhs)
    mergeSort(rhs)
    i,j = 0,0
    k = 0
    while i < len(lhs) and j < len(rhs):
        if lhs[i] < rhs[j]:
            a1[k] = lhs[i]
            k += 1
            i += 1
        else:
            a1[k] = rhs[j]
            k += 1
            j += 1
    while j < len(rhs):
        a1[k] = rhs[j]
        k += 1
        j += 1
    while i < len(lhs):
        a1[k] = lhs[i]
        k += 1
        i += 1
    print("Now it's sorted!\n" + str(a1))

def checkIfSorted(newList, uList):
    newList = newList[:]
    newList.sort()
    if newList == uList:
        return print(True)
    else:
        return print(False)

def main():
    uList = createRandomList(getSize())
    newList = uList[:]
    mergeSort(uList)
    checkIfSorted(newList, uList)
main()