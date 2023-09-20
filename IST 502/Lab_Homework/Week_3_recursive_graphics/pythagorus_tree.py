'''
Write a Python code in pythagorus_tree.py
that generates an image similar to the one shown below.
'''

import turtle
from math import sqrt


def pythagorus_tree(order, size):
    if order == 1:
        for i in range(4):
            turtle.forward(size)
            turtle.right(90)
        return

    # Draw the square
    for i in range(4):
        turtle.forward(size)
        turtle.right(90)

    turtle.left(45)
    turtle.forward(size * sqrt(2)/2)
    turtle.right(90)
    turtle.forward(size * sqrt(2)/2)
    turtle.right(135)
    turtle.forward(size)
    turtle.right(180)
    turtle.left(135)
    turtle.forward(size * sqrt(2)/2)
    turtle.right(90)

    pythagorus_tree(order-1, size * sqrt(2)/2)

    turtle.forward(size * sqrt(2)/2)
    turtle.right(90)
    turtle.forward(size * sqrt(2)/2)
    turtle.left(90)
    turtle.forward(size * sqrt(2)/2)
    turtle.right(90)

    pythagorus_tree(order-1, size * sqrt(2)/2)
    turtle.right(90)
    turtle.forward(2 * size * sqrt(2)/2)
    turtle.left(135)


# set speed to fastest
turtle.speed(0)
turtle.setheading(0)
turtle.penup()
turtle.goto(0, 0)
turtle.pendown()
turtle.color('red')
pythagorus_tree(9, 100)

turtle.done()
