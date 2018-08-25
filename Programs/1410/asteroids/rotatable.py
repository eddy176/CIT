import math
from movable import Movable


class Rotatable(Movable):
    def __init__(self, x, y, dx, dy, rotation, world_width, world_height):
        Movable.__init__(self, x, y, dx, dy, world_width, world_height)
        self.mRotation = rotation

    def getRotation(self):
        return self.mRotation

    def rotate(self, delta_rotation):
        self.mRotation += delta_rotation
        if self.mRotation < 0:
            self.mRotation += 360
        elif self.mRotation >= 360:
            self.mRotation -= 360

    def splitDeltaVIntoXAndY(self, rotation, delta_velocity):
        newB = math.radians(rotation)
        newX = delta_velocity * math.cos(newB)
        newY = delta_velocity * math.sin(newB)
        tup = (newX, newY)
        return tup

    def accelerate(self, delta_velocity):
        r = self.getRotation()
        x, y = self.splitDeltaVIntoXAndY(r, delta_velocity)
        self.mDX += x
        self.mDY += y

    def rotatePoint(self, x, y):
        distance = math.sqrt(x ** 2 + y ** 2)
        theta = math.atan2(y, x)
        angle = math.radians(self.getRotation())
        newtheta = theta + angle
        dx = distance * math.cos(newtheta)
        dy = distance * math.sin(newtheta)
        tup = (dx, dy)
        return tup

    def translatePoint(self, x, y):
        x += self.getX()
        y += self.getY()
        tup = (x, y)
        return tup

    def rotateAndTranslatePoint(self, x, y):
        xr, yr = self.rotatePoint(x, y)
        xt, yt = self.translatePoint(xr, yr)
        tup = (xt, yt)
        return tup

    def rotateAndTranslatePointList(self, point_list):
        new = []
        for point in point_list:
            x = point[0]
            y = point[1]
            newpoint = self.rotateAndTranslatePoint(x, y)
            new.append(newpoint)
        return new