/*
 ============================================================================
 Name        : invert_sort.cpp
 Author      : xingrui
 Version     : insert str1 to str2 to make palindrome
 Copyright   : GPL
 Description : Invert Sort Algorithm In Microsoft's Book Beautiful Programming
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
const int LENGTH = 10;
int method[100];
int nMaxCount;
void init(int *array, int length) {
	array[0] = 3;
	array[1] = 2;
	array[2] = 1;
	array[3] = 6;
	array[4] = 5;
	array[5] = 4;
	array[6] = 9;
	array[7] = 8;
	array[8] = 7;
	array[9] = 0;
}

void invert(int *array, int start, int end) {
	int index;
	for (index = 0; 2 * index < end - start; ++index) {
		int tmp = array[start + index];
		array[start + index] = array[end - index];
		array[end-index] = tmp;
	}
}

void printArray(int *array, int length) {
	int index;
	for (index = 0; index < length; ++index)
		printf("%d ", array[index]);
	puts("");
}

int isSorted(int *array, int length) {
	int index;
	for (index = 0; index < length - 1; ++index)
		if (array[index] > array[index+1])
			return 0;
	return 1;
}

int indent(int count) {
	int index = 0;
	while (index++ < count)
		printf("\t");
}

int calculate(int *array, int length, int count) {
	int i;
	int maxCount = 2*(length - 1);
	int currentCount;
	//indent(count);
	//printf("%d\n", count);
	if (count >= nMaxCount) {
		method[count] = 0;
		return 2*(length -1);
	}
	if (isSorted(array, length)) {
		method [count] = 0;
		nMaxCount = count;
		return count;
	}
	for (i = 1; i < length; ++i) {
		invert(array, 0, i);
		currentCount = calculate(array, length, count + 1);
		method[count] = i;
		if (currentCount < maxCount)
			maxCount = currentCount;
		invert(array, 0, i);
	}
	return maxCount;
}

int main(void) {
	int array[LENGTH];
	init(array, 10);
	nMaxCount = 2 * 10- 2;
	int count = calculate(array, 10, 0);
	printf("count:%d\n", count);
	//invert(array, 0, 2);
	printArray(array, 10);
	return EXIT_SUCCESS;
}
