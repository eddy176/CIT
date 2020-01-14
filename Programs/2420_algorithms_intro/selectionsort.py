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

def selectionSort(a):
    for i in range(len(a)):
        low = i
        for j in range(i+1,len(a)):
            if a[j] < a[low]:
                low = j
        a[i], a[low] = a[low], a[i]
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
    sortedList = selectionSort(uList)
    checkIfSorted(uList, sortedList)
main()