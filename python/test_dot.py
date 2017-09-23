from numpy import *

a = array([[1,2,3],[4,5,6],[7,8,9]])
b = array([1,2,3])

print dot(a,b) # b as (1,3) array
print dot(b,a) # b as (3,1) array
