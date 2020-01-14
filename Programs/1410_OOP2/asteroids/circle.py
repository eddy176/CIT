from rotatable import Rotatable
import pygame

class Circle(Rotatable):
    def __init__(self,x,y,dx,dy,rotation,radius,world_width,world_height):
        Rotatable.__init__(self, x, y, dx, dy, rotation, world_width, world_height)
        self.mRadius = radius
        self.mColor = (255,255,255)

    def getColor(self):
        return self.mColor

    def setColor(self,color):
        self.mColor = color

    def getRadius(self):
        return self.mRadius

    def setRadius(self,radius):
        if radius >= 1:
            self.mRadius = radius

    def draw(self,surface):
        x = self.getX()
        y = self.getY()
        pos = (int(x),int(y))
        pygame.draw.circle(surface, self.getColor(), pos , self.getRadius())