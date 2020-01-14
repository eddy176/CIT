import pygame
class Poly:
    def __init__(self, points, color):
        self.mPoints = points
        self.mColor = color
        return

    def draw(self, surface):
        pygame.draw.polygon(surface, self.mColor, self.mPoints, 0)