//basic algorithm
// f(n,m)=(f(n-1, m) + m - 1)%n + 1
// suppose variable x, such that k+m*x-1=i+x
#include <stdio.h>
#include <stdlib.h>

long Josephus(long n, long m, long k) {
	// n total number of people
	// m step to out of the cycle
	// k start counting index
	if (m == 1)
		return (k+n-2)%n+1;
	else {
		long i = 1;
		for (; i <= n; ++i) {
			if ((k+m)<i) {
				long x=(i-k)/(m-1)-1;
				if (i + x < n) {
					i+=x;
					k+=m*x;
				} else {
					k+=m*(n-i);
					i=n;
				}
			}
			k=(k+m-1)%i + 1;
		}
	}
	return k;
}

long Josephus_iter(long n, long m) {
	int res = 1;
	long index = 1;
	while (index++ < n) {
		res = (res + m - 1)%index+1;
	}
	return res;
}

int main(void) {
	int m, n;
	while (scanf("%d %d", &n, &m)!=-1&& m != -1&& n != -1) {
		printf("%ld\n", Josephus(n, m, 1));
		fflush(stdout);
		printf("%ld\n", Josephus_iter(n, m));
		fflush(stdout);
	}
	return EXIT_SUCCESS;
}
