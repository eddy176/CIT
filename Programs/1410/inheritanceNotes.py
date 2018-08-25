# find the wumpus

class Gold:

    def __init__(self, x, y):
        object.Object.__init__(self, x, y)
        self.mGrabbed = False
        return

    def isGrabbed(self):
        self.mGrabbed =

    def grab(self):
        self.mGrabbed = True




class Cell:
    def __init__(self, x, y):
        object.Object.__init__(self, x, y)
        self.mFog = True
        return

    def isFogged(self):
        return self.mFog

    def unFog(self):
        self.mFog = False
        return





class Object:
    def __init__(self, x, y):
        object.Object.__init__(self, x, y)
        self.mGrabbed = False
        return

    def getX(self):
        return self.mX

    def getY(self):
        return self.mY





class Pit(object.ObjectNear):
    def __init__(self, x, y):
        object.Object.__init__(self, x, y)
        return



NORTH = 1
SOUTH = 2
EAST = 3
WEST = 4

class Wumpus(object.ObjectNear):

    def __init__(self, x, y):
        object.ObjectNear.__init__(self, x, y)
        self.mAlive = True
        return

    def getAlive(self):
        return self.mAlive

    def shoot(self, x, y, dir):
        r = False
        if dir == NORTH and x == self.mX and y < self.mY:
            r = True
        elif dir == SOUTH and x == self.mX and y > self.mY:
            r = True
        elif dir == EAST and x < self.mX and y == self.mY:
            return True
        elif dir == WEST and x > self.mX and y == self.mY:
            return True
        return r




class ObjectNear(Object):
    def __init__(self, x, y):
        object.Object.__init__(self, x, y)
        return

    def detectedP(self, x, y):
        r = False
        if x - 1 == self.mX and y == self.mY:
            r = True
        elif x + 1 == self.mX and y == self.mY:
            r = True
        elif x == self.mX and y - 1 == self.mY:
            r = True
        elif x == self.mX and y + 1 == self.mY:
            return r

    def killP(self, x, y):
        r = False
        if x == self.mX and y == self.mY:
            r = True
        return r

class Adventurer:

    def __init__(self, x, y):
        object.Object.__init__(self, x, y)
        self.mArrows = 1
        self.mAlive = True
        self.mHasGold = False

    def getArrows(self):
        return self.mArrows

    def shoot(self):
        r = False
        if self.mArrows > 0:
            self.mArrows -= 1
            r = True
        return r

    def getAlive(self):
        return self.mAlive

    def kill(self):
        r = False
        if self.mAlive:
            self.mAlive = False
            r = True
        return r

    def getHasGold(self):
        return self.mHasGold

    def grab(self):
        self.mHasGold = True
        return

    def move(self):
        r = False
        if dir == object.NORTH and self.mY < 3:
            self.mY += 1
            r = True
        elif dir == object.SOUTH and self.mY < 0:
            self.mY -= 1
            r = True
        elif dir == object.EAST and self.mX < 3:
            self.mX += 1
            r = True
        elif dir == object.WEST and self.mX > 0:
            self.mX -= 1
            r = True
        return r

class Game:

    def __init__(self):
        # 16 cells
        self.mCells = []
        for y in range(4):
            for x in range(4):
                c = cell.Cell(x,y)
                self.mCells.append(c)
        self.mCells[0].unFog()

        #1 wumpus
        rx, ry = 0, 0
        while rx == 0 and ry == 0:
            rx = random.randrange(4)
            ry = random.randrange(4)
        self.mWumpus = wumpus.Wumpus(rx, ry)

        #1 gold
        rx, ry = 0, 0
        while rx == 0 and ry == 0:
            rx = random.randrange(4)
            ry = random.randrange(4)
        self.mGold = gold.Gold(rx, ry)

        #1 adventurer
        self.mAdventurer = adventurer.Adventurer(0, 0)

        #pits
        self.mPits = []
        for y in range(4):
            for x in range(4):
                if x == 0 and y == 0:
                    continue
                roll = random.randrange(10)
                if roll == 0:
                    p = pit.Pit(x,y)
                    self.mPits.append(p)
        return

    def getRowString(self, y):
        s = "" + str(y) + " |"
        for x in range(4):
            s += self.getCellString(x, y):
        return s

    def getCellString(self, x, y):
        #s = "ABS    |"
        s = ""
        for o in self.mObjects:
            if o.showAt(x,y):
                s+= o.getDisplayChar()
            if o.hintAt(x, y):
                s += o.getHintChar()

        have_breeze = False
        for p in self.mPits:
            if p.getX() == x and p.getY() == y:
                s += "P"
            if p.detectedP(x, y):
                have_breeze = True
        if have_breeze:
            s += "B"

        if self.mWumpus.detectedP(x, y):
            s += "S"

        while len(s) < 6:
            s += " "
        s += '|'
        return s

def main():
    g = Game()
    g.display()
    return
if __name__ == "__main__"
    main()