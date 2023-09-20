'''
Consider an insect in an M by N grid. 
The insect starts at the bottom left corner, (1, 1), 
and wants to end up at the top right corner, (M, N). 
The insect is only capable of moving right or up. 
Write a recursive function in ${\color{yellow}path.py}$ 
that takes a grid length and width and returns 
the number of different paths the insect can take 
from the start to the goal.
'''

memo = {}


def paths(m, n):
    """Return the number of paths from one corner of an
    M by N grid to the opposite corner.

    >>> paths(2, 2)
    2
    >>> paths(5, 7)
    210
    >>> paths(117, 1)
    1
    >>> paths(1, 157)
    1
    """
    "*** YOUR CODE HERE ***"
    if (m, n) in memo:
        return memo[(m, n)]
    if m == 1 or n == 1:
        return 1
    memo[(m, n)] = paths(m-1, n) + paths(m, n-1)
    return memo[(m, n)]


print("paths(2, 2) = " + str(paths(2, 2)))
print("paths(5, 7) = " + str(paths(5, 7)))
print("paths(117, 1) = " + str(paths(117, 1)))
print("paths(1, 157) = " + str(paths(1, 157)))
