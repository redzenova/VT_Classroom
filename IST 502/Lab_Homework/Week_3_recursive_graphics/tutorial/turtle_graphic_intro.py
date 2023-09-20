# learn about Python's Turtle graphics library through examples
# also see the document at https://docs.python.org/3/library/turtle.html
import turtle

# Set to slowest speed and east heading
# For fastest speed, use turtle.speed(0)
turtle.speed(1)
turtle.setheading(1)

# draw a green circle
turtle.penup()
turtle.color("green")
turtle.fillcolor("green")
turtle.goto(0, 0)
turtle.pendown()
turtle.begin_fill()
turtle.circle(100)
turtle.end_fill()

# draw a blue circle
turtle.penup()
turtle.color("blue")
turtle.goto(0, -200)
turtle.pendown()
turtle.circle(100, 360)

# draw a red square
turtle.penup()
turtle.color("red")
turtle.fillcolor("green")
turtle.goto(-200, 0)
turtle.pensize(5)
turtle.pendown()
turtle.begin_fill()
turtle.circle(100, 360, 4)
turtle.end_fill()

# draw many polygons
turtle.penup()
turtle.color("black")
turtle.fillcolor("yellow")
turtle.goto(-300, -200)
turtle.pensize(5)
turtle.pendown()
for sides in range(3, 7, 1):
    if sides == 3:
        turtle.begin_fill()
    for i in range(sides):
        turtle.forward(100)
        turtle.left(360/sides)
    if sides == 3:
        turtle.end_fill()

# draw brown rectangle no fill
turtle.penup()
turtle.color("brown")
turtle.goto(100, 0)
turtle.pensize(1)
turtle.pendown()
turtle.forward(100)
turtle.left(90)
turtle.forward(50)
turtle.left(90)
turtle.forward(100)
turtle.left(90)
turtle.forward(50)
turtle.left(90)

# draw magenta half-circle
turtle.penup()
turtle.color("magenta")
turtle.fillcolor("magenta")
turtle.goto(200, -200)
turtle.pendown()
turtle.begin_fill()
turtle.circle(100, 180)
turtle.end_fill()

# draw a random polygon
turtle.setheading(90)
turtle.penup()
turtle.goto(200, 100)
turtle.color("black")
turtle.fillcolor("magenta")
turtle.pensize(10)
turtle.pendown()
turtle.begin_fill()
turtle.forward(100)
turtle.left(20)
turtle.forward(30)
turtle.left(60)
turtle.forward(50)
turtle.goto(200, 100)
turtle.end_fill()
turtle.setheading(0)

# hold the window; close it by clicking the window close 'x' mark
turtle.done()
