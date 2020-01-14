from polygon import Polygon
from bullet import Bullet

class Ship(Polygon):

    def __init__(self, x, y, world_width, world_height):
        dx = 0
        dy = 0
        rotation = 0
        Polygon.__init__(self, x, y, dx, dy, rotation, world_width, world_height)
        point_list = [(10, 0), (-10, -10), (-5, 0), (-10, 10)]
        self.setPolygon(point_list)

    def fire(self):
        x, y = self.getPolygon()[0]
        newX, newY = self.rotateAndTranslatePoint(x, y)
        dx = self.getDX()
        dy = self.getDY()
        rotation = self.getRotation()
        width = self.getWorldWidth()
        height = self.getWorldHeight()
        bullet = Bullet(newX, newY, dx, dy, rotation, width, height)
        return bullet

    def evolve(self, dt):
        self.move(dt)