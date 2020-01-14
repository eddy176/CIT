import pygame
class Circle:
    def __init__(self, x, y, r, color):
        self.mX = x
        self.mY = y
        self.mRadius = r
        self.mColor = color

    def draw(self, surface):
        pos = (int(self.mX), int(self.mY))
        pygame.draw.circle(surface, self.mColor, pos, int(self.mRadius), 0)