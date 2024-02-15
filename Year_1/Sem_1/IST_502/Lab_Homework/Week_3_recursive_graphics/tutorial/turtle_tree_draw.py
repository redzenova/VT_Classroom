import turtle


def tree_draw(level, size):
    if level == 1:
        turtle.forward(size)
        turtle.forward(-1*size)
        return
    turtle.forward(size)
    turtle.left(25)
    tree_draw(level - 1, size*0.65)
    turtle.right(25)
    turtle.right(35)
    tree_draw(level - 1, size*0.85)
    turtle.left(35)
    turtle.forward(-1*size)


# set speed to fastest
turtle.speed(0)
turtle.setheading(90)
turtle.pensize(5)
turtle.color('green')
tree_draw(6, 100)

turtle.done()
