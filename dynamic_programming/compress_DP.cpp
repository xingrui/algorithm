//============================================================================
// Name        : compress_DP.cpp
// Author      : xingrui
// Version     :
// Copyright   : GPL
// Description : 状态压缩DP程序的演示程序
// 在 n*n(n≤20)的方格棋盘上放置n 个车(可以攻击所在行、列)，求使它们不能互相攻击的方案总数。
//============================================================================

//============================================================================
// 这个题目之所以是作为引例而不是例题，是因为它实在是个非常简单的组合学问题：我们一行一行放置，
// 则第一行有n 种选择，第二行n-1，……，最后一行只有 1 种选择，根据乘法原理，答案就是n! 。
// 这里既然以它作为状态压缩的引例，当然不会是为了介绍组合数学。
// 我们下面来看另外一种解法：状态压缩递推(States Compressing Recursion,SCR)。
// 我们仍然一行一行放置。取棋子的放置情况作为状态，某一列如果已经放置棋子则为1，否则为0.
// 这样一个状态就可以用一个最多20位的二进制数表示。
// 例如n=5，第1、3、4列已经放置，则这个状态可以表示为01101（从右到左）。
// 设f[s]为达到状态s的方案数，则可以尝试建立f的递推关系
// 考虑n=5，s=01101，这个状态是怎么得到的呢？
// 因为我们是一行一行放置的，所以当达到s时已经放到了第三行。
// 又因为一行能且仅能放置一个车，所以我们知道状态s一定来自：
// ①前两行在第 3、4  列放置了棋子(不考虑顺序，下同)，第三行在第 1 列放置；
// ②前两行在第 1、4 列放置了棋子，第三行在第3 列放置；
// ③前两行在第 1、3 列放置了棋子，第三行在第4 列放置。
// 这三种情况互不相交，且只可能有这三种情况。
// 根据加法原理，f[s]应该等于这三种情况的和。写成递推式就是：
// f[01101]=f[01100]+f[01001]+f[00101]
// 根据上面的讨论思路推广之，得到题目的解决办法
// f[0]=1
// f[s]=∑f[s^2i]
// 其中s∈[0…01,1…11]，s的右起第i+1位为1。 
// 反思这个算法，其正确性毋庸置疑(可以和n!对比验证)。
// 但是算法的时间复杂度为O(n2^n )，空间复杂度O(2^n )，是个指数级的算法，比循环计算n!差了好多。
// 它有什么优势？较大的推广空间。(
//============================================================================

#include<stdio.h>
#include<string.h>
const int MAXN = 1 << 20;
__int64 DP_space[MAXN + 23];
int main() {
	int nInputNum;
	while (scanf("%d", &nInputNum) != EOF) {
		if (nInputNum< 1 || nInputNum > 20)break;

		memset(DP_space , 0, sizeof(DP_space));
		int nIterator, space_size = (1 << nInputNum) - 1;
		DP_space[0] = 1;
		for (nIterator = 1; nIterator <= space_size; nIterator ++) {
			int nBitIterator = nIterator , first_not_zero_bit;
			while (nBitIterator != 0) {
				// 从右往左找到第一个不是0的bit位
				first_not_zero_bit = nBitIterator&(-nBitIterator);
				// 加上对应的bit位为0的数字
				DP_space[nIterator] += DP_space[nIterator ^ first_not_zero_bit];
				// 清楚掉对应的bit位，继续向左遍历
				nBitIterator ^= first_not_zero_bit;
			}
		}
		printf("%I64d\n", DP_space[space_size]);
		fflush(stdout);
	}
	return 0;
}
// 附加一份数1的个数的代码
int count(int v) {
	int num = 0;

	while (v) {
		// 清除掉最右边的1 不能用在上面的例子中是因为上面的例子要的是清除掉某一位上的1
		// 看来还是基础知识不过关啊，虽然想到了这个例子，却没有注意到它们之间的区别
		v &= (v - 1);
		++num;
	}

	return num;
}
