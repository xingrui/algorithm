# -*- coding:utf-8 -*-

import time
import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )

# 递归计算斐波那契数列 
def fib1(n):
  if n <= 1 :
    return 1
  else :
    return fib1(n - 1) + fib1(n - 2)

def fib2(n):
  a = 1
  b = 1
  c = 0
  for i in range(n - 1):
    c = a + b
    a = b
    b = c
  return c

# 计算 a, b (都是 2×2 的矩阵) 的乘积 
def mul(a, b):
  r = [[0, 0], [0, 0]]
  r[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
  r[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
  r[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
  r[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
  return r;

# 递归加速计算斐波那契数列 O(n^2) -> O(logn)
def fib(n):
  if n == 0:
    return [[1, 0], [0, 1]]
  if n == 1:
    return [[1, 1], [1, 0]]
  if n % 2 == 0 :
    return mul(fib(int(n / 2)), fib(int(n / 2)))
  else:
    return mul(mul(fib(int(n / 2)), fib(int(n / 2))), [[1, 1], [1, 0]])

if __name__ == '__main__':
  n = 10000000
  starttime = time.clock()
  res = fib2(n)  
  endtime = time.clock()
  print('direct', endtime - starttime)
  starttime = time.clock()
  res = fib(n)[0][0] 
  endtime = time.clock()
  print('accer:', endtime - starttime)
