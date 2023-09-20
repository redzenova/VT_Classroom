def hanoi(N, left, middle, right):
    if N == 0:
        return
    hanoi(N-1, left, right, middle)
    print("Move disc", N, "from", left, "to", right)
    hanoi(N-1, middle, left, right)

hanoi(3, "left", "middle", "right")