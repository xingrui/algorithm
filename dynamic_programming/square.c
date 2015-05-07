//============================================================================
// Name        : square.cpp
// Author      : xingrui
// Version     :
// Copyright   : GPL
// Description : 祭祀广场问题 来自北京邮电大学的 bianchengla.com 
// 输入
// 包含多组测试数据，每组测试数据的第一行是两个正整数M、N（1<=M<=3000，1<=N<=3000），表示建设广场的矩形区域的长和宽。
// 然后接下来是M×N的0、1矩阵。(0表示可以用来建设，1表示不可以用来建设)
// 输入数据以0 0结束。
// 输出
// 对应每组测试数据，仅输出一行，即广场的最大边长。(广场必须是正方形)
//============================================================================

//============================================================================
// 典型的动态规划题目
// 假设读取的数据保存在矩阵Status当中
// 创建M*N的矩阵MaxSquare，采取一行一行依次遍历的方法
// MaxSquare[i][j]中的数据表示以[i][j]位置为右下角对应的最大正方形边长
// 容易知道MaxSquare[i+1][j+1]对应的数字应该是
// 0 (Status[i+1][j+1] == 1)
// Min(MaxSquare[i][j+1], MaxSquare[i+1][j], MaxSquare[i][j]) + 1 (Status[i+1][j+1] == 0)
// 基本的思路就是上面的内容，我写的程序是采取了优化以后的代码
// 由于可以重复利用空间，因此可以直接一个缓冲数组currentRow来计算动态规划的过程
//============================================================================
#include <stdio.h>
#include <stdlib.h>
int currentRow[3000];
char buffer[6000];
int judging() {
	int nRow, nCol;
	currentRow[0] = 0;
	fgets(buffer, 100, stdin);
	sscanf(buffer, "%d %d", &nRow, &nCol);
	if (nRow || nCol) {
		int curRow, curCol;
		int maxSquare = 0;
		for (curRow = 0; curRow < nRow; ++curRow) {
			int tmpNumber = currentRow[0];
			fgets(buffer, 10000, stdin);
			for (curCol = 0; curCol < nCol; ++curCol) {
				if (curCol && curRow) {
					if (buffer[2*curCol] == '0') {
						// tmpNumber is MaxSquare[i][j]
						int min = tmpNumber;
						// currentRow[curCol] is MaxSquare[i+1][j]
						if (min>currentRow[curCol])
							min = currentRow[curCol];
						// currentRow[curCol-1] is MaxSquare[i][j+1]
						if (min>currentRow[curCol-1])
							min = currentRow[curCol-1];
						++min;
						// the number is the MaxSquare[i][j] in the next iterator
						tmpNumber = currentRow[curCol];
						// set back the number 
						currentRow[curCol] = min;
						if (min > maxSquare)
							maxSquare = min;
					} else {
						currentRow[curCol] = 0;
					}
				} else {
					currentRow[curCol] = buffer[2*curCol] == '0';
					if (currentRow[curCol] > maxSquare)
						maxSquare = currentRow[curCol];
				}
			}
		}
		printf("%d\n", maxSquare);
		fflush(stdout);
		return 1;
	}
	return 0;
}

int main(void) {
	while (judging())
		;
	return EXIT_SUCCESS;
}