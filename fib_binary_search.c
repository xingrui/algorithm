#include <stdio.h>
#include <stdlib.h>

int array[] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610,
                987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393,
                196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887,
                9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141,
                267914296, 433494437, 701408733, 1134903170, 1836311903,
              };

int search_repeat_first(int* array, int length, int num)
{
    int low = -1;
    int high = length;

    while (high - low > 1) {
        int range_length = high - low;
        int probe = low + range_length / 2;

        if (array[probe] < num) {
            low = probe;
        } else {
            high = probe;
        }
    }

    if (low < length && array[low + 1] == num) {
        printf("found: index = %d\n", low + 1);
    } else {
        printf("not found: index(largest number not greater than input num) = %d \n", low);
        printf("not found: index(least number greater than input num) = %d \n", low + 1);
    }

    return 0;
}

int search_repeat_last(int* array, int length, int num)
{
    int low = -1;
    int high = length;

    while (high - low > 1) {
        int length = high - low;
        int probe = low + length / 2;

        if (array[probe] > num) {
            high = probe;
        } else {
            low = probe;
        }
    }

    if (low != -1 && array[low] == num) {
        printf("found: index = %d\n", low);
    } else {
        printf("not found: index(largest number not greater than input num) = %d \n", low);
        printf("not found: index(least number greater than input num) = %d \n", low + 1);
    }

    return 0;
}

int main(void)
{
    int num;

    while (scanf("%d", &num) != -1) {
        if (num < 0) {
            printf("%d\n", -1);
        } else {
            search_repeat_first(array, sizeof(array) / sizeof(int), num);
            search_repeat_last(array, sizeof(array) / sizeof(int), num);
        }

        fflush(stdout);
    }

    return EXIT_SUCCESS;
}
