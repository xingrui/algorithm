def get_value(coefficient, current):
    res = 0
    for i in range(0, len(coefficient)):
        res += coefficient[i] * current[i]
    return res

def calculate(coefficient, init, n):
    if n < 0:
        return 1
    arr_len = len(coefficient)
    if arr_len != len(init):
        return 1
    if n < arr_len:
        return init[n]
    current = init
    next_val = 0
    coefficient = coefficient[::-1]
    for i in xrange(arr_len):
        print i, init[i]
    for i in xrange(arr_len, n + 1):
        next_val = get_value(coefficient, current)
        print i, next_val
        current = current[1:]
        current.append(next_val)
    return next_val

if __name__ == "__main__":
    coefficient = [4,3,2,1]
    init = [1,1,1,1]
    init = [1,2,3,4]
    n = 20
    res = calculate(coefficient, init, n)
    print res
