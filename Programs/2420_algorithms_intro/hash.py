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


def hashSort(a):
    freq = []
    for x in range(len(a)):
        freq.append(0)
    for values in a:
        freq[values] += 1
    num = 0
    for i in range(len(freq)):
            for j in range(freq[i]):
                a[num] = i
                num += 1
    print("Now it's sorted!\n" + str(a))
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
    sortedList = hashSort(uList)
    checkIfSorted(uList, sortedList)


main()