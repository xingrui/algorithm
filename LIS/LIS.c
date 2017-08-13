#include<stdio.h>
#include<stdlib.h>

int binary_search(int* array, int length, int num) {
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

int LIS(int*array, int length) {
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
        printf("search_res of array[%d]=%d is %d:\n", i, current_num, search_res);
    }
    return current_length;
}

int test_binary_search(){
    int array[] = {0,1,2,3,4,5,6,7,8,9,10};
    int length = sizeof(array) / sizeof(int);
    int i = 0;
    for (i = -1; i <= length + 2; ++i) {
        int loc = binary_search(array, length, i); 
        printf("location of %d is %d\n", i, loc);
    }
    return 0;
}

int main(){
    // int array[] = {100, 0, 1, 2, 1000, 2000, 3, 4, 5, 6, 7, 8};
    int array[] = {1, -1, 2, -3, 4, -5, 6, -7};
    int length = sizeof(array) / sizeof(int);
    int lis_len = LIS(array, length);
    printf("LIS len res = %d\n", lis_len);
    return 0;
}
