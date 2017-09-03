#narray can be 1,2,3,4,...,N dimension(s)
#matrix only can be 2 dimensions including not final reduce functions, eg : sum, avg
from numpy import *

def testMultiply():
    testArr = array([[4,3], [2,1]])
    testMat = mat(testArr)
    print testMat, type(testMat)
    print testArr, type(testArr)
    print testMat*testMat
    print testArr*testArr
    print dot(testArr, testArr)
    print testMat**2
    print testArr**2

def testShape():
    testArr = array([[1,2],[2,5]])
    testMat = mat(testArr)
    meanArr = testArr.mean(1)
    meanMat = testMat.mean(1)
    print meanArr.shape, meanMat.shape
    print testArr - meanArr
    print testArr - meanArr[:,newaxis]
    print testMat - meanMat
    print testArr.sum(1)
    print testMat.sum(1)

if __name__ == "__main__":
    testMultiply()
    testShape()
