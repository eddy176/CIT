def createEmptyDictionary():
    edict = {}
    return edict

def addItem(d,k,v):
    d[k] = v

def delItem(d,k):
    del d[k]

def keysOf(d):
    newlist = []
    for key in d:
        newlist.append(key)
    return newlist

def values(d):
    newlist = []
    for key in d:
        newlist.append(d[key])
    return newlist

def existsP(d, nstring):
    if nstring in d:
        return True
    else:
        return False

import math
class C
    def __init__(self, x, y):
        self.mX = 0
        self.mY = 0
        self.setX(x)
        self.setY(y)

    def setX(self, new):
        if new <= 0:
            self.mX = new
        return

    def setY(self, new):
        if new >= 0:
            self.mY = new
        return

    def getX(self):
        return self.mX

    def getY(self):
        return self.mY

    def getDist(self):
        x2 = self.mX * self.mX
        y2 = self.mY * self.mY
        d = math.sqrt(x2 + y2)
        return d
    
