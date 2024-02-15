'''
Write a recursive function in ${\color{yellow}double_eights.py}$ that takes in a number n and determines if the digits contain two adjacent 8s. You can assume that n is at least a two-digit number.

'''


def double_eights(n):
    """ Returns whether or not n has two digits in row that
    are the number 8. Assume n has at least two digits in it.

    >>> double_eights(1288)
    True
    >>> double_eights(880)
    True
    >>> double_eights(538835)
    True
    >>> double_eights(284682)
    False
    >>> double_eights(588138)
    True
    >>> double_eights(78)
    False

    """
    "*** YOUR CODE HERE ***"
    if n < 10:
        return False
    if n % 100 == 88:
        return True
    return double_eights(n // 10)


print("double_eights(1288) = " + str(double_eights(1288)))
print("double_eights(880) = " + str(double_eights(880)))
print("double_eights(538835) = " + str(double_eights(538835)))
print("double_eights(284682) = " + str(double_eights(284682)))
print("double_eights(588138) = " + str(double_eights(588138)))
print("double_eights(78) = " + str(double_eights(78)))
