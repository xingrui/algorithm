// reorder an array, so that odd number is on left, and event number is on right.
#include <stdio.h>

void swap(int* p, int* q)
{
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

int reorder(int* array, int length)
{
    int i = 0, j = length - 1;

    while (i < j) {
        while (i < j && array[i] % 2 == 1) {
            ++i;
        }

        while (j > i && array[j] % 2 == 0) {
            --j;
        }

        if (i < j) {
            swap(array + i, array + j);
        }
    }

    return 0;
}

int main()
{
    int array[10] = {2, 4, 6, 1, 3, 5, 0, 7, 9, 8};
    int length = sizeof(array) / sizeof(int);
    int i = 0;
    reorder(array, length);

    for (i = 0; i < length; ++i) {
        printf("%d\t", array[i]);
    }

    return 0;
}
