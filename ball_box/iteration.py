# -*- coding:utf-8 -*-

import time
import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )

def get_identity(n):
  identity = []
  for i in range(n):
    array = [0] * n
    array[i] = 1
    identity.append(array)
  return identity
  
def get_matrix(c_array):
  matrix = []
  matrix.append(c_array)
  c_len = len(c_array)
  for i in range(1, c_len):
    array = [0] * c_len
    array[i - 1] = 1
    matrix.append(array)
  return matrix

# 计算 a, b (都是 2×2 的矩阵) 的乘积 
def mul(a, b):
  n = len(a)
  r = []
  for i in range(n):
    r.append([0] * n)
  for i in range(n):
    for j in range(n):
	  for k in range(n):
	    r[i][j] += a[i][k] * b[k][j]
  print r
  return r;

# 递归加速计算斐波那契数列 O(n^2) -> O(logn)
def fib(n, matrix, identity):
  #print identity
  if n == 0:
    return identity
  if n == 1:
    return matrix
  tmp_val = fib(int(n/2), matrix, identity)
  tmp_res = mul(tmp_val, tmp_val)
  if n % 2 == 0 :
    return tmp_res
  else:
    return mul(tmp_res, matrix)

if __name__ == '__main__':
  n = 20
  c_array = [1, 1]
  c_len = len(c_array)
  identity = get_identity(c_len)
  matrix = get_matrix(c_array)
  for i in range(n):
    res = fib(i, matrix, identity)[0][0]
    print res