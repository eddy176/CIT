import pygame
class Wick:
    def __init__(self, x, y, width, height, color):
        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height
        self.mColor = color
        p1 = (x, y + height)
        p2 = (x + width, y)
        self.mPoints = [p1, p2]

    def draw(self, surface):
        for i in range(len(self.mPoints) - 1):
            p = self.mPoints[i]
            q = self.mPoints[i + 1]
            pygame.draw.line(surface, self.mColor, p, q, 5)