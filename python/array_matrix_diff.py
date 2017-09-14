#narray can be 1,2,3,4,...,N dimension(s)
#matrix only can be 2 dimensions including not final reduce functions, eg : sum, avg
from numpy import *

def testMultiply():
    print '\n******\ntestMultiply'
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
    print '\n******\ntestShape'
    testArr = array([[1,2],[2,5]])
    testMat = mat(testArr)
    print testArr[0,:].shape
    print testMat[0,:].shape
    print testArr[0,:].T.shape
    print testMat[0,:].T.shape
    meanArr = testArr.mean(1)
    meanMat = testMat.mean(1)
    print meanArr.shape, meanMat.shape
    print testArr - meanArr
    print testArr - meanArr[:,newaxis]
    print testMat - meanMat
    print testArr.sum(1)
    print testMat.sum(1)
    print testArr.sum(1).T
    print testMat.sum(1).T

def testSet():
    print '\n******\ntestSet'
    testArr = array([[1,100],[1,200],[2,100],[2,200]])
    testMat = mat(testArr)
    print set((testMat[:, 0].T.tolist())[0])
    print set(testMat[:, 0])

if __name__ == "__main__":
    testMultiply()
    testShape()
    testSet()