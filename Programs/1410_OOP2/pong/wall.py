import pygame
import time
import random

class Wall:
    def __init__(self, x, y, width, height):
        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height

    def getX(self):
        return self.mX

    def getY(self):
        return self.mY

    def getWidth(self):
        return self.mWidth

    def getHeight(self):
        return self.mHeight

    def getRightX(self):
        return self.mX + self.mWidth

    def getBottomY(self):
        return self.mY + self.mHeight

    def draw(self, surface):
        rect = pygame.Rect(int(self.mX), int(self.mY), int(self.mWidth), int(self.mHeight))
        pygame.draw.rect(surface, (255, 255, 255), rect, 0)