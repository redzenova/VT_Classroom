# This solution uses combinatorics to calculate the values of Pascal's triangle

def comb(n, r):
    if n == r:
        return 1
    if r == 0:
        return 1
    return comb(n-1, r-1) + comb(n-1, r)

def pascal(n):
    if n == 1:
        print(str(comb(0, 0)))
        return
    pascal(n-1)
    s = ""
    for i in range(n):
        s += str(comb(n-1, i)) + " "
    print(s)

pascal(5)