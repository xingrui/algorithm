#include<iostream>
using namespace std;
int main()
{
    int range = 1 << 14;
    int array[100] = {0};
    array[0] = 1;
    array[1] = 1;
    int i;

    for (i = 0; i < 100; ++i) {
        array[i + 2] = array[i] + array[i + 1];
        printf("%d\n", array[i]);

        if (array[i + 2] >= 1000000) {
            break;
        }
    }

    int* a = new int[range];
    int* first_location = new int [range];
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
    }

    return 0;
}
