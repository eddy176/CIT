import random
import sys
import math


class Count:

    def __init__(self):
        self.mCompares = 0
        self.mSwaps = 0

    def getCompares(self):
        return self.mCompares

    def getSwaps(self):
        return self.mSwaps

    def incSwaps(self):
        self.mSwaps += 1

    def incCompares(self):
        self.mCompares += 1


def getSize():
    size = input('How large do you want your list? ')
    return size


def createRandomList(size):
    a = []
    for i in range(int(size)):
        a.append(random.randrange(0, size))
    return a

def createNearlySortedList(size):
    a = createRandomList(size)
    a.sort()
    a[0], a[len(a)-1] = a[len(a)-1], a[0]
    return a


def bubbleSort(a, mCount):
    changes = True
    while changes:
        changes = False
        for i in range(len(a) - 1):
            mCount.incCompares()
            if a[i] > a[i + 1]:
                mCount.incSwaps()
                a[i], a[i + 1] = a[i + 1], a[i]
                changes = True
    return a


def shakerSort(a1, mCount):
    changes = True
    while changes:
        changes = False
        for i in range(len(a1)-1):
            mCount.incCompares()
            if a1[i] > a1[i + 1]:
                mCount.incSwaps()
                a1[i], a1[i + 1] = a1[i+1], a1[i]
                changes = True
        if changes:
            changes = False
            for i in range(len(a1) - 2, -1, -1):
                mCount.incCompares()
                if a1[i] > a1[i + 1]:
                    mCount.incSwaps()
                    a1[i], a1[i + 1] = a1[i + 1], a1[i]
                    changes = True
    return a1


def selectionSort(a1, mCount):
    for i in range(len(a1)):
        low = i
        for j in range(i+1, len(a1)):
            mCount.incCompares()
            if a1[j] < a1[low]:
                low = j
        mCount.incSwaps()
        a1[i], a1[low] = a1[low], a1[i]
    return a1


def mergeSort(a1, mCount):
    if len(a1) <= 1:
        return
    split = len(a1) // 2
    lhs = a1[:split]
    rhs = a1[split:]
    mergeSort(lhs, mCount)
    mergeSort(rhs, mCount)
    i, j = 0, 0
    k = 0
    while i < len(lhs) and j < len(rhs):
        mCount.incCompares()
        if lhs[i] < rhs[j]:
            mCount.incSwaps()
            a1[k] = lhs[i]
            k += 1
            i += 1
        else:
            mCount.incSwaps()
            a1[k] = rhs[j]
            k += 1
            j += 1
    while j < len(rhs):
        mCount.incSwaps()
        mCount.incCompares()
        a1[k] = rhs[j]
        k += 1
        j += 1
    while i < len(lhs):
        mCount.incSwaps()
        mCount.incCompares()
        a1[k] = lhs[i]
        k += 1
        i += 1
    return a1


def isModified():
    mod = input('Do you want to run modified sort?(yes or no)')
    if mod[0] == 'y' or mod[0] == 'Y':
        return True
    return False


def quickSort(a, low, high, modified, mCount):
    if high - low <= 0:
        mCount.incCompares()
        return
    if modified:
        mCount.incSwaps()
        mid = (low + high) // 2
        a[low], a[mid] = a[mid], a[low]
    lM = low + 1
    for i in range(low, high):
        mCount.incCompares()
        if a[i] < a[low]:
            mCount.incSwaps()
            a[i], a[lM] = a[lM], a[i]
            lM += 1  # lM += 1
    pivotIndex = lM - 1
    mCount.incSwaps()
    a[low], a[pivotIndex] = a[pivotIndex], a[low]
    quickSort(a, low, pivotIndex, modified, mCount)
    quickSort(a, pivotIndex + 1, high, modified, mCount)
    return a


def callQuick(a, mCount):
    quickSort(a, 0, len(a)-1, False, mCount)

def modCallQuick(a, mCount):
    quickSort(a, 0, len(a)-1, True, mCount)


def hashSort(a, mCount):
    freq = []
    for x in range(len(a)):
        freq.append(0)
        mCount.incSwaps()
    for values in a:
        mCount.incCompares()
        freq[values] += 1
    num = 0
    for i in range(len(freq)):
        for j in range(freq[i]):
            mCount.incSwaps()
            a[num] = i
            num += 1
    return a


def checkIfSorted(uList, bbSort, shakeSort, selSort, mSort, qSort, hSort):
    uList1 = uList[:]
    uList1.sort()
    print('Here is your pysort:\n' + str(uList1))
    if uList1 == bbSort:
        print('True')
    if uList1 == shakeSort:
        print('True')
    if uList1 == selSort:
        print('True')
    if uList1 == mSort:
        print('True')
    if uList1 == qSort:
        print('True')
    if uList1 == hSort:
        print('True')
    else:
        print('False')


def main():
    sys.setrecursionlimit(5000)
    print(end='\t')
    sortAll = [bubbleSort, shakerSort, selectionSort, mergeSort, callQuick, modCallQuick, hashSort]
    sortNames = ["bubbleSort", "shakerSort", "selectionSort", "mergeSort", "quickSort","modQuickSort", "hashSort"]
    for i in range(len(sortNames)):
        print(sortNames[i], end='\t')
    print()
    for i in range(3, 13):
        size = 2**i
        print(i, end='\t')
        for sort in sortAll:
            a = createNearlySortedList(size)
            totalCount = Count()
            sort(a, totalCount)
            if totalCount.getCompares() != 0 or totalCount.getSwaps() != 0:
                print(math.log2(totalCount.getSwaps()), end='\t')
            else:
                print("0")
        print()


main()