#include<iostream>
#include<cstdio>
using namespace std;
long long get_value(long long input)
{
    if (input == 0 || input == 1)
        return input;

    int k = 0; //k<60
    long long l = 4;

    while (l < input) {
        ++k;
        l <<= 1;
    }

    l >>= 1;
    long long pos = input - l;
    long long len = l + 1;

    if (pos > (len / 2)) pos = len - pos - 1;

    if (pos == 0) {
        return 1;
    }

    long long vall, valr, posl, posr;
    vall = valr = 1;
    posl = 0;
    posr = len - 1;
    long long bpos = len / 2;
    long long bval = vall + valr;

    while (bpos != pos) {
        if (pos < bpos) {
            valr = bval;
            posr = bpos;
        } else if (pos > bpos) {
            vall = bval;
            posl = bpos;
        }

        bpos = (posl + posr) / 2;
        bval = vall + valr;
    }

    return bval;
}
int main()
{
    int range = 3122094;
    const int RANGE = 400000;
    int* least_num = new int[RANGE];
    memset(least_num, 0, RANGE * sizeof(int));
    int i;

    for (i = 1; i < range; ++i) {
        int value = get_value(i);

        if (value < RANGE && least_num[value] == 0) {
            least_num[value] = i;
        }
    }

    char buffer[30];

    while (fgets(buffer, 30, stdin)) {
        int num;
        sscanf(buffer, "%d", &num);

        if (num < RANGE) {
            printf("%d\n", least_num[num]);
        }
    }
}
int main2()
{
    int range = 643122094;
    int* a = new int[range];
    int* least_num = new int[400000];
    memset(least_num, 0, 400000 * sizeof(int));

    if (a == NULL)return -1;

    int i;
    a[0] = 0;
    a[1] = 1;

    for (i = 2; i < range; ++i) {
        if (i & 1) {
            a[i] = a[i / 2] + a[i / 2 + 1];
        } else {
            a[i] = a[i / 2];
        }
    }

    for (i = 1; i < range; ++i) {
        if (a[i] < 400000 && least_num[a[i]] == 0) {
            least_num[a[i]] = i;
        }
    }

    char buffer[30];

    while (fgets(buffer, 30, stdin)) {
        int num;
        sscanf(buffer, "%d", &num);
        printf("%d\n", least_num[num]);
    }
}
