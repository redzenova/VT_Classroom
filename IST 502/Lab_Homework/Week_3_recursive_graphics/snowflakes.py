'''
Write a Python code in snowflakes.py that generates an image similar to the one shown below.
'''

import turtle
from math import sqrt


def snowflake(order, size):
    if order == 1:
        for i in range(6):
            turtle.forward(size)
            turtle.forward(size * -1)  # Backward
            turtle.left(60)
        return

    # Draw the hexagon
    for i in range(6):
        turtle.forward(size)
        turtle.forward(size * -1)
        turtle.left(60)

    for i in range(6):
        turtle.forward(size * 0.85)
        snowflake(order - 1, size * 0.35)
        turtle.forward(size * 0.85 * -1)
        turtle.left(60)


# set speed to fastest
turtle.speed(0)
turtle.setheading(0)
turtle.penup()
turtle.goto(0, 0)
turtle.pendown()
turtle.color('orange')
snowflake(4, 150)

turtle.done()
