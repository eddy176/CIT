import sys
import time

class BST:

    def __init__(self):
        self.mRoot = None

    def Insert(self, item):
        if self.Exists(item):
            return False
        self.mRoot = self.InsertR(item, self.mRoot)
        return True

    def Exists(self, item):
        return self.existsR(item, self.mRoot)

    def delete(self, dummy):
        if not self.Exists(dummy):
            return False
        self.mRoot = self.deleteR(dummy, self.mRoot)
        return True

    def countNodes(self):
        return self.countNodesR(self.mRoot)

    def traverse(self, callback):
        return self.traverseR(callback, self.mRoot)

    def retrieve(self, dummy):
        if not self.Exists(dummy):
            return None
        item = self.retrieveR(dummy, self.mRoot)
        return item

    # recursives

    def InsertR(self, item, current):
        if current is None:
            n = Node(item, None, None)
            current = n
        elif item < current.mItem:
            current.mLeft = self.InsertR(item, current.mLeft)
        else:
            current.mRight = self.InsertR(item, current.mRight)
        return current

    def existsR(self, dummy, current):
        if current is None:
            return False
        elif current.mItem == dummy:
            return True
        elif dummy < current.mItem:
            return self.existsR(dummy, current.mLeft)
        else:
            return self.existsR(dummy, current.mRight)

    def deleteR(self, dummy, current):
        if dummy < current.mItem:
            current.mLeft = self.deleteR(dummy, current.mLeft)
        elif dummy > current.mItem:
            current.mRight = self.deleteR(dummy, current.mRight)
        else:
            if current.mLeft is None and current.mRight is None:
                current = None
            elif current.mRight is None:
                current = current.mLeft
            elif current.mLeft is None:
                current = current.mRight
            else:
                s = current.mRight
                while s.mLeft is not None:
                    s = s.mLeft
                current.mItem = s.mItem
                current.mRight = self.deleteR(s.mItem, current.mRight)
        return current

    def countNodesR(self, current):
        if not current:
            return 0
        else:
            return 1 + self.countNodesR(current.mLeft) + self.countNodesR(current.mRight)

    def traverseR(self, callback, current):
        if current is None:
            return
        callback(current.mItem)
        self.traverseR(callback, current.mLeft)
        self.traverseR(callback, current.mRight)

    def retrieveR(self, dummy, current):
        if dummy < current.mItem:
            return self.retrieveR(dummy, current.mLeft)
        elif dummy > current.mItem:
            return self.retrieveR(dummy, current.mRight)
        else:
            return current.mItem


class Students:

    def __init__(self, lName, fName, sn, email, age):
        self.mFName = fName
        self.mLName = lName
        self.mSN = sn
        self.mEmail = email
        self.mAge = age

    def getInput(self):
        return input('What is the name of your file? ')

    def getFName(self):
        return self.mFName

    def getLName(self):
        return self.mLName

    def getSN(self):
        return self.mSN

    def getEmail(self):
        return self.mEmail

    def getAge(self):
        return self.mAge

    def setFName(self, item):
        self.mFName = item

    def setLName(self, item):
        self.mLName = item

    def setSN(self, item):
        self.mSN = item

    def setEmail(self, item):
        self.mEmail = item

    def setAge(self, item):
        self.mAge = item

    def __eq__(self, other):
        return self.mSN == other.mSN

    def __lt__(self, other):
        return self.mSN < other.mSN

    def __gt__(self, other):
        return self.mSN > other.mSN

    def __le__(self, other):
        return self.mSN <= other.mSN

    def __ge__(self, other):
        return self.mSN >= other.mSN

    def __ne__(self, other):
        return self.mSN <= other.mSN


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
    icount = 0
    students = BST()
    fin = open('InsertNames.txt', 'r')
    start = time.time()
    for line in fin:
        line = line.split()
        s = Students(line[0], line[1], line[2], line[3], line[4])
        if not students.Insert(s):
            icount += 1
    stop = time.time()
    fin.close()
    print("Insert errors:",icount)
    print('Time:',round(stop-start, 2))

    students.traverse(addAge)
    print("Average age is " + str(round(total_age / students.countNodes(), 2)) + '.')

    fdelete = open('DeleteNames.txt', 'r')
    dcount = 0
    dstart = time.time()
    for line in fdelete:
        line = line.split()
        s = Students('', '', line[0], '', '')
        if not students.delete(s):
            dcount += 1
    dstop = time.time()
    fdelete.close()
    print('Delete errors:', dcount)
    print('Time:', round(dstop - dstart, 2))

    fretrieve = open('RetrieveNames.txt', 'r')
    rstart = time.time()
    retcount = 0
    rcount = 0
    for line in fretrieve:
        line = line.split()
        s = Students('', '', line[0], '', '')
        retrievedStudent = students.retrieve(s)
        if not retrievedStudent:
            rcount += 1
        else:
            retcount += 1
            rtotal_age += int(retrievedStudent.getAge())
    print('Retrieve errors:', rcount)
    print("Average age is " + str(round(rtotal_age / retcount, 2)) + '.')

    rstop = time.time()
    fretrieve.close()
    print('Time:', round(rstop - rstart, 2))

    print(students.countNodes())


main()