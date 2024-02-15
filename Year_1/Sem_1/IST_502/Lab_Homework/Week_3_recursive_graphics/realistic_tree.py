'''
Write a Python code in ${\color{yellow}realistic_tree.py}$ that generates a tree image similar 
to the one shown below. Note that the branches get smaller as they are closer to the leaves.
And, all leaves are green whereas all branches are brown.
'''
import turtle

colors = ['brown', 'green']


def tree_draw(level, size):
    if level == 1:
        turtle.color(colors[1])
        turtle.pensize(5)
        turtle.forward(size)
        turtle.forward(-1*size)
        turtle.color(colors[0])
        return
    turtle.pensize(20*size/100)
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
turtle.pensize(20)
turtle.color(colors[0])
tree_draw(9, 100)

turtle.done()
