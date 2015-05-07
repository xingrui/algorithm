/*
 ============================================================================
 Name        : river.cpp
 Author      : xingrui
 Version     :
 Copyright   : GPL
 Description : 典型的DP问题 青蛙过河问题
 ============================================================================
 */
/* 
 * 问题描述
 * 在河上有一座独木桥，一只青蛙想沿着独木桥从河的一侧跳到另一侧。
 * 在桥上有一些石子，青蛙很讨厌踩在这些石子上。
 * 由于桥的长度和青蛙一次跳过的距离都是正整数，我们可以把独木桥上青蛙可能到达的点看成数轴上的一串整点：0，1，……，L（其中L是桥的长度）。
 * 坐标为0的点表示桥的起点，坐标为L的点表示桥的终点。
 * 青蛙从桥的起点开始，不停的向终点方向跳跃。一次跳跃的距离是S到T之间的任意正整数（包括S,T）。
 * 当青蛙跳到或跳过坐标为L的点时，就算青蛙已经跳出了独木桥。 
 * 题目给出独木桥的长度L，青蛙跳跃的距离范围S,T，桥上石子的位置。
 * 你的任务是确定青蛙要想过河，最少需要踩到的石子数。
 * 
 * 输入
 * 输入包含多组数据，每组数据第一行有一个正整数L（1 <= L <= 20000），表示独木桥的长度。
 * 第二行有三个正整数S，T，M，分别表示青蛙一次跳跃的最小距离，最大距离，及桥上石子的个数，
 * 其中1 <= S <= T <= 10，1 <= M <= 100。
 * 第三行有M个不同的正整数分别表示这M个石子在数轴上的位置（数据保证桥的起点和终点处没有石子）。
 * 所有相邻的整数之间用一个空格隔开。输入以一个0结束。
 * 
 * 输出
 * 对每组数据输出一行，这一行只包括一个整数，表示青蛙过河最少需要踩到的石子数。
 * 
 * */
/*
 * 解法仍然是动态规划算法 只不过由于石子数目的限制，将石头和答案放到一个一个char中
 * */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_LENGTH 20001
typedef struct SData {
	unsigned char has_stone : 1;
	unsigned char min_stone_count : 7;
} Data;
Data datas[MAX_LENGTH];
char buffer[100];
void calculate(void) {
	int L, S, T, M;
	fgets(buffer, 100, stdin);
	sscanf(buffer, "%d", &L);
	while (L) {
		int tmp;
		int i, j;
		fgets(buffer, 100, stdin);
		sscanf(buffer, "%d %d %d", &S, &T, &M);
		memset(datas, 0xfe, MAX_LENGTH);
		for (i = M; i; --i) {
			scanf("%d", &tmp);
			datas[tmp].has_stone = 1;
		}
		fgets(buffer, 100, stdin);
		for (j = S; j <= T; ++j) {
			datas[j].min_stone_count = datas[j].has_stone;
		}
		for (i = S; i < L; ++i) {
			if (datas[i].min_stone_count != 0x7f)
				for (j = S; j <= T; ++j) {
					if (i + j < L) {
						int cnt = datas[i].min_stone_count + datas[i+j].has_stone;
						if (cnt < datas[i+j].min_stone_count)
							datas[i+j].min_stone_count = cnt;
					} else {
						if (datas[i].min_stone_count < datas[L].min_stone_count)
							datas[L].min_stone_count = datas[i].min_stone_count;
					}
				}
		}
		printf("%d\n", datas[L].min_stone_count);
		fgets(buffer, 100, stdin);
		sscanf(buffer, "%d", &L);
	}
}

int main() {
	calculate();
	return EXIT_SUCCESS;
}
