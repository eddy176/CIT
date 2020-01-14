import turtle

turtle.speed(0)

def coolshapes(color, fillin, distance, angle, locationx, locationy, loops):
    turtle.penup()
    turtle.setx(locationx)
    turtle.sety(locationy)
    turtle.pencolor(color)
    angle = angle
    
    turtle.pendown()
    turtle.fillcolor(fillin)
    turtle.begin_fill()

    for i in range(loops):

        turtle.forward(distance)
        turtle.right(angle)
        distance = distance
    
    turtle.end_fill()
    

coolshapes("red", "red", 50, 45, 100, 100, 8)

coolshapes("blue", "yellow", 100, 144, -100, -100, 5)

def coolspiral(color, distance, angle, locationx, locationy, loops):
    turtle.penup()
    turtle.setx(locationx)
    turtle.sety(locationy)
    turtle.pencolor(color)
    angle = angle

    turtle.pendown()
    distance = distance

    for i in range(loops):

        turtle.forward(distance)
        turtle.left(angle)
        angle += 1

coolspiral("purple", 7, 1, -100, 100, 40)

coolshapes("teal", "white", 50, 277, 100, -100, 13)
