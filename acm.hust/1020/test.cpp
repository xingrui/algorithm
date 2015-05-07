// a[1] = 1
// a[2 * i] = a[i];
// a[2 * i + 1] = a[i] + a[i + 1];
#include <cstdio>
#include <cmath>
#include <cstring>
int main()
{
    int range = 643122094;
    //int range = 643122093;
    //int range = 1000000000;
    int* a = new int[range];
    int* first_location = new int[range];
    memset(first_location, 0, range * sizeof(int));
    int i;
    a[1] = 1;

    for (i = 2; i < range; ++i) {
        if (i & 1) {
            a[i] = a[i / 2] + a[i / 2 + 1];
        } else {
            a[i] = a[i / 2];
        }
    }

    for (i = 1; i < range; ++i) {
        if (first_location[a[i]] == 0) {
            first_location[a[i]] = i;
        }

        // printf("%d:0%X:%d\n", i, i, a[i]);
    }

    int max = 0;

    for (i = 1; i <= 400000; ++i) {
        printf("%d,", first_location[i]);
        if(i%50 == 0)puts("");
    }
}
int old()
{
    int range = 643122094;
    //int range = 643122093;
    //int range = 1000000000;
    int* a = new int[range];
    int* first_location = new int[range];
    memset(first_location, 0, range * sizeof(int));
    int i;
    a[1] = 1;

    for (i = 2; i < range; ++i) {
        if (i & 1) {
            a[i] = a[i / 2] + a[i / 2 + 1];
        } else {
            a[i] = a[i / 2];
        }
    }

    for (i = 1; i < range; ++i) {
        if (first_location[a[i]] == 0) {
            first_location[a[i]] = i;
        }

        // printf("%d:0%X:%d\n", i, i, a[i]);
    }

    int max = 0;

    for (i = 1; i < range; ++i) {
        if (first_location[i] != 0) {
            printf("first location i=0X%X:%d location=0X%X:%d\n", i, i, first_location[i], first_location[i]);
            printf("[loc:%d][a1:%d a2:%d][location=0X%X:%d]\n", first_location[i] / 2, a[first_location[i] / 2], a[first_location[i] / 2 + 1], first_location[i], first_location[i]);
        }
    }
}
