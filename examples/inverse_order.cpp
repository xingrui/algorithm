#include <cstdio>
#include <cstdlib>

int merge(int* a, int left, int middle, int right, int* aid_array)
{
    int i = left, j = middle, k = left;

    while (i < middle && j < right) {
        if (a[i] < a[j]) {
            aid_array[k++] = a[i++];
        } else {
            aid_array[k++] = a[j++];
        }
    }

    while (i < middle) {
        aid_array[k++] = a[i++];
    }

    while (j < middle) {
        aid_array[k++] = a[j++];
    }

    for (int i = left; i < right; ++i) {
        a[i] = aid_array[i];
    }

    return 0;
}

// compute inverse between left and right.[left, right)
int count_inverse(int* a, int left, int right, int* aid_array)
{
    if (right - left <= 1) {
        return 0;
    }

    int length = right - left;
    int middle = left + length / 2;
    int count1 = count_inverse(a, left, middle, aid_array);
    int count2 = count_inverse(a, middle, right, aid_array);
    int i = left, j = middle;
    int count3 = 0;

    while (true) {
        if (a[i] <= a[j]) {
            if (++i == middle) break;
        } else if (a[i] > a[j]) {
            count3 += middle - i;

            if (++j == right) break;
        }
    }

    // sort(a + left, a + right);
    merge(a, left, middle, right, aid_array);
    return count1 + count2 + count3;
}

int main()
{
    // int array[] = {5, 4, 3, 2, 1, 0, -1};
    int array[] = {7, 1, 2, 3, 4, 5, 6, 7, 7, 7,};
    int length = sizeof(array) / sizeof(int);
    int* aid_array = new int[length];
    int count = count_inverse(array, 0, length, aid_array);
    delete[] aid_array;
    printf("res=%d\n", count);
    return 0;
}
