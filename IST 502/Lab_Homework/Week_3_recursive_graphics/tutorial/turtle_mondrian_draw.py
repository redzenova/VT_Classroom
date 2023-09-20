import turtle
import random

colors = ['red', 'yellow', 'blue', 'black', 'white']


def rectangle_draw(width, height):
    turtle.color("black")
    turtle.fillcolor(colors[random.randint(0, 4)])
    turtle.begin_fill()
    for i in range(2):
        turtle.forward(width)
        turtle.left(90)
        turtle.forward(height)
        turtle.left(90)
    turtle.end_fill()


def mondrian_draw(level, width, height):
    if level == 1:
        rectangle_draw(width, height)
        return

    fraction = random.uniform(0.2, 0.8)
    if width >= height:
        mondrian_draw(level-1, fraction*width, height)
        turtle.forward(fraction*width)
        mondrian_draw(level-1, (1-fraction)*width, height)
        turtle.forward(-1*fraction*width)
    else:
        turtle.forward(width)
        turtle.left(90)
        mondrian_draw(level-1, fraction*height, width)
        turtle.forward(fraction*height)
        mondrian_draw(level-1, (1-fraction)*height, width)
        turtle.forward(-1*fraction*height)
        turtle.right(90)
        turtle.forward(-1*width)


# set speed to fastest
turtle.speed(0)
turtle.setheading(0)
turtle.pensize(5)
turtle.penup()
turtle.goto(-400, -300)
turtle.pendown()
mondrian_draw(7, 800, 600)

turtle.done()
