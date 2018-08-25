import time


def isPrime(n):

    if n == 1:
        return False
    elif n == 2:
        return True
    else:
        count = 0
        for x in range(2, n):
            if(n % x == 0):
                count += 1
                if count != 0:
                    return False
            else:
                return True


class Hash:

    def __init__(self, expectedSize):
        tableSize = 2 * expectedSize + 1
        while not isPrime(tableSize):
            tableSize += 2
        self.mTable = [None] * tableSize

    def Insert(self, item):
        if self.Exists(item):
            return False
        key = int(item)
        index = key % len(self.mTable)
        while self.mTable[index] is not None:
            index += 1
            if index >= len(self.mTable):
                index = 0
        self.mTable[index] = item
        return True

    def Exists(self, item):
        key = int(item)
        index = key % len(self.mTable)
        while True:
            if self.mTable[index] is None:
                return False
            if self.mTable[index] and self.mTable[index] == item:
                return True
            index += 1
            if index >= len(self.mTable):
                index = 0

    def traverse(self, callback):
        for i in range(len(self.mTable)):
            if self.mTable[i] is not None and self.mTable[i] is not False:
                callback(self.mTable[i])

    def delete(self, dummy):
        if not self.Exists(dummy):
            return False
        key = int(dummy)
        index = key % len(self.mTable)
        while not (self.mTable[index] and self.mTable[index] == dummy):
            index += 1
            if index >= len(self.mTable):
                index = 0
        self.mTable[index] = False
        return True

    def countNodes(self):
        count = 0
        for i in range(len(self.mTable)):
            if self.mTable[i]:
                count += 1
        return count

    def retrieve(self, item):
        if self.Exists(item):
            key = int(item)
            index = key % len(self.mTable)
            while not (self.mTable[index] and self.mTable[index] == item):
                index += 1
                if index >= len(self.mTable):
                    index = 0
            return self.mTable[index]
        return None


class Students:

    def __init__(self, lName, fName, sn, email, age):
        self.mFName = fName
        self.mLName = lName
        self.mSocial = sn
        self.mEmail = email
        self.mAge = age

    def getInput(self):
        return input('What is the name of your file? ')

    def getFName(self):
        return self.mFName

    def getLName(self):
        return self.mLName

    def getSN(self):
        return self.mSocial

    def getEmail(self):
        return self.mEmail

    def getAge(self):
        return self.mAge

    def setFName(self, item):
        self.mFName = item

    def setLName(self, item):
        self.mLName = item

    def setSN(self, item):
        self.mSocial = item

    def setEmail(self, item):
        self.mEmail = item

    def setAge(self, item):
        self.mAge = item

    def __eq__(self, other):
        return self.mSocial == other.mSocial

    def __lt__(self, other):
        return self.mSocial < other.mSocial

    def __gt__(self, other):
        return self.mSocial > other.mSocial

    def __le__(self, other):
        return self.mSocial <= other.mSocial

    def __ge__(self, other):
        return self.mSocial >= other.mSocial

    def __ne__(self, other):
        return self.mSocial != other.mSocial

    def __int__(self):
        return int(self.mSocial.replace ('-', ''))

class Node:
    def __init__(self, item, left, right):
        self.mItem = item
        self.mLeft = left
        self.mRight = right

total_age = 0
def addAge(s):
    global total_age
    total_age += int(s.getAge())

rtotal_age = 0
def raddAge(s):
    global rtotal_age
    rtotal_age += int(s.getAge())


def main():
    global total_age
    global rtotal_age
    fin = open('InsertNamesMedium.txt', 'r')
    hash_object = Hash(300000)
    mcount = 0
    start = time.time()
    for line in fin:
        line = line.split()
        student_object = Students(line[0], line[1], line[2], line[3], line[4])
        if not hash_object.Insert(student_object):
            mcount += 1
    stop = time.time()
    fin.close()
    print("Insert errors:",mcount)
    print('Time:',round(stop-start, 2))

    hash_object.traverse(addAge)
    print("Average age is " + str(round(total_age / hash_object.countNodes(), 6)) + '.')

    fdelete = open('DeleteNamesMedium.txt', 'r')
    dcount = 0
    dstart = time.time()
    for line in fdelete:
        line = line.split()
        student_object = Students('', '', line[0], '', '')
        if not hash_object.delete(student_object):
            dcount += 1
    dstop = time.time()
    fdelete.close()
    print('Delete errors:', dcount)
    print('Time:', round(dstop - dstart, 2))

    fretrieve = open('RetrieveNamesMedium.txt', 'r')
    rstart = time.time()
    retcount = 0
    rcount = 0
    for line in fretrieve:
        line = line.split()
        student_object = Students('', '', line[0], '', '')
        retrievedStudent = hash_object.retrieve(student_object)
        if not retrievedStudent:
            rcount += 1
        else:
            retcount += 1
            rtotal_age += int(retrievedStudent.getAge())
    print('Retrieve errors:', rcount)
    print("Average age is " + str(round(rtotal_age / retcount, 6)) + '.')

    rstop = time.time()
    fretrieve.close()
    print('Hashobjects in hash table:', hash_object.countNodes())
    print('Time:', round(rstop - rstart, 2))


main()
