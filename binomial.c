/*
 ============================================================================
 Name        : binomial.cpp
 Author      : xingrui
 Version     :
 Copyright   : GPL
 Description : https://www.interviewstreet.com/challenges/dashboard/#problem/4fe19c4f35a0e
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
char buffer[600];
/* In mathematics, binomial coefficients are a family of positive integers 
 * that occur as coefficients in the binomial theorem.
 * denotes the number of ways of choosing k objects from n different objects.
 * However when n and k are too large, we often save them after modulo operation by a prime number P. 
 * Please calculate how many binomial coefficients of n become to 0 after modulo by P.
 * Input
 * The first of input is an integer T , the number of test cases.
 * Each of the following T lines contains 2 integers,  n and prime P.
 * Output
 * For each test case, output a line contains the number of  s (0<=k<=n)  
 * each of which after modulo operation by P is 0.
 * Sample Input
 * 3
 * 2 2
 * 3 2
 * 4 3
 * Sample Output
 * 1
 * 0
 * 1
 * Constraints:
 * T is less than 100
 * n is less than 10^500.
 * P is less than 10^9.
 */
/*
 * 这个问题的解答要用到数学上的定理 Kummer's Theorem
 * 将n表示成以p(p为素数)为基的数字,假设为p1p2...pk
 * 在C(n,m)(m=0,1,...,n)的n+1个数中，不能被p整除的个数为
 * (p1+1)*(p2+1)*...*(pk+1)
 * 
 * 定理
 * Cnk(k=0...n)组合数中，不能够被p整除的数字个数为
 * 将n表示为p进制以后，所有的进制上数字+1然后相互乘起来
 * 
 * 定理的证明参见冯志刚的《初等数论》一书37页
 * 
 * */

// 本程序约定：所有的大整数在进入处理函数前都是从左边第一位开始的减去'0'以后的数字
//          也就是说，所有的操作都需要数字的长度，因为无法通过strlen来判断长度
int PRIME_SPLIT=INT_MAX/10+1;
#define BUFFER_SIZE 600
#define MAX_PRIME_ARRAY_SIZE 2000
#define BYTE unsigned char
char g_current_num[BUFFER_SIZE]; // 读取进来数字的以10进制表示的
int g_num_base_prime[MAX_PRIME_ARRAY_SIZE]; // 取大于log2(10)的最小整数 * 500 因为n位的十进制数表示成二进制约为n*log2(10)位
char g_temp_array[2][BUFFER_SIZE];
void print_result(char* result_array, int length);
void print_array(char* result_array, int length);
void process(int prime, char* buffer, int* p_result_length);
int convert_to_base_prime(int prime, int current_num_length);
void divide_by_prime(int prime, char* input_array, int input_length,
		char* output_array, int* output_length, int* p_remainder);
void multiply(char* multi1, int length1, char* multi2, int length2,
		char* result, int* p_result_length);
void minus_add_one(char* first, int first_length, char* second,
		int second_length, char* result, int* p_result_length);
void remove_ascii_0(char* array, int length) {
	int index = 0;
	for (; index < length; ++index)
		array[index] -= '0';
}
void add_ascii_0(char* array, int length) {
	int index = 0;
	for (; index < length; ++index)
		array[index] += '0';
}

int test_multiply() {
	int array1[]= { 1000, 999, 999, 99, 9, 1, 3, 3, 13, 31 };
	int array2[]= { 999, 0, 999, 99, 9, 1, 3, 4, 13, 31 };
	//int array1[]= { 1 };
	//int array2[]= { 10 };
	int count = sizeof(array1) /sizeof(int);
	while(--count >= 0)
	{
		sprintf(g_temp_array[0], "%d", array1[count]);
		sprintf(g_temp_array[1], "%d", array2[count]);
		int len1 = strlen(g_temp_array[0]);
		int len2 = strlen(g_temp_array[1]);
		remove_ascii_0(g_temp_array[0], len1);
		remove_ascii_0(g_temp_array[1], len2);
		char buffer[BUFFER_SIZE];
		int result_length;
		multiply(g_temp_array[0], len1, g_temp_array[1], len2, buffer,
		&result_length);
		add_ascii_0(buffer, result_length);
		print_result(buffer, result_length);
	}
	return 0;
}

int test_minus_add_one() {
	int array1[]= { 1000, 999, 999, 998 };
	int array2[]= { 999, 0, 999, 999 };
	int count = sizeof(array1) /sizeof(int);
	while(--count >= 0)
	{
		sprintf(g_temp_array[0], "%d", array1[count]);
		sprintf(g_temp_array[1], "%d", array2[count]);
		int len1 = strlen(g_temp_array[0]);
		int len2 = strlen(g_temp_array[1]);
		remove_ascii_0(g_temp_array[0], len1);
		remove_ascii_0(g_temp_array[1], len2);
		char buffer[BUFFER_SIZE];
		int result_length;
		minus_add_one(g_temp_array[0], len1, g_temp_array[1], len2, buffer,
		&result_length);
		add_ascii_0(buffer, result_length);
		print_result(buffer, result_length);
	}
	return 0;
}

