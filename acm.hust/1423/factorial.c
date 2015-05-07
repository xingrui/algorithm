/* http://poj.org/problem?id=1423 */
#include<stdio.h>
#include<math.h>

int main()
{
    int N, j = 1;
    int number, temp = 0;
    long double member = 0;
    scanf("%d", &N);

    while (N > 0) {
        int i = 0;
        --N;
        scanf("%d", &number);
        member = 0;

        for (i = 1, temp = 0; i <= number; ++i) {
            member += log10(i * 1.0);
        }

        temp = floor(member) + 1;
        printf("%d\n", temp);
    }

    return 0;
}

