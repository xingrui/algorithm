from numpy import *

a = array([[1,2,3],[4,5,6],[7,8,9]])
b = array([1,2,3])

print dot(a,b), dot(a,b).shape # b as (1,3) array
print dot(b,a), dot(b,a).shape # b as (3,1) array

a = mat(a)

print dot(a,b), dot(a,b).shape # b as (1,3) array
print dot(b,a), dot(b,a).shape # b as (3,1) array
