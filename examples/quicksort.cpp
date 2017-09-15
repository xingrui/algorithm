/*
 ============================================================================
 Name        : quicksort.cpp
 Author      : xingrui
 Version     : The most Beautiful Code I Never Wrote[Beautiful Code]
 Copyright   : GPL
 Description : Algorithms Improved Step By Step To Calculate Complexity Of Quick Sort
 ============================================================================
 */

#include<cstdlib>
#include<iostream>
using namespace std;
#define MAX_SIZE 10000
int array[MAX_SIZE];
float t[MAX_SIZE];

void swap(int i, int j) {
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

int randint(int l, int r) {
	srand(time(NULL));
	int num = rand();
	return l + num % (r - l + 1);
}

void quicksort1(int l, int u) {
	int i, m;
	if (l >= u)
		return;
	swap(l, randint(l, u));
	m = l;
	for (i = l + 1; i <= u; i++)
		if (array[i] < array[l])
			swap(++m, i);
	swap(l, m);
	quicksort1(l, m-1);
	quicksort1(m+1, u);
}

int compare_count = 0;

void quicksort2(int l, int u) {
	int i, m;
	if (l >= u)
		return;
	swap(l, randint(l, u));
	m = l;
	for (i = l + 1; i <= u; i++) {
		compare_count++;
		if (array[i] < array[l])
			swap(++m, i);
	}
	swap(l, m);
	quicksort2(l, m-1);
	quicksort2(m+1, u);
}

void quicksort3(int l, int u) {
	int i, m;
	if (l >= u)
		return;
	swap(l, randint(l, u));
	m = l;
	compare_count += u - l;
	for (i = l + 1; i <= u; i++) {
		if (array[i] < array[l])
			swap(++m, i);
	}
	swap(l, m);
	quicksort3(l, m-1);
	quicksort3(m+1, u);
}

void quicksort4(int l, int u) {
	int m;
	if (l >= u)
		return;
	m = randint(l, u);
	compare_count += u - l;
	quicksort4(l, m-1);
	quicksort4(m+1, u);
}

void quicksort5(int n) {
	int m;
	if (n <= 1)
		return;
	m = randint(1, n);
	compare_count += n - 1;
	quicksort5(m - 1);
	quicksort5(n - m);
}

int quicksort6(int N) {
	int m;
	if (N <= 1)
		return 0;
	m = randint(1, N);
	return N - 1+ quicksort6(m-1)+quicksort6(N-m);
}

float quicksort7(int N) {
	int m;
	float sum = 0;
	if (N <= 1)
		return 0;
	for (m = 1; m<=N; ++m)
		sum += N-1+quicksort7(m-1)+quicksort7(N-m);
	return sum/N;
}

float quicksort8(int N) {
	int num, i;
	t[0] = 0;
	for (num = 1; num <= N; num++) {
		float sum = 0;
		for (i = 1; i <= num; ++i)
			sum += num - 1+ t[i-1]+ t[num-i];
		t[num]=sum/num;
	}
	return t[N];
}

float quicksort9(int N) {
	int num, i;
	t[0] = 0;
	for (num = 1; num <= N; num++) {
		float sum = 0;
		for (i = 1; i <= num; ++i)
			sum += t[i-1]+ t[num-i];
		t[num]=num-1+sum/num;
	}
	return t[N];
}

float quicksort10(int N) {
	int num, i;
	t[0] = 0;
	for (num = 1; num <= N; num++) {
		float sum = 0;
		for (i = 1; i <= num; ++i)
			sum += 2*t[i];
		t[num]=num-1+sum/num;
	}
	return t[N];
}

float quicksort11(int N) {
	int num;
	t[0] = 0;
	float sum = 0;
	for (num = 1; num <= N; num++) {
		sum += 2*t[num - 1];
		t[num]=num-1+sum/num;
	}
	return t[N];
}

float quicksort12(int N) {
	int num;
	float t = 0;
	float sum = 0;
	for (num = 1; num <= N; num++) {
		sum += 2*t;
		t=num-1+sum/num;
	}
	return t;
}

int main() {
	for (int i = 0; i < MAX_SIZE; ++i)
		array[i] = MAX_SIZE - i;
	cout << "count:"<< quicksort12(MAX_SIZE);
	return 0;
}