int test_divide_by_prime() {
	int number[] = { 123 };
	int prime[] = { 2 };
	int count = sizeof(number) / sizeof(int);
	while (--count >= 0) {
		sprintf(g_temp_array[0], "%d", number[count]);
		int number_length = strlen(g_temp_array[0]);
		remove_ascii_0(g_temp_array[0], number_length);
		int result_length;
		int remain;
		divide_by_prime(prime[count], g_temp_array[0], number_length,
		g_temp_array[1], &result_length, &remain);
		add_ascii_0(g_temp_array[1], result_length);
		print_result(g_temp_array[1], result_length);
		printf("remain : %d\n", remain);
	}
	return 0;
}

int main(void) {
	char buffer[BUFFER_SIZE];
	int test_case_count;
	fgets(buffer, BUFFER_SIZE, stdin);
	sscanf(buffer, "%d", &test_case_count);
	while (test_case_count-- > 0) {
		int prime;
		int result_length;
		fgets(buffer, BUFFER_SIZE, stdin);
		sscanf(buffer, "%s %d", g_current_num, &prime);
		process(prime, buffer, &result_length);
		add_ascii_0(buffer, result_length);
		print_result(buffer, result_length);
		fflush(stdout);
	}
	// test_minus_add_one();
	// test_multiply();
	// test_divide_by_prime();
	return EXIT_SUCCESS;
}
void print_base_array(int num) {
	int i;
	for (i = 0; i < num; ++i) {
		printf("%d, ", g_num_base_prime[i]);
	}
	puts("");
}
// buffer 输出参数 用来存放处理的结果 也就是最后要求的答案
void process(int prime, char* buffer, int* p_result_length) {
	int current_num_length = strlen(g_current_num);
	int n_base_prime_length = convert_to_base_prime(prime, current_num_length);
	int index;
	int array_length[2];
	// 一直定不下来是从开头好还是从结尾好，sprintf帮我确定了这个数字
	char current_location_num[20];
	int current_location_num_length;
	int t = 0;
	sprintf(g_temp_array[0], "%d", g_num_base_prime[0] + 1);
	array_length[0] = strlen(g_temp_array[0]);
	remove_ascii_0(g_temp_array[0], array_length[0]);
	for (index = 1; index < n_base_prime_length; ++index) {
		// 把所有每个位置上面的数字+1然后乘起来，获取到不能被p整除的所有数字的个数
		sprintf(current_location_num, "%d", g_num_base_prime[index] + 1);
		current_location_num_length = strlen(current_location_num);
		remove_ascii_0(current_location_num, current_location_num_length);
		multiply(g_temp_array[t], array_length[t], current_location_num,
				current_location_num_length, g_temp_array[1-t], array_length+ 1
						- t);
		t = 1 - t;
	}
	//print_base_array(n_base_prime_length);
	//printf("%d\n", n_base_prime_length);
	//fflush(stdout);
	//print_array(g_temp_array[t], array_length[t]);
	// 这个还不是最终结果，因为还要使用原来的数字+1减去当前这个数字
	minus_add_one(g_current_num, current_num_length, g_temp_array[t],
			array_length[t], g_temp_array[1 - t], array_length + 1- t);
	*p_result_length = array_length[1 - t];
	memcpy(buffer, g_temp_array[1 - t], (*p_result_length + 1) * 4);
}
// 被减数 减数和差各自的数组及长度
void minus_add_one(char* first, int first_length, char* second,
		int second_length, char* result, int* p_result_length) {
	int carry = 1;
	char* first_current = first + first_length;
	char* second_current = second + second_length;
	char* result_current = result + BUFFER_SIZE;
	while (second_current != second) {
		--first_current;
		--second_current;
		--result_current;
		char char_minus = *first_current + carry - *second_current;
		if (char_minus < 0) {
			carry = -1;
			*result_current = char_minus + 10;
		} else if (char_minus < 10) {
			carry = 0;
			*result_current = char_minus;
		} else {
			carry = 1;
			*result_current = 0;
		}
	}
	if (-1 == carry) {
		while (*--first_current == 0) {
			*--result_current = 9;
		}
		*--result_current = *first_current - 1;
	}
	if (1 == carry) {
		while (*--first_current == 9) {
			if (first_current == first) {
				*--result_current = 1;
				goto end_of_minus;
			} else {
				*--result_current = 0;
			}
		}
		*--result_current = *first_current + 1;
	}
	while (first_current != first)
		*--result_current = *--first_current;
	while (0 == *result_current && result_current != (result + BUFFER_SIZE- 1))
		++result_current;
	end_of_minus: *p_result_length = result + BUFFER_SIZE- result_current;
	memmove(result, result_current, *p_result_length);
	result[*p_result_length] = 0;
}

