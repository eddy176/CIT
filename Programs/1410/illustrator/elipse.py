import pygame
class Elipse:
    def __init__(self, x, y, width, height, color):
        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height
        self.mColor = color

    def draw(self, surface):
        rect = pygame.Rect(int(self.mX), int(self.mY), int(self.mWidth), int(self.mHeight))
        pygame.draw.ellipse(surface, self.mColor, rect, 0)