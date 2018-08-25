#classes needed:

#paddle
    # leftPaddleX
    # minY
    # maxY
    # if newX <= leftPaddleX and x >= leftPaddleX:
        # if midY >= leftPaddleMinY and midY <= leftPaddleMaxY:
            # newX = 2 * minX - newX

#ball
    #datamembers: x, y, dx, dy, size
        # dx and dy are speeds in the directions of x and y
        # x = pixels
        # dx = pixels/second
        # dt is len of time
        # newX = x + dx * dt
        # newY = y + dy * dt
        # x and y datamembers need to update to the new values determined by these problems
    # bounce off top wall
        # if newY <= minY and dy < 0:
            # newY = 2 * minY - newY
            # dY = -dY
    # bounce off bottom wall
        # if newY >= maxY and dY > 0:
            # newY = 2 *

    # touch right wall
        # if newX + size >= maxX and dX > 0:
                # size is the size of the ball
                # newY stays the same
            # newX = maxX - size
            # dX = 0
            # dy = 0
    # touch left wall
        # if newX <= minX and dX > 0:
            #newX = minX
            # dX = 0
            # dY = 0

#scoreboard

#wall
    #on each of the borders
    #right or left walls are score walls
    #each wall is a rectangle
    #minY is the minimum Y value on top which the ball bounces off of
    #maxY is maximum Y value on bottom which the ball bounces off of
    #minX is the minimum X value on the left which the ball sticks to, giving opposing player a point
    #maxX is the maximum X value on the right which the ball sticks to, giving opposing player a point
