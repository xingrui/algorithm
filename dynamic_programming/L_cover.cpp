// https://www.interviewstreet.com/challenges/dashboard/#problem/4f5bcc9549433
// Brick Tiling
/****************************************************************************
 * Name        : L_cover.cpp
 * Author      : xingrui
 * Version     :
 * Copyright   : GPL
 * Description : 使用L型图形覆盖图形问题
 *****************************************************************************/

/****************************************************************************
 * 问题描述
 * 有M*N的一个矩阵，里面的存储的是0 1数组，数字为0表示此处为空，数字为1表示此处不为空
 * 要用如下所示的八种形状完美覆盖此图
 *     *          *            *               *                   * *     * *
 * (1) *   (2)    *    (3) * * * (4) * * * (5) * * * (6) * * * (7) *   (8)   *
 *     * *      * *                      *               *         *         * 
 * 请输出覆盖的总方法数
 ***************************************************************************/

/****************************************************************************
 * 解决问题的思路
 * 仍然采用压缩状态DP的方法，采取类似于多米诺骨牌覆盖的方式来解决
 * 不过和之前的相比，有两个复杂的地方
 * (1) 此时当前的状态不仅受前一行状态的影响，而是受之前两行的影响
 * (2) 此时的覆盖不再是一个规则的长方形，而是一个有障碍的物体
 * 
 ***************************************************************************/
/****************************************************************************
 * You are given a grid having N rows and M columns. 
 * A grid square can either be blocked or empty. 
 * Blocked squares are represented by a '#' 
 * and empty squares are represented by '.'. 
 * Find the number of ways to tile the grid using L shaped bricks. 
 * A L brick has one side of length three units while other of length 2 units. 
 * All empty squares in the grid should be covered by exactly one of the L shaped tiles, 
 * and blocked squares should not be covered by any tile. 
 * The bricks can be used in any orientation (they can be rotated or flipped).
 * 
 * Input:
 * The first line contains the number of test cases T. 
 * T cases follow. Each case contains N and M on the first line, 
 * followed by N lines describing each row of the grid.
 * 
 * Output:
 * Output the number of ways to tile the grid. 
 * Output each answer modulo 1000000007.
 * 
 * Constraints:
 * 1 <= T <= 50
 * 1 <= N <= 20
 * 1 <= M <= 8
 * Each grid square will be either '.' or '#'.
 * 
 ***************************************************************************/
/*
 * TODO 可以考虑的问题 如果跨越多行，采取这种方法肯定就不合适了
 * 还有什么其他的解法呢?
 * */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_N 1<<8|3
#define MAX_COLUMN 8
#define MAX_ROW 20
int sum[MAX_ROW][MAX_N][MAX_N]; // 最关键的地方，弄明白sum的含义
// 把第i行以前的所有行填满以后i行状态为j,i+1行状态为k的总数保存在sum[i][j][k]当中
// 现在考虑将第0行填满时，第一行和第二行对应的状态总数
int row_num, column_num;
#define BYTE unsigned char
BYTE board[MAX_ROW + 1];
BYTE one_bit[8]= {1, 2, 4, 8, 16, 32, 64, 128};
BYTE two_bit[8]= {0, 3, 6, 12, 24, 48, 96, 192};
BYTE three_bit[8]= {0, 0, 7, 14, 28, 56, 112, 224};
// 由于最多8列因此采取BYTE来存储数据这样用起来也方便
// 打印读取的棋盘内容
void printboard() {
	printf("row_num : %d, column_num = %d\n", row_num, column_num);
	for (int i = 0; i < row_num; ++i) {
		printf("%d: ", board[i]);
		for (int j = column_num - 1; j >=0; --j)
			printf("%c", (board[i] & one_bit[j]) ? '#' : '.');
		puts("");
	}
}

