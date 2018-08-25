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

def bubbleSort(a):
    changes = True
    while changes == True:
        changes = False
        for i in range(len(a)-1):
            if a[i]>a[i + 1]:
                a[i], a[i + 1] = a[i+1],a[i]
                changes = True
    print("Now it's sorted!" + '\n' + str(a))
    return a

def checkIfSorted(uList, sortedList):
    uList2 = uList[:]
    uList2.sort()
    if sortedList == uList2:
        return print(True)
    else:
        return print(False)

def main():
    uList = createRandomList(getSize())
    sortedList = bubbleSort(uList)
    checkIfSorted(uList, sortedList)
main()