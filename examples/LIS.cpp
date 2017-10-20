#include<stdio.h>
#include<stdlib.h>

int binary_search(int* array, int length, int num)
{
    int low = -1;
    int high = length;

    while (high - low > 1) {
        int len = high - low;
        int mid = low + len / 2;

        if (array[mid] < num) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return low + 1;
}

int LIS_without_print(int* array, int length)
{
    int* tmp_array = (int*)malloc(length * sizeof(int));
    int current_length = 0;
    int i = 0;

    for (i = 0; i < length; ++i) {
        int current_num = array[i];
        int search_res = binary_search(tmp_array, current_length, current_num);
        tmp_array[search_res] = array[i];

        if (search_res == current_length) {
            ++current_length;
        }
    }

    free(tmp_array);
    return current_length;
}

int LIS_with_print(int* array, int length)
{
    int* tmp_array = (int*)malloc(length * sizeof(int));
    int* mid_res_array = (int*)malloc(length * sizeof(int) * 3);
    int current_length = 0;
    int i = 0;

    for (i = 0; i < length; ++i) {
        int current_num = array[i];
        int search_res = binary_search(tmp_array, current_length, current_num);
        tmp_array[search_res] = array[i];
        int pre_data = search_res == 0 ? 0 : (tmp_array[search_res - 1]);
        mid_res_array[i * 3] = search_res;
        mid_res_array[i * 3 + 1] = array[i];
        mid_res_array[i * 3 + 2] = pre_data;

        if (search_res == current_length) {
            ++current_length;
        }
    }

    int to_find_index = current_length - 1;
    int to_find_data = tmp_array[to_find_index];

    for (i = length - 1; i >= 0; --i) {
        int index = mid_res_array[i * 3];
        int cur_data = mid_res_array[i * 3 + 1];
        int pre_data = mid_res_array[i * 3 + 2];

        if (index == to_find_index && cur_data == to_find_data) {
            printf("%d\t", cur_data);
            --to_find_index;
            to_find_data = pre_data;
        }
    }

    printf("\n");
    free(tmp_array);
    free(mid_res_array);
    return current_length;
}

int LIS_normal(int* array, int length)
{
    int ret_len = 0;
    int* tmp = (int*)malloc(length * sizeof(int));
    int i, j;

    for (i = 0; i < length; ++i) {
        int max_len = 1;

        for (j = 0; j < i; ++j) {
            if (array[i] > array[j] && max_len < (tmp[j] + 1)) {
                max_len = tmp[j] + 1;
            }
        }

        tmp[i] = max_len;
    }

    for (i = 0; i < length; ++i) {
        if (tmp[i] > ret_len) {
            ret_len = tmp[i];
        }
    }

    free(tmp);
    return ret_len;
}

int test_binary_search()
{
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(array) / sizeof(int);
    int i = 0;

    for (i = -1; i <= length + 2; ++i) {
        int loc = binary_search(array, length, i);
        printf("location of %d is %d\n", i, loc);
    }

    return 0;
}

int main()
{
    // int array[] = {100, 0, 1, 2, 1000, 2000, 3, 4, 5, 6, 7, 8};
    int array[] = {1, -1, 2, -3, 4, -5, 6, -7, -1, 2, -3, 4, -5, 6, -7};
    int length = sizeof(array) / sizeof(int);
    int lis_len = LIS_without_print(array, length);
    printf("LIS len res = %d\n", lis_len);
    lis_len = LIS_normal(array, length);
    printf("LIS len res = %d\n", lis_len);
    return 0;
}
