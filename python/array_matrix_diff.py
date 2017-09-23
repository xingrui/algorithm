#narray can be 1,2,3,4,...,N dimension(s)
#matrix only can be 2 dimensions including not final reduce functions, eg : sum, avg
from numpy import *

def testSquare():
    print 'testSquare begin.'
    testArr = array([[1,1],[1,1]])
    testMat = mat(testArr)
    # ** 2 will not always use element square.
    assert (testArr ** 2 == testArr).all()
    assert (testMat ** 2 != testMat).all()
    assert (testMat ** 2 == 2 * testMat).all()
    # square will always use element square.
    assert (square(testArr) == testArr).all()
    assert (square(testMat) == testMat).all()
    # power 2 will always use element square.
    assert (power(testArr,2) == testArr).all()
    assert (power(testMat,2) == testMat).all()
    print 'testSquare passed.'

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

def testMatOp():
    print '\n******\ntestMatOp'
    testArr = array([[1,100],[1,200],[2,100],[2,200]])
    testMat = mat(testArr)
    print testMat
    print testMat[:,1]
    print testMat[:,1] > 150
    print nonzero(testMat[:,1] > 150)
    print type(nonzero(testMat[:,1] > 150))
    print type(nonzero(testMat[:,1] > 150)[0])
    print nonzero(testMat[:,1] > 150)[0]
    print type(testMat[nonzero(testMat[:,1] > 150)[0],:])
    print testMat[nonzero(testMat[:,1] > 150)[0],:].shape

def testArrOp():
    print '\n******\ntestArrOp'
    testArr = array([[1,100],[1,200],[2,100],[2,200]])
    print testArr
    print testArr[:,1]
    print testArr[:,1] > 150
    print nonzero(testArr[:,1] > 150)
    print nonzero(testArr[:,1] > 150)[0]
    print type(nonzero(testArr[:,1] > 150))
    print type(nonzero(testArr[:,1] > 150)[0])
    print testArr[nonzero(testArr[:,1] > 150)[0],:]

def testNonZero():
    print '\n******\ntestNonZeros'
    testArr = array([[1,100],[1,200],[2,100],[2,200]])
    testMat = mat(testArr)
    print nonzero(testMat[:,1])
    print testMat[nonzero(testMat[:,1])]
    print testMat[mat([[0],[1]]),mat([[0],[1]])]
    print testMat[mat([[1,2],[1,2]])]
    print testMat[nonzero(testMat[:,1])].shape
    print testMat[nonzero(testMat.A[:,1])[0]].shape
    print testMat[nonzero(testMat[:,1])[0]].T.shape
    print nonzero(testArr)
    print testArr[nonzero(testArr)]
    print testArr[nonzero(testArr)].shape

def main():
    testSquare()
    testMatOp()
    testArrOp()
    testNonZero()
    testMultiply()
    testShape()
    testSet()

if __name__ == "__main__":
    main()
