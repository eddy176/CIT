import pygame
import time
import random
from text import Text

class ScoreBoard:
    def __init__(self, x, y, width, height):
        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height
        self.mLeftscore = 0
        self.mRightscore = 0
        self.mServeStatus = 1

    def getX(self):
        return self.mX

    def getY(self):
        return self.mY

    def getWidth(self):
        return self.mWidth

    def getHeight(self):
        return self.mHeight

    def getLeftScore(self):
        return self.mLeftscore

    def getRightScore(self):
        return self.mRightscore

    def getServeStatus(self):
        return self.mServeStatus

    def isGameOver(self):
        if self.mServeStatus == 3:
            return True
        elif self.mServeStatus == 4:
            return True
        else:
            return False

    def scoreLeft(self):
        if self.isGameOver() == False:
            if self.mLeftscore < 9:
                self.mLeftscore += 1
            if self.mLeftscore == 9:
                self.mServeStatus = 3

    def scoreRight(self):
        if self.isGameOver() == False:
            if self.mRightscore < 9:
                self.mRightscore += 1
            if self.mRightscore == 9:
                self.mServeStatus = 4

    def swapServe(self):
        if self.isGameOver() == False:
            if self.mServeStatus == 1:
                self.mServeStatus = 2
            elif self.mServeStatus == 2:
                self.mServeStatus = 1

    def draw(self, surface):
        rect = pygame.Rect(int(self.mX), int(self.mY), int(self.mWidth), int(self.mHeight))
        pygame.draw.rect(surface, (255, 255, 255), rect, 0)
        LeftscoreText = Text("L:" + str(self.mLeftscore), self.mX + 20, self.mY + 10)
        RightscoreText = Text("R:" + str(self.mRightscore), self.mX + 20, self.mY + 30)
        LeftscoreText.draw(surface)
        RightscoreText.draw(surface)