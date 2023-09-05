'''
Write a recursive function that draws the scale marks of a vertical ruler using dash “-” symbol. 
The middle mark should be the longest and mark the 1⁄2 way point, 
slightly shorter marks should mark the 1⁄4 way points, even slightly shorter marks should mark the 1⁄8 way points and so on. 
The function should take one argument: the height of the middle scale mark (i.e. the number of dashes). Example:

ruler(1)    ruler(2)    ruler(3)
  -           -           -
              --          --
              -           -
                          ---
                          -
                          --
                          -

'''

def ruler(n):
    if n == 1: # base case
        print("-")
    else:
        ruler(n - 1)   # Top part
        print("-" * n) # print - for n times
        ruler(n - 1)   # Bottom part


# Test cases
ruler(1)
print()
ruler(2)
print()
ruler(3)
print()
ruler(4)
print()
ruler(5)