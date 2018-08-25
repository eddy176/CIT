from ship import Ship
from rock import Rock
from star import Star
import random

class Asteroids:

    def __init__(self, world_width, world_height):
        self.mWorldWidth = world_width
        self.mWorldHeight = world_height

        self.mShip = Ship(world_width//2, world_height//2, world_width, world_height)
        self.mShip.setColor((0, 255, 0))

        self.mRocks = []
        for i in range(10):
            x = random.randint(0, world_width)
            y = random.randint(0, world_width)
            r = Rock(x, y, world_width, world_height)
            num_points = random.randint(5, 10)
            radius = random.randint(10, 20)
            point_list = r.createRandomPolygon(radius, num_points)
            r.setPolygon(point_list)
            r.setColor((0, 0, 255))
            self.mRocks.append(r)

        self.mStars = []
        for i in range(20):
            x = random.randint(0, world_width)
            y = random.randint(0, world_width)
            s = Star(x, y, world_width, world_height)
            self.mStars.append(s)
        self.mBullets = []
        self.mObjects = [self.mShip] + self.mRocks + self.mStars + self.mBullets

    def getWorldWidth(self):
        return self.mWorldWidth

    def getWorldHeight(self):
        return self.mWorldHeight

    def getBullets(self):
        return self.mBullets

    def getStars(self):
        return self.mStars

    def getShip(self):
        return self.mShip

    def getRocks(self):
        return self.mRocks

    def getObjects(self):
        return self.mObjects

    def turnShipLeft(self, delta_rotation):
        self.mShip.rotate(-delta_rotation)

    def turnShipRight(self, delta_rotation):
        self.mShip.rotate(delta_rotation)

    def accelerateShip(self, delta_velocity):
        self.mShip.accelerate(delta_velocity)

    def fire(self):
        if len(self.getBullets()) < 3:
            b = self.getShip().fire()
            b.setColor((255, 0, 0))
            self.mBullets.append(b)
            self.mObjects.append(b)

    def evolveAllObjects(self,dt):
        for obj in self.mObjects:
            obj.evolve(dt)

    def collideShipAndBullets(self):
        for b in self.mBullets:
            if self.mShip.hits(b):
                self.mShip.setActive(False)
                b.setActive(False)

    def collideShipAndRocks(self):
        for r in self.mRocks:
            if self.mShip.hits(r):
                self.mShip.setActive(False)
                r.setActive(False)

    def collideRocksAndBullets(self):
        for b in self.mBullets:
            for r in self.mRocks:
                if b.hits(r):
                    b.setActive(False)
                    r.setActive(False)

    def removeInactiveObjects(self):
        for obj in self.mObjects:
            if not obj.getActive():
                self.mObjects.remove(obj)
        for b in self.mBullets:
            if not b.getActive():
                self.mBullets.remove(b)
        for r in self.mRocks:
            if not r.getActive():
                self.mRocks.remove(r)

    def evolve(self,dt):
        if not self.getShip().getActive():
            return
        if len(self.mRocks) == 0:
            self.mShip.setActive(False)
            return
        self.evolveAllObjects(dt)
        self.collideRocksAndBullets()
        self.collideShipAndBullets()
        self.collideShipAndRocks()
        self.removeInactiveObjects()

    def draw(self, surface):
        surface.fill((0, 0, 0))
        for obj in self.getObjects():
            if obj.getActive():
                obj.draw(surface)
