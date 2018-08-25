import turtle

def drawashape(color, sides, distance,):

    turtle.speed(0)
    turtle.pencolor(color)
    angle = 360 / sides
    

    for i in range(450):
        
        turtle.forward(distance)
        turtle.left(angle + 1)
        distance = distance + 1
    
    
drawashape("green", 6, 25)
