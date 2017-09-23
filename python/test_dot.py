from numpy import *

a = array([[1,2,3],[4,5,6],[7,8,9]])
b = array([1,2,3])
assert (outer(b,b) == multiply(b[:,newaxis],b[newaxis,:])).all()
assert (outer(b,b) == dot(b[:,newaxis],b[newaxis,:])).all()
assert (outer(b,b) == multiply(reshape(b,(-1,1)),reshape(b,(1,-1)))).all()
assert (outer(b,b) == dot(reshape(b,(-1,1)),reshape(b,(1,-1)))).all()

c = array([[1,2],[4,5],[7,8]])
d = c.copy()
assert (c==d).all()

assert dot(a,b).shape == (3,)
assert dot(b,a).shape == (3,)

array_dot = dot(array([[1,2,3],[4,5,6],[7,8,9]]), array([1,2,3]))
mat_dot = mat([[1,2,3],[4,5,6],[7,8,9]]) * mat([[1],[2],[3]])
assert (array_dot[:,newaxis] == mat_dot).all()

a = mat(a)

assert dot(a,b).shape == (1,3)# b as (1,3) array
assert dot(b,a).shape == (1,3)# b as (1,3) array

print 'Test Passed.'