void DFS(int row_num, BYTE pre_state1, BYTE pre_state2, BYTE cur_state1,
		BYTE cur_state2, int current_column) {
	// TODO 仔细考虑column的设计 DONE
	// 应该没有重复计算啊 因为所有状态的pre_state都是不相同的，都是从不同的pre_state过来的啊
	if (current_column == column_num) {
		/*printf(
		 "row_num = %d, pre(0X%X, 0X%X, board 0X%X), -->cur(0X%X, 0X%X):count(%d)\n",
		 row_num, pre_state1, pre_state2, board[row_num + 1],
		 cur_state1, cur_state2,
		 sum[row_num - 1][pre_state1][pre_state2]);*/
		sum[row_num][cur_state1][cur_state2]
				+= sum[row_num - 1][pre_state1][pre_state2];
		if (sum[row_num][cur_state1][cur_state2] > 1000000007)
			sum[row_num][cur_state1][cur_state2] %= 1000000007;
		return;
	}
	int bit_column = column_num - 1- current_column;
	if ((pre_state1 & one_bit[bit_column]) == 0) {
		// 当前位不为1，才能进行下一步计算
		// 在之前的例子中，并没有对条件进行判断就直接进行了状态转化
		// 是因为要判断的条件太少了，并没有多少需要判断的地方
		// 而在这个例子当中就不同了，必须首先判断能否放入其中，然后再进行状态转换
		// 一共需要判断八种状态，一种一种判断
		// 碰到了空格是必须添加方块的，如果不添加肯定不能完成铺满的任务
		// 问题 如果转化不了怎么办？ 转化不了说明不能够完美覆盖
		if (current_column > 0) {
			//   *
			//   *
			// * *
			if ((cur_state1 & one_bit[bit_column]) == 0&& (cur_state2
					& two_bit[bit_column + 1]) == 0) {
				DFS(row_num, pre_state1, pre_state2, cur_state1
						|one_bit[bit_column], cur_state2
						| two_bit[bit_column + 1], current_column + 1);
			}
			if (current_column > 1) {
				//     *
				// * * *
				if ((cur_state1& three_bit[bit_column + 2])== 0) {
					DFS(row_num, pre_state1, pre_state2, cur_state1
							| three_bit[bit_column + 2], cur_state2,
							current_column + 1);
				}
			}
		}
		if ((current_column + 1)< column_num) {

			// *
			// *
			// * *
			if ((cur_state1 & one_bit[bit_column])==0&& (cur_state2
					& two_bit[bit_column])==0) {
				DFS(row_num, pre_state1, pre_state2, cur_state1
						|one_bit[bit_column], cur_state2| two_bit[bit_column],
						current_column + 1);
			}
			// * *
			// *
			// *
			if ((pre_state1 & two_bit[bit_column ])== 0&& (cur_state1
					& one_bit[bit_column])==0
					&&(cur_state2& one_bit[bit_column])==0) {
				DFS(row_num, pre_state1, pre_state2, cur_state1
						| one_bit[bit_column], cur_state2| one_bit[bit_column],
						current_column+2);
			}
			// * *
			//   *
			//   *
			if ((pre_state1 & two_bit[bit_column])== 0&&(cur_state1
					&one_bit[bit_column-1])==0&&(cur_state2
					&one_bit[bit_column-1])==0) {
				DFS(row_num, pre_state1, pre_state2, cur_state1
						| one_bit[bit_column-1], cur_state2
						| one_bit[bit_column-1], current_column+2);
			}
			if ((current_column + 2) < column_num) {
				// *
				// * * *
				if ((cur_state1 & three_bit[bit_column])== 0) {
					DFS(row_num, pre_state1, pre_state2, cur_state1
							| three_bit[bit_column], cur_state2, current_column
							+ 1);
				}
				// * * *
				// *
				if ((pre_state1 & three_bit[bit_column]) == 0&& (cur_state1
						& one_bit[bit_column]) == 0) {
					DFS(row_num, pre_state1, pre_state2, cur_state1
							| one_bit[bit_column], cur_state2, current_column
							+ 3);
				}

				// * * *
				//     *
				if ((pre_state1 & three_bit[bit_column]) == 0&& (cur_state1
						& one_bit[bit_column - 2])==0) {
					DFS(row_num, pre_state1, pre_state2, cur_state1
							| one_bit[bit_column - 2], cur_state2,
							current_column + 3);
				}
			}
		}
	} else { // (pre_state1 & one_bit[bit_column]) != 0
		DFS(row_num, pre_state1, pre_state2, cur_state1, cur_state2,
				current_column+ 1);
	}
}
void printSum() {
	for (int i = 1; i < row_num; ++i)
		for (int j = 0; j < (1 << column_num); ++j)
			for (int k = 0; k < (1 << column_num); ++k)
				printf("i=%d, j=%d, k=%d, sum = %d\n", i, j, k, sum[i][j][k]);
}
// 计算种类数的函数
int process() {
	memset(sum , 0, sizeof(sum));
	// 在将第0行以前所有行填满时，只可能有一种情况，那就是第0行状态为board[0]，第1行状态为board[1]
	sum[0][board[0]][board[1]] = 1;
	BYTE pre_state1, pre_state2, cur_state1, cur_state2;
	int current_row = 1;
	// 由于首行只可能有一种状态，故直接计算这种状态，不再进行循环计算
	DFS(1, board[current_row - 1], board[current_row], board[current_row],
			board[current_row + 1], 0);
	int sum_column = 1<<column_num;
	for (current_row = 2; current_row != row_num; current_row++) {
		// 边界情况处理 : 采用之前就初始化的状态，循环中不需要再进行额外的判断
		// 也就是之前board最后一行后面添加了全为1的一行，省得在代码中重复判断
		pre_state1 = board[current_row - 1];
		pre_state2 = cur_state1 = board[current_row];
		cur_state2 = board[current_row + 1];
		// 搜索 
		for (int i = 0; i<sum_column; ++i)
			for (int j = 0; j < sum_column; ++j)
				if (sum[current_row - 1][i][j] != 0)
					DFS(current_row , i, j, j, cur_state2, 0);
	}
	//printSum();
	return sum[row_num - 1][(1 << column_num) - 1][(1 << column_num) - 1];
}
int main() {
	char buffer[100];
	int test_case_count;
	fgets(buffer, 100, stdin);
	sscanf(buffer, "%d", &test_case_count);
	while (test_case_count--) {
		memset(board, 0, MAX_ROW); // 清空棋盘内容
		int currentRow = 0;
		fgets(buffer, 100, stdin);
		sscanf(buffer, "%d %d", &row_num , &column_num); // 读取棋盘大小
		// 读取棋盘内容
		for (; currentRow < row_num; ++currentRow) {
			fgets(buffer, MAX_COLUMN + 3, stdin);
			for (int i = 0; i < column_num; ++i) {
				board[currentRow] <<= 1;
				board[currentRow] |= buffer[i] == '#';
			}
		}
		board[row_num] = (1<<column_num)-1; // 最后一行的下面一行视为已经填满，因为无法填入这一行
		//printboard();
		// 计算覆盖种类数
		int result = process();
		printf("%d\n", result);
		fflush(stdout);
	}
	return 0;
}

