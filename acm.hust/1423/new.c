#include<stdio.h>
#include<math.h>
#define PI 3.141592653589793239
#define ee 2.7182818284590452354
int ans(int n)
{
    return (int)((n * log10(n / ee) + log10(sqrt(2 * n * PI)))) + 1;
}
int main()
{
    int n, i, k;
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        scanf("%d", &k);
        printf("%d\n", ans(k));
    }

    return 0;
}
