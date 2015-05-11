import sys
def get_num(n, m):
    if n < 1 or m < 1:
        return 0
    if data[n][m] != 0:
        return data[n][m]
    res = 0
    if n == 1 or m == 1:
        res = 1
    elif n < m:
        res = get_num(n, n)
    elif n == m:
        res = 1 + get_num(n, n - 1)
    else:
        res = get_num(n - m, m) + get_num(n, m - 1)
    data[n][m] = res
    return res

def get_array(n, m):
    return [[0 for col in range(n)] for row in range(m)]

if __name__ == "__main__":
    n = 200
    n += 1
    data = get_array(n, n)
    for i in range(1, n):
        print("%d : %d" % (i, get_num(i, i)))
    print_len = 20
    for i in range(1, print_len):
        data_list = []
        for j in range(1, print_len):
            data_list.append("%d" % data[i][j])
        print '\t'.join(data_list)
