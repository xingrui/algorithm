/*
 * https://en.wikipedia.org/wiki/Find_first_set
 * an important function : ffs
 * using hardware instruction to compute __builtin_clz
 */

/*
 * __builtin_ffs
 * __builtin_clz
 * __builtin_ctz
 * __builtin_ctzl
 * __builtin_ctzll
 */

#include <strings.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

int f1(unsigned int x)
{
    int n = 1;

    // if(x==0) return -1;
    if ((x >> 16) == 0) {
        n += 16;
        x <<= 16;
    }

    if ((x >> 24) == 0) {
        n += 8;
        x <<= 8;
    }

    if ((x >> 28) == 0) {
        n += 4;
        x <<= 4;
    }

    if ((x >> 30) == 0) {
        n += 2;
        x <<= 2;
    }

    n = n - (x >> 31);
    return 31 - n;
}

int f2(unsigned int x)
{
    return 31 - __builtin_clz(x);
}

int f3(unsigned int x)
{
    return int(trunc(log2(x)));
}

int get_log2(unsigned int x)
{
    return f2(x);
}

int test_clz()
{
    int var = 0xe0;
    printf("%d\n", __builtin_ffs(var));
    printf("%d\n", __builtin_clz(var));
    printf("%d\n", __builtin_clzl(var));
    printf("%d\n", __builtin_ctz(var));
    printf("%d\n", __builtin_ctzl(var));
    printf("%d\n", __builtin_ctzll(var));
    unsigned int bvar = 0xfff + 1;
    int res1 = f1(bvar);
    int res2 = f2(bvar);
    printf("%d %d\n", res1, res2);
    printf("%d %d\n", bvar, 1 << res1);
    return 0;
}

#define MN 50005
using namespace std;
int mi[MN][17], mx[MN][17], w[MN];
int n, q;
void rmqinit()
{
    int i, j, m;

    for (i = 1; i <= n; i++) {
        mi[i][0] = mx[i][0] = w[i];
    }

    m = get_log2(n);

    for (i = 1; i <= m; i++) {
        for (j = n; j >= 1; j--) {
            mx[j][i] = mx[j][i - 1];

            if (j + (1 << (i - 1)) <= n)
                mx[j][i] = max(mx[j][i], mx[j + (1 << (i - 1))][i - 1]);

            mi[j][i] = mi[j][i - 1];

            if (j + (1 << (i - 1) <= n))
                mi[j][i] = min(mi[j][i], mi[j + (1 << (i - 1))][i - 1]);
        }
    }
}

int rmqmin(int l, int r)
{
    int m = get_log2(r - l + 1);
    return min(mi[l][m], mi[r - (1 << m) + 1][m]);
}

int rmqmax(int l, int r)
{
    int m = get_log2(r - l + 1);
    return max(mx[l][m], mx[r - (1 << m) + 1][m]);
}

int main()
{
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);

    rmqinit();
    int l, r;

    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &l, &r);
        printf("%d %d\n", rmqmax(l, r), rmqmin(l, r));
    }

    while (cin >> n)
        return 0;
}

