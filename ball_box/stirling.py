
def get_num(n, m):
    if n > 20 or m > 10:
        return 0
    a = [0] * m
    a[0] = 1
    a[1] = 1
    for i in range(1, n - 1):
        if i < m:
            a[i] = 1
        for j in range(m - 1, 0, -1):
            a[j] = a[j-1] + (j + 1) * a[j]
    return a[m - 1]

if __name__ == "__main__":
    n = 8
    m = 3
    print(get_num(n, m))
