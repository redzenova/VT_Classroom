import turtle


def sierpinski_draw(order, size):
    if order == 1:
        for i in range(3):
            turtle.forward(size)
            turtle.left(120)
        return
    sierpinski_draw(order-1, 0.5*size)
    turtle.forward(0.5*size)
    sierpinski_draw(order-1, 0.5*size)
    turtle.left(120)
    turtle.forward(0.5*size)
    turtle.right(120)
    sierpinski_draw(order-1, 0.5*size)
    turtle.right(120)
    turtle.forward(0.5*size)
    turtle.left(120)


# set speed to fastest
turtle.speed(1)
turtle.setheading(0)
turtle.penup()
turtle.goto(-300, -300)
turtle.pendown()
turtle.color('green')
sierpinski_draw(2, 600)

turtle.done()