// multi1  : 1st multiply number array
// length1 : 1st multiply number length
// multi2  : 2nd multiply number array
// length2 : 2nd multiply number length
// result  : multiply number result array
// p_result_length : store result length
void multiply(char* multi1, int length1, char* multi2, int length2,
		char* result, int* p_result_length) {
	if ((length1 ==1&&multi1[0] == 0)|| (length2 ==1&& multi2[0]==0)) {
		result[0] = 0;
		*p_result_length = 1;
		return;
	}
	int cur_index2 = 0;
	memset(result, 0, BUFFER_SIZE);
	char carry = 0;
	int result_end= BUFFER_SIZE - 1;
	while (cur_index2 < length2) {
		char num = multi2[length2 - cur_index2 - 1];
		int cur_index1 = 0;
		carry = 0;
		while (cur_index1 < length1) {
			char res = num * multi1[length1 - cur_index1 - 1]+ carry
					+ result[result_end - cur_index1 - cur_index2];
			carry = res / 10;
			result[result_end - cur_index1 - cur_index2] = res % 10;
			++cur_index1;
		}
		result[result_end - cur_index1 - cur_index2] = carry;
		++cur_index2;
	}
	*p_result_length = length1 + length2 - 1;
	if (carry != 0) {
		(*p_result_length)++;
		result[result_end - length1 - length2 + 1] = carry;
	}
	memmove(result, result + result_end - *p_result_length + 1,
			*p_result_length);
	result[*p_result_length] = 0;
}
// 进制转换函数
// 结果存放在全局变量g_num_base_prime当中
// 返回该数字在p进制下的长度
int convert_to_base_prime(int prime, int current_num_length) {
	int current_prime_index= MAX_PRIME_ARRAY_SIZE;
	int remainder;
	int temp_array_length[2];
	remove_ascii_0(g_current_num, current_num_length);
	int t = 0;
	divide_by_prime(prime, g_current_num, current_num_length, g_temp_array[t],
			&temp_array_length[t], &remainder);
	g_num_base_prime[--current_prime_index] = remainder;
	while (temp_array_length[t] != 1|| g_temp_array[t][0] != 0) {
		divide_by_prime(prime, g_temp_array[t], temp_array_length[t],
				g_temp_array[1 - t], &temp_array_length[1 - t], &remainder);
		g_num_base_prime[--current_prime_index] = remainder;
		t = 1 - t;
	}
	int num_prime_length= MAX_PRIME_ARRAY_SIZE - current_prime_index;
	memmove(g_num_base_prime, g_num_base_prime + current_prime_index,
			num_prime_length * 4);
	return num_prime_length;
}
// 除法运算函数 
// prime 除数
// input_array 被除数数组
// input_length 被除数长度
// output_array 结果数组
// p_output_length 存放结果长度
// p_remainder 存放余数
void divide_by_prime(int prime, char* input_array, int input_length,
		char* output_array, int* p_output_length, int* p_remainder) {
	int index = 0;
	int current_num = 0;
	int output_length = 0;
	int start = 0;
	while (index < input_length) {
		int divide = 0;
		if (current_num < PRIME_SPLIT) {
			current_num*=10;
			current_num += input_array[index];
			divide = current_num / prime;
			current_num %= prime;
		} else {
			int ite_num = 1;
			int total_sum = current_num;
			while (ite_num < 10) {
				total_sum+=current_num;
				if (total_sum > prime) {
					++divide;
					total_sum %= prime;
				}
				++ite_num;
			}
			current_num = total_sum + input_array[index];
			if (current_num > prime) {
				++divide;
				current_num%=prime;
			}
		}
		if (0 == divide) {
			if (start) {
				output_array[output_length] = 0;
				++output_length;
			}
		} else {
			start = 1;
			output_array[output_length] = divide;
			++output_length;
		}
		++index;
	}
	if (start != 0) {
		*p_output_length = output_length;
	} else {
		*p_output_length = 1;
		output_array[0] = 0;
	}
	*p_remainder = current_num;
}
// 直接输出result_array里面的元素
void print_result(char* result_array, int length) {
	int index = 0;
	for (; index < length; ++index) {
		putchar(result_array[index]);
	}
	puts("");
}

void print_array(char* result_array, int length) {
	int index = 0;
	printf("current array is : ");
	for (; index < length; ++index) {
		putchar(result_array[index] + '0');
	}
	puts("");
}
