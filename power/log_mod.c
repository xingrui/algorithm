// http://bianchengla.com/problem/826/
// 1<=n<=1000 1<=x<=1000
#include<stdio.h>
#include<stdlib.h>
int MOD_NUM = 100007;
int calc(int n, int x)
{
    unsigned long tmp_num = x;
    unsigned long result = 1;
    while (n >= 1) {
        if (n & 1) {
            result *= tmp_num;
            result %= MOD_NUM;
        }
        n >>= 1;
        tmp_num *= tmp_num;
        tmp_num %= MOD_NUM;
    }
    return result;
}
int main()
{
    char buffer[100];
    int n = 0;
    int x = 0;

    while (fgets(buffer, 100, stdin)) {
        sscanf(buffer, "%d %d", &n, &x);

        if (n && x) {
            printf("%d\n", calc(n - 1, x + 1));
        } else {
            break;
        }
    }

    return 0;
}
