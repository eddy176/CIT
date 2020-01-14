from rotatable import Rotatable
import math
import pygame

class Polygon(Rotatable):

    def __init__(self, x, y, dx, dy, rotation, world_width, world_height):
        Rotatable.__init__(self, x, y, dx, dy, rotation, world_width, world_height)
        self.mPoly = []
        self.mColor = (255,255,255)

    def getPolygon(self):
        return self.mPoly

    def getColor(self):
        return self.mColor

    def setPolygon(self, points_list):
        if self.mPoly != points_list:
            self.mPoly = points_list

    def setColor(self, color):
        if self.mColor != color:
            self.mColor = color

    def draw(self, surface):
        polyPoints = self.getPolygon()
        newpoints = self.rotateAndTranslatePointList(polyPoints)
        pygame.draw.polygon(surface, self.getColor(), newpoints)


    ##PART 2!!!!!!!!!!
    def getRadius(self):
        t = 0
        c = 0
        for x, y in self.getPolygon():
            distance = math.sqrt(x**2 + y**2)
            t += distance
            c += 1
        if c > 0:
            return t/c
        return t