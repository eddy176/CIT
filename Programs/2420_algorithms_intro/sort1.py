import random

def getSize():
    size = input('How large do you want your list? ')
    return size

def createRandomList(size):
    a = []
    for i in range(int(size)):
        a.append(random.randrange(0, size))
    print('Here is your list', a)
    return a

def bubbleSort(a1):
    changes = True
    while changes == True:
        changes = False
        for i in range(len(a1)-1):
            if a1[i]>a1[i + 1]:
                a1[i], a1[i + 1] = a1[i+1],a1[i]
                changes = True
    print("Now it's sorted!" + '\n' + str(a1))
    return a1

def shakerSort(a1):
    changes = True
    while changes == True:
        changes = False
        for i in range(len(a1)-1):
            if a1[i]>a1[i + 1]:
                a1[i], a1[i + 1] = a1[i+1],a1[i]
                changes = True
        if changes == True:
            changes = False
            for i in range(len(a1) - 2, -1, -1):
                if a1[i] > a1[i + 1]:
                    a1[i], a1[i + 1] = a1[i + 1], a1[i]
                    changes = True
    print("Now it's sorted!" + '\n' + str(a1))
    return a1

def selectionSort(a1):
    for i in range(len(a1)):
        low = i
        for j in range(i+1,len(a1)):
            if a1[j] < a1[low]:
                low = j
        a1[i], a1[low] = a1[low], a1[i]
    print("Now it's sorted!\n" + str(a1))
    return a1

def checkIfSorted(uList, bbSort, shakeSort, selSort):
    uList1 = uList[:]
    uList1.sort()
    print('Here is your pysort:\n' + str(uList1))
    if uList1 == bbSort:
        print('True')
    if uList1 == shakeSort:
        print('True')
    if uList1 == selSort:
        print('True')
    else:
        print('False')
    return

def main():
    uList = createRandomList(getSize())
    bbSort = bubbleSort(uList[:])
    shakeSort = shakerSort(uList[:])
    selSort = selectionSort(uList[:])
    checkIfSorted(uList, bbSort, shakeSort, selSort)
main()