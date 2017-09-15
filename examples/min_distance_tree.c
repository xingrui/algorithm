#include <iostream>

using namespace std;

struct NODE
{
	NODE *pLeft;
	NODE *pRight;
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
