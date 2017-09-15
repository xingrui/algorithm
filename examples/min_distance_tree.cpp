#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::max;

struct NODE
{
	NODE *pLeft;
	NODE *pRight;
    NODE():pLeft(NULL), pRight(NULL) {}
};

struct RESULT
{
	int nMaxDistance;
	int nMaxDepth;
};

RESULT GetMaximumDistance(NODE* root)
{
	if (!root)
	{
		RESULT empty = { 0, -1 };	// trick: nMaxDepth is -1 and then caller will plus 1 to balance it as zero.
		return empty;
	}

	RESULT lhs = GetMaximumDistance(root->pLeft);
	RESULT rhs = GetMaximumDistance(root->pRight);

	RESULT result;
	result.nMaxDepth = max(lhs.nMaxDepth + 1, rhs.nMaxDepth + 1);
	result.nMaxDistance = max(max(lhs.nMaxDistance, rhs.nMaxDistance), lhs.nMaxDepth + rhs.nMaxDepth + 2);
	return result;
}

int main() {
    NODE* root = new NODE;
    root->pLeft = new NODE;
    root->pLeft->pLeft = new NODE;
    root->pLeft->pRight = new NODE;
    root->pLeft->pRight->pLeft = new NODE;
    root->pRight = new NODE;
    root->pRight->pLeft = new NODE;
    root->pRight->pRight = new NODE;
    root->pRight->pRight->pLeft = new NODE;
    RESULT res = GetMaximumDistance(root);
    std::cout << res.nMaxDistance << std::endl;
}
