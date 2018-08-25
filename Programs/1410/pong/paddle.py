import pygame
import time
import random

class Paddle:
    def __init__(self, x, y, width, height, speed, min_y, max_y):

        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height
        self.mSpeed = speed
        self.mMinY = min_y
        self.mMaxY = max_y

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

    def getSpeed(self):
        return self.mSpeed

    def getMinY(self):
        return self.mMinY

    def getMaxY(self):
        return self.mMaxY

    def setPosition(self, y):
        # if new y position causes top of paddle to go out of range, don't make changes, update mY
        if y + self.mHeight <= self.mMaxY and y >= self.mMinY:
            self.mY = y

    def moveUp(self, dt):
        # if movement out of range, stop at top, update y of paddle based on dt and speed
        newY = self.mY - (self.mSpeed * dt)
        if newY <= self.mMinY:
            self.setPosition(self.mMinY)
        else:
            self.setPosition(newY)

    def moveDown(self, dt):
        newY = self.mY + (self.mSpeed * dt)
        if newY >= self.mMaxY - self.mHeight:
            self.setPosition(self.mMaxY - self.mHeight)
        else:
            self.setPosition(newY)

    def draw(self, surface):
        rect = pygame.Rect(int(self.mX), int(self.mY), int(self.mWidth), int(self.mHeight))
        pygame.draw.rect(surface, (0, 0, 255), rect, 0)