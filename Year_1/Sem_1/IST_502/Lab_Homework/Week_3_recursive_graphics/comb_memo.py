'''
Given the code to calculate n choose r combination below

def comb(n, r):
    if n == r:
        return 1
    if r == 0:
        return 1
    return comb(n-1, r-1) + comb(n-1, r)

print(comb(35, 11))

Hint: use Python’s dictionary as a memo and use Python’s tuple as keys in the memo dictionary
'''


memo = {}


def comb(n, r):
    if (n, r) in memo:
        return memo[(n, r)]
    if n == r:
        return 1
    if r == 0:
        return 1
    memo[(n, r)] = comb(n-1, r-1) + comb(n-1, r)
    return memo[(n, r)]


print("comb(35, 11) = " + str(comb(35, 11)))
print("comb(10, 5) = " + str(comb(10, 5)))
print("comb(5, 3) = " + str(comb(5, 3)))
