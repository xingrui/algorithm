from numpy import *

def inner_test(dataMat, t):
    dataMat = dataMat.astype(t)
    try:
        vdot(dataMat[0], dataMat[1])
        return 0
    except ValueError,e:
        return 1

def test_vdots():
    dataMat = mat(ones((5,5)))
    type_list = ['int', 'int8', 'int16', 'int32', 'int64', 'float', 'float16', 'float32','float64','float128', 'complex', 'complex64', 'complex128', 'complex256']
    res_list = [[],[]]
    for t in type_list:
        ret = inner_test(dataMat, t)
        res_list[ret].append(t)
    print 'passed_list:', res_list[0]
    print 'except_list:', res_list[1]

if __name__ == "__main__":
    test_vdots()
