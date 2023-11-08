# Have a 1 square in the middle of the screen and 4 squares in the corners

import turtle
# Draw a square


def draw_square(t, size, x, y):
    s = size // 2
    t.fillcolor('lightgray')
    t.pencolor('black')
    t.begin_fill()
    t.penup()
    t.goto(x-s, y-s)
    t.pendown()

    for _ in range(4):
        t.forward(size)
        t.left(90)
    t.end_fill()

# Draw a fractal square


def draw_fractal_square(t, size, x, y, depth):
    # Base case
    if depth == 0:
        return

    # Calculate the size of the squares in the corners
    ss = size // 2.2

    # Draw the center square
    draw_square(t, size, x, y)

    # Draw the 4 squares in the corners
    draw_fractal_square(t, ss, x-size/2, y-size/2, depth - 1)
    draw_fractal_square(t, ss, x-size/2, y+size/2, depth - 1)
    draw_fractal_square(t, ss, x+size/2, y+size/2, depth - 1)
    draw_fractal_square(t, ss, x+size/2, y-size/2, depth - 1)


# Set up the turtle
turtle.screensize(canvwidth=200, canvheight=200, bg="white")
turtle.speed(0)
turtle.setheading(0)
turtle.hideturtle()

# Initial size and the smallest size for the squares
initial_size = 200
draw_fractal_square(turtle, initial_size, 0, 0, 4)

turtle.done()
