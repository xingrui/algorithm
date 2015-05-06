#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000000
size_t max = 0;
size_t cnt[MAX_SIZE];
size_t INT_MAX = (size_t)-1;
size_t NUM_MAX;

typedef struct {
	size_t pre;
	size_t post;
} BigInt;

size_t calculate(size_t input);
BigInt threeaddone(BigInt input) {
	BigInt num;
	int test;
	num.pre = input.pre + (input.pre>>1);
	test = input.pre & 1;
	num.post = input.post + (input.post>>1)+ 1;
	if (num.post < input.post) {
		num.pre+=1;
	}
	if (test) {
		if (num.post&(1<<31)) {
			num.post &= ((size_t)1<<31)-1;
			num.pre +=1;
		} else {
			num.post |=(size_t)1<<31;
		}
	}
	return num;
}
size_t calBigInt(BigInt input) {
	if (input.post & 1) {
		return calBigInt(threeaddone(input)) + 2;
	} else {
		if (input.pre == 0)
			return calculate(input.post >> 1) + 1;
		else if (input.pre == 1)
			return calculate(input.post>>1| 1<<31) + 1;
		else {
			BigInt num;
			num.pre = input.pre / 2;
			num.post = input.post / 2;
			if (num.pre & 1)
				num.post |= 1<<31;
			return calBigInt(num) + 1;
		}
	}
}

size_t calculate(size_t input) {
	if (max < input)
		max = input;
	if (input < MAX_SIZE) {
		if (cnt[input] != -1)
			return cnt[input];
		else {
			if (input & 1) {
				size_t count;
				count = calculate(3*input+1)+1;
				cnt[input] = count;
				return count;
			} else {
				size_t count;
				count = calculate(input / 2) + 1;
				cnt[input] = count;
				return count;
			}
		}
	}
	if (input & 1) {
		size_t count;
		if (input >= NUM_MAX) {
			BigInt num;
			num.post = input + input / 2+ 1;
			if (num.post < input)
				num.pre = 1;
			else
				return calculate(num.post) + 2;
			return calBigInt(num) + 2;
		}
		count = calculate(input + input / 2+ 1)+2;
		return count;
	} else {
		size_t count;
		count = calculate(input / 2) + 1;
		return count;
	}
}

int three(void) {
	size_t index = 0;
	NUM_MAX = INT_MAX / 3* 2;
	for (; index < MAX_SIZE; ++index)
		cnt[index] = -1;
	cnt[1] = 1;
	cnt[2] = 2;
	cnt[4] = 3;
	for (index = 3; index < MAX_SIZE; ++index) {
		calculate(index);
	}

	return EXIT_SUCCESS;
}
char buffer[100];
int main() {
	int start, end, i;
	three();
	while (scanf("%d %d", &start, &end) != EOF) {
		int small, big;
		if (start < end) {
			small = start;
			big = end;
		} else {
			small = end;
			big = start;
		}
		size_t max_count = 0;
		for (i = small; i <= big; ++i) {
			if (max_count < cnt[i])
				max_count = cnt[i];
		}
		printf("%d %d %d\n", start, end, max_count);
		fflush(stdout);
	}
	return EXIT_SUCCESS;
}
