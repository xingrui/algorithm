
def get_num(n, m):
    if n < 1 or m < 1:
        return 0
    if n == 1 or m == 1:
        return 1
    if n < m:
        return get_num(n, n)
    if n == m:
        return 1 + get_num(n, n - 1)
    return get_num(n - m, m) + get_num(n, m - 1)

if __name__ == "__main__":
    n = 200
    for i in range(1, n):
        print("%d : %d" % (i, get_num(i, i)))
