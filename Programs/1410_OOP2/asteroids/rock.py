from polygon import Polygon
import random
import math

class Rock(Polygon):
    def __init__(self, x, y, world_width, world_height):
        dx = 0
        dy = 0
        rotation = random.uniform(0, 359.9)
        Polygon.__init__(self, x, y, dx, dy, rotation, world_width, world_height)
        point_list = self.createRandomPolygon(20,5)
        self.setPolygon(point_list)
        self.mSpinRate = random.uniform(0.1, 90) * random.choice((1,-1))
        self.accelerate(random.uniform(10, 20))

    def createRandomPolygon(self, radius, number_of_points):
        point_list = []
        for degree in range(0,360, 360//number_of_points):
            angle = math.radians(degree)
            distance = random.uniform(radius * 0.7, radius * 1.3)
            newx = distance * math.cos(angle)
            newy = distance * math.sin(angle)
            point_list.append((newx,newy))
        return point_list

    def getSpinRate(self):
        return self.mSpinRate

    def setSpinRate(self,spin_rate):
        self.mSpinRate = spin_rate

    def evolve(self,dt):
        self.rotate(self.getSpinRate() * dt)
        self.move(dt)