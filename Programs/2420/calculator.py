# calculator program
# 2420

from graphics import *
import math
#from stack import Stack

class Stack:

    def __init__(self):
        self.stack = []

    def push(self, p):
        self.stack.append(p)

    def pop(self):
        p = self.stack.pop()
        return p

    def top(self):
        return self.stack[len(self.stack) - 1]

    def isEmpty(self):
        if len(self.stack) == 0:
            return True
        else:
            return False


def formatMenu():
    print('Welcome to the graphing calculator!')
    print('')
    expression = input('Please input your expression with number 0-9 and operators +-/*. ')
    while len(expression) < 3:
        print('Sorry, please input the correct format. ')
        expression = input('Please input your expression with number 0-9 and operators +-/*. ')
    return expression


def inFixToPostFix(expression):
    postFix = ''
    s = Stack()
    for c in expression:
        if c in '0123456789x':
            postFix += c
        elif c in '+-':
            while not s.isEmpty() and s.top() in '+-*/':
                postFix += s.pop()
            s.push(c)
        elif c in '*/':
            while not s.isEmpty() and s.top() in '*/':
                postFix += s.pop()
            s.push(c)
        elif c in '(':
            s.push(c)
        elif c in ')':
            while s.top() != '(':
                postFix += s.pop()
            s.pop()
    while not s.isEmpty():
        postFix += s.pop()
    return postFix


def evaluatePostFix(postFix, x):
    s = Stack()
    for c in postFix:
        if c in '0123456789':
            s.push(c)
        elif c in 'x':
            s.push(float(x))
        elif c in '+-*/':
            rhs = float(s.pop())
            lhs = float(s.pop())
            if c == '+':
                lhs += rhs
                s.push(lhs)
            elif c == '-':
                lhs -= rhs
                s.push(lhs)
            elif c == '/':
                lhs /= rhs
                s.push(lhs)
            elif c == '*':
                lhs *= rhs
                s.push(lhs)
    total = s.pop()
    return total
# This program draws user entered functions onto a graphics window
# By the CS 2420 class
# February, 2018


def main():
    expression = formatMenu()
    postfix = inFixToPostFix(expression)
    win = GraphWin("My Circle", 500, 500)
    XLOW = -10.0
    XHIGH = +10.0
    YLOW = -10.0
    YHIGH = +10.0
    win.setCoords(XLOW, YLOW, XHIGH, YHIGH)

    # Store the curve points in xpoints and ypoints
    xpoints = []
    ypoints = []
    x = -10.0
    while x < 11:
        y = evaluatePostFix(postfix, x)
        xpoints.append(x)
        ypoints.append(y)
        x += .1

    # Draw the curve
    for i in range(len(xpoints) - 1):
        p1 = Point(xpoints[i], ypoints[i])
        p2 = Point(xpoints[i + 1], ypoints[i + 1])
        line = Line(p1, p2)
        line.setOutline("blue")
        line.setWidth(3)
        line.draw(win)

    # Draw Axes
    line = Line(Point(XLOW, (YLOW + YHIGH) // 2), Point(XHIGH, (YLOW + YHIGH) // 2))
    line.setOutline("red")
    line.draw(win)
    line = Line(Point((XLOW + XHIGH) // 2, YLOW), Point((XLOW + XHIGH) // 2, YHIGH))
    line.setOutline("red")
    line.draw(win)

    win.getMouse()  # Pause to view result
    win.close()  # Close window when done


main()
