// 从小到大排序的一个循环数组，比如 9,1,2,3,4,5,6,7,8
// 从里面查找某个数字是否存在
#include <iostream>
#include <cstdio>

bool binary_search(int *array, int length, int num) {
    int low = -1;
    int high = length;
    while (high - low > 1) {
        int rlen = high - low;
        int probe = low + rlen / 2;
        if (array[probe] < num) {
            low = probe;
        } else {
            high = probe;
        }
    }
    return high != length && array[high] == num;
}

bool circular_search(int* array, int length, int num) {
    if (length <= 0) return false;
    if (length == 1) return array[0] == num;
    int middle = length / 2 - 1;
    if (array[middle] == num) return true;
    //printf("middle:%d array[middle]:%d length:%d\n", middle, array[middle], length);
    if (array[0] <= array[middle]) {
        // 左半部分有序
        if (array[0] > num || array[middle] < num) {
            return circular_search(array + length / 2, length - length / 2, num);
        } else {
            return binary_search(array, length / 2, num);
        }
    } else {
        // 右半部分有序
        if (array[middle] > num || array[length - 1] < num) {
            return circular_search(array, length / 2, num);
        } else {
            return binary_search(array + length / 2, length - length / 2, num);
        }
    }
}

int main() {
    int array[] = {8,9,1,3,5,7};
    int length = sizeof(array) / sizeof(int);
    for (int i = 0; i < 11; ++i) {
        std::cout << i << " " << circular_search(array, length, i) << std::endl;
    }
}
