import random


def getSize():
    size = input('How large do you want your list? ')
    return size

def createRandomList(size):
    a = []
    for i in range(int(size)):
        a.append(random.randrange(0, int(size)))
    print('Here is your list', a)
    return a

def quickSort(a, low, high):
    if high - low <= 0:                             # make sure high-low is greater than 0
        return                                      # if not, return
    lM = low + 1                                    # set lM to low + 1
    for i in range(low, high):                      # loop from low to high in list
        if a[i] < a[low]:                           # if a at location i < a at location low
            a[i],a[lM] = a[lM], a[i]                # swap their places
            lM += 1                                 # lM += 1
    pivotIndex = lM - 1                             # pivotIndex becomes lM - 1
    a[low], a[pivotIndex] = a[pivotIndex], a[low]   # swap a at low with a at pivot index
    print("Now it's sorted!\n" + str(a))            # print results
    quickSort(a, low, pivotIndex)                   # recurse once
    quickSort(a, pivotIndex + 1, high)              # recurse twice

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
    quickSort(uList, 0, len(uList))
    checkIfSorted(newList, uList)
main()