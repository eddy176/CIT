import pygame
import time
import random

class Ball:
    def __init__(self, size, minX, maxX, minY, maxY, left_paddle_x, right_paddle_x):
    # Ball location
        self.mX = minX
        self.mY = minY
    # Ball Movement
        self.mDX = 0
        self.mDY = 0
    # Ball's maximum travel
        self.mMinX = minX
        self.mMinY = minY
        self.mMaxX = maxX
        self.mMaxY = maxY
    # left paddle
        self.mLeftPaddleMinY = minY
        self.mLeftPaddleMaxY = maxY
        self.mLeftPaddleX = left_paddle_x
    # right paddle
        self.mRightPaddleMinY = minY
        self.mRightPaddleMaxY = maxY
        self.mRightPaddleX = right_paddle_x
    # paddle y min and max
        self.mPmin = minY
        self.mPmax = maxY
    # Ball size
        self.mSize = size
        return

    def getX(self):
        return self.mX

    def getY(self):
        return self.mY

    def getSize(self):
        return self.mSize

    def getDX(self):
        return self.mDX

    def getDY(self):
        return self.mDY

    def getMinX(self):
        return self.mMinX

    def getMinY(self):
        return self.mMinY

    def getMaxX(self):
        return self.mMaxX

    def getMaxY(self):
        return self.mMaxY

#left paddle
    def getLeftPaddleX(self):
        return self.mLeftPaddleX

    def getLeftPaddleMinY(self):
        return self.mLeftPaddleMinY

    def getLeftPaddleMaxY(self):
        return self.mLeftPaddleMaxY

#right paddle
    def getRightPaddleX(self):
        return self.mRightPaddleX

    def getRightPaddleMinY(self):
        return self.mRightPaddleMinY

    def getRightPaddleMaxY(self):
        return self.mRightPaddleMaxY

#position of ball
    def setPosition(self, x, y):
        minX = self.mMinX
        minY = self.mMinY
        maxX = self.mMaxX
        maxY = self.mMaxY
        size = self.mSize
        if x >= minX and x <= maxX - size and y >= minY and y <= maxY - size:
            self.mX = x
            self.mY = y
# speed of ball
    def setSpeed(self, dX, dY):
        self.mDX = dX
        self.mDY = dY
# left paddle Y
    def setLeftPaddleY(self, paddle_min_y, paddle_max_y):
        if paddle_min_y > paddle_max_y:
            paddle_max_y, paddle_min_y = paddle_min_y, paddle_max_y
        if paddle_min_y >= self.mMinY and paddle_max_y <= self.mMaxY:
            self.mLeftPaddleMinY = paddle_min_y
            self.mLeftPaddleMaxY = paddle_max_y

# right paddle Y
    def setRightPaddleY(self, paddle_min_y, paddle_max_y):
        if paddle_min_y > paddle_max_y:
            paddle_max_y, paddle_min_y = paddle_min_y, paddle_max_y
        if paddle_min_y >= self.mMinY and paddle_max_y <= self.mMaxY:
            self.mRightPaddleMinY = paddle_min_y
            self.mRightPaddleMaxY = paddle_max_y

# check boundary
    def checkTop(self, new_y):
        if new_y <= self.mMinY and self.mDY < 0:
            self.mDY = -self.mDY
            new_y = self.mMinY + (self.mMinY - new_y)
        return new_y

    def checkBottom(self, new_y):
        if new_y + self.mSize >= self.mMaxY:
            self.mDY = - self.mDY
            new_y = self.mMaxY + (self.mMaxY - new_y) - 2 * self.mSize
        return new_y

    def checkLeft(self, new_x):
        if new_x <= self.mMinX and self.mDX < 0:
            new_x = self.mMinX
            self.mDX = 0
            self.mDY = 0
        return new_x

    def checkRight(self, new_x):
        if new_x + self.mSize >= self.mMaxX:
            self.mDX = 0
            self.mDY = 0
            new_x = self.mMaxX - self.mSize
        return new_x

    def checkLeftPaddle(self, new_x, new_y):
        mid_y = (new_y + self.mY) / 2
        if mid_y >= self.mLeftPaddleMinY and mid_y <= self.mLeftPaddleMaxY and new_x <= self.mLeftPaddleX \
                and self.mX >= self.mLeftPaddleX:
            new_x = 2 * self.mLeftPaddleX - new_x
            self.mDX = -self.mDX
        return new_x

    def checkRightPaddle(self, new_x, new_y):
        mid_y = (new_y + self.mY) / 2
        if mid_y >= self.mRightPaddleMinY and mid_y <= self.mRightPaddleMaxY and new_x + self.mSize \
                >= self.mRightPaddleX and self.mX + self.mSize <= self.mRightPaddleX and self.mDX > 0:
            new_x = self.mRightPaddleX - self.mSize - (new_x - (self.mRightPaddleX - self.mSize))
            self.mDX = -self.mDX
        return new_x

    def move(self, dt):
        new_x = self.mX + self.mDX * dt
        new_y = self.mY + self.mDY * dt
        new_y = self.checkTop(new_y)
        new_y = self.checkBottom(new_y)
        new_x = self.checkLeft(new_x)
        new_x = self.checkRight(new_x)
        new_x = self.checkLeftPaddle(new_x, new_y)
        new_x = self.checkRightPaddle(new_x, new_y)
        self.mX = new_x
        self.mY = new_y

    def serveLeft(self, x, min_y, max_y, min_dx, max_dx, min_dy, max_dy):
        y = random.uniform(min_y,max_y)
        self.mX = x
        self.mY = y
        self.mDX = random.uniform(min_dx, max_dx)
        self.mDY = random.uniform(min_dy, max_dy)

    def serveRight(self, x, min_y, max_y, min_dx, max_dx, min_dy, max_dy):
        y = random.uniform(min_y,max_y)
        self.mX = x
        self.mY = y
        self.mDX = random.uniform(-min_dx, -max_dx)
        self.mDY = random.uniform(min_dy, max_dy)

    def draw(self, surface):
        rect = pygame.Rect(int(self.mX), int(self.mY), self.mSize, self.mSize)
        pygame.draw.rect(surface, (255,0,0), rect, 0)