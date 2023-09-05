'''
that accepts an integer argument and prints out a Pascal triangle of depth n. For example, a call to:

pascal(3) will output:
1
1 1
1 2 1

pascal(5) will output:
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1

'''

# For computing the nth line of the triangle
def pascal_line(line):
    if line == 1: # base case line 1
        return [1]
    elif line == 2: # base case line 2
        return [1, 1]
    else:
        prev_line = pascal_line(line - 1)
        result = [1]
        for i in range(len(prev_line) - 1):
            result.append(prev_line[i] + prev_line[i + 1]) # add the two numbers above
        result.append(1)
        return result

# For printing the triangle
def pascal(depth):
    for i in range(1, depth + 1):
        line = pascal_line(i)
        for j in range(len(line)):
            if j > 0:
                print(" ", end=" ")
            print(line[j], end="")
        print()


# Test cases
pascal(1)
print()
pascal(2)
print()
pascal(3)
print()
pascal(5)
print()
pascal(6)
