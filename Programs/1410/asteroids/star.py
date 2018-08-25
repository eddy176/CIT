from circle import Circle
import random

class Star(Circle):

    def __init__(self, x, y, world_width, world_height):
        dx = 0
        dy = 0
        rotation = 0
        radius = 2
        Circle.__init__(self, x, y, dx, dy, rotation, radius, world_width, world_height)
        self.mBrightness = random.randrange(0, 255)

    def getBrightness(self):
        return self.mBrightness

    def setBrightness(self, brightness):
        if brightness >= 0 and brightness <= 255:
            self.mBrightness = brightness
            self.mColor = (brightness, brightness, brightness)

    def evolve(self, dt):
        choices = (10, -10, 0)
        self.setBrightness(self.getBrightness() + random.choice(choices))