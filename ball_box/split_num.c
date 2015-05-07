/*
 ============================================================================
 Name        : split_num.cpp
 Author      : xingrui
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define N 400
unsigned long long a[N][N];
int main(void) {
	int i,j,k;
	a[0][0] = 1;
	for (i = 0; i < N; ++i) {
		a[i][1]=a[1][i]=a[0][i]=1;
	}
	for (i = 2; i < N; ++i) {
		for (j = 2; j <= i; ++j) {
			for (k = 1; k <= i && k <= j; ++k) {
				a[i][j] += a[i-k][k];
		    }
		}
		for(;j<N;++j){
			a[i][j]=a[i][i];
		}
	}
	for(i = 0; i < N; ++i) {
		printf("%d:%llu\n", i, a[i][i]);
	}
	return EXIT_SUCCESS;
}
