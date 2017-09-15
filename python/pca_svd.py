#http://blog.csdn.net/dark_scope/article/details/53150883
from numpy import *

def pca_01(X):
    covMat = cov(X, rowvar=0)
    eigVal, eigVec = linalg.eig(covMat)
    return eigVal, eigVec

def pca_02(X):
    mean_ = mean(X, axis=0)
    X = X - mean_
    covMat = cov(X, rowvar=0)
    eigVal, eigVec = linalg.eig(covMat)
    return eigVal, eigVec

def pca_03(X):
    mean_ = mean(X, axis=0)
    X = X - mean_
    M,N = X.shape
    Sigma = dot(X.T, X)/(M-1)
    eigVal, eigVec = linalg.eig(Sigma)
    return eigVal, eigVec

def pca_04(X):
    mean_ = mean(X, axis=0)
    X = X - mean_
    M,N = X.shape
    Sigma = dot(X.T,X)
    U,S,V = linalg.svd(Sigma)
    return U,S,V

def pca_05(X):
    mean_ = mean(X, axis=0)
    X = X - mean_
    U,S,V = linalg.svd(X)
    return U,S,V

def main():
    X=mat([[1,4],[9,10],[10,20]])
    print pca_01(X)
    print pca_02(X)
    print pca_03(X)
    Y=mat([[1,4],[9,10],[10,20]])
    U1,S1,V1 = pca_04(Y)
    print S1, V1
    U2,S2,V2 = pca_05(Y)
    print S2, V2
    print multiply(S2, S2) - S1 #should be zero

if __name__ == "__main__":
     main()
