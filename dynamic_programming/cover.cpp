//============================================================================
// Name        : cover.cpp
// Author      : xingrui
// Version     :
// Copyright   : GPL
// Description : 多米诺骨牌完美覆盖总数求解问题
//             : 给出n*m(1 <= n,m <= 11)的方格棋盘，用1*2的长方形骨牌不重叠地覆盖这个棋盘
//             : 求覆盖满的方案数
//============================================================================

//============================================================================
// 算法思想 : 以行作为阶段, 每个阶段的状态是将该行填满后下一行的分布方式(这实在很难想到)
//============================================================================
// 算法介绍 : 显然，如果n和m都是奇数则无解，因此假设n，m至少有一个偶数，且m<=n(否则交换)
// 用sum[i][s]表示把前i-1行覆盖满、第i行覆盖状态为s的覆盖方案数。
// 因为在第i行上放置的骨牌最多也只能影响到第i-1行，则容易得到递推式：
// sum[0][1…11]=1 [TODO 全1如果表示全填满的话，如果是列数奇数怎么办？明显没有填写方法啊]
// 问题已经解决，是我理解错了，全填满是指假设的上面一行，因为这个循环进行了n次，而不是n-1次
// sum[i][pre_row_state]=∑sum[i-1][current_row_state]
// 其中(pre_row_state,current_row_state)整体作为一个放置方案，可以把所有方案 DFS 预处理出来
// 对于当前行每一个位置，我们有3 种放置方法：
// ①竖直覆盖，占据当前格和上一行同一列的格；
// ②水平覆盖，占据当前格和该行下一格；
// ③不放置骨牌，直接空格。
// 如何根据这些枚举出每个(pre_row_state,current_row_state)呢？
//============================================================================
#include<stdio.h>
#include<string.h>
#define MAX_N 1<<11 | 3
__int64 sum[2][MAX_N];
int row_num, column_num;
// 把结果存放在数组 sum[t][] 中 , pre_row_state , current_row_state 分别为前一行和当前行的状态 ,
// current_column 为访问到了第几列
void DFS(int t, int pre_row_state, int current_row_state, int current_column) {
	if (current_column == column_num) {
		sum[t][current_row_state] += sum[1 - t][pre_row_state];
		printf("DFS t=%d, pre_row_state=%d, current_row_state=%d sum=%I64d\n",
				t, pre_row_state, current_row_state, sum[t][current_row_state]);
		return;
	}

	if ((current_column + 1) <= column_num) {
		// 当前行不放置 由于不放置，所以应该设置当前行对应bit位为0，而查询前一行对应bit位为1的
		// 因为如果前一行bit位也为零则在填充后面的时候会出现漏洞
		DFS(t , (pre_row_state << 1) + 1, current_row_state << 1,
				current_column + 1) ;
		// 当前行竖直放置 由于水平放置，所以应该设置当前行对应bit位为1，而查询前一行对应bit位为0的
		// 因为如果前一行bit为也为1则无法竖直填充当前行
		DFS(t , pre_row_state << 1, (current_row_state << 1) + 1,
				current_column + 1) ;
	}

	if ((current_column + 2) <= column_num) {
		// 当前行水平放置 由于水平放置，所以应该设置当前行对应bit位为11，而查询前一行对应bit位也为11的
		DFS(t , (pre_row_state << 2) + 3, (current_row_state << 2) + 3,
				current_column + 2) ;
	}
}
int main() {
	while (scanf("%d %d", &row_num , &column_num)) {
		if ((row_num | column_num) == 0)
			break;

		//  都为奇数肯定无解
		if (((row_num & 1) == 1) && ((column_num & 1) == 1)) {
			printf("0\n") ;
			fflush(stdout);
			continue;
		}

		if (row_num < column_num) // 交换
		{
			int tmp = row_num ;
			row_num = column_num , column_num = tmp ;
		}

		memset(sum , 0, sizeof(sum)) ;
		sum[0][(1<<column_num) - 1] = 1;
		int i, t = 0;

		for (i = 1; i <= row_num ; i ++) { // 此处是<=而不是<，这就解决了之前无法填满的那个问题
			DFS(1 - t , 0, 0, 0) ;
			memset(sum[t], 0, sizeof(sum[t])) ;
			t = 1 - t ;
		}

		printf("%I64d\n", sum[t][(1<<column_num) - 1]) ;
		fflush(stdout);
	}

	return 0;
}
