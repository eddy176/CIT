from graphics import *
import random
import math

import itertools


def createRandomCities(n, screen_x, screen_y):
    points = []
    for i in range(n):
        x = random.randrange(0, screen_x)
        y = random.randrange(0, screen_y)
        p = [x,y]
        points.append(p)
    return points


def findDistancesBetweenCities(points):
    # n * n array initialized to 0
    n = len(points)
    d = []
    for i in range(n):
        inner = [0] * n
        d.append(inner)
    # set n * n values to be correct distances
    for i in range(n):
        for j in range(n):
            xdist = points[i][0] - points[j][0]
            ydist = points[i][0] - points[j][0]
            d[i][j] = math.sqrt(xdist * xdist + ydist * ydist)
    return d


def measurePathCost(fullPath, d):
    pathCost = 0
    for x in range(len(fullPath) -1):
        i = fullPath[x]
        j = fullPath[x + 1]
        pathCost += d[i][j]
    return pathCost


def findSolution_factorialAlgorithm(d):
    bestPath = None
    bestCost = 1000000
    n = len(d)
    citiesExceptZero = []
    for i in range(1, n):
        citiesExceptZero.append(i)
    for path in itertools.permutations(citiesExceptZero):
        fullPath = [0] + list(path) + [0]
        currentCost = measurePathCost(fullPath, d)
        if currentCost < bestCost:
            bestCost = currentCost
            bestPath = fullPath
    return bestPath, bestCost


def DrawCities(win, points):
    for i in range(len(points)):
        p = Point(points[i][0], points[i][1])
        c = Circle(p, 10)
        if i == 0:
            c.setFill('lightblue')
        else:
            c.setFill('pink')
        c.draw(win)
        t = Text(p, str(i))
        t.draw(win)

def main():
    n = 10
    screen_x = 1200
    screen_y = 900
    points = createRandomCities(n, screen_x, screen_y)
    d = findDistancesBetweenCities(points)

    #d[i][j]

    bestPath, bestCost = findSolution_factorialAlgorithm(d)
    print('Best path is', bestPath, '.')
    print('Best cost is', bestCost, '.')


    win = GraphWin("traveling salesman cities and route ", screen_x, screen_y)

    ###Draw every city:
    DrawCities(win, points)

main()
