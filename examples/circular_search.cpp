// 从小到大排序的一个循环数组，比如 9,1,2,3,4,5,6,7,8
// 从里面查找某个数字是否存在
#include <iostream>
#include <cstdio>

bool circular_search(int* array, int length, int num) {
    if (length == 0) return false;
    if (length == 1) return array[0] == num;
    int middle = length / 2 - 1;
    if (array[middle] == num) return true;
    //printf("middle:%d array[middle]:%d length:%d\n", middle, array[middle], length);
    bool in_left_part = true;
    if (array[0] <= array[middle]) {
        // 左半部分有序
        if (array[0] > num || array[middle] < num) {
            in_left_part = false;
        } else {
            in_left_part = true;
        }
    } else {
        // 右半部分有序
        if (array[middle] > num || array[length - 1] < num) {
            in_left_part = true;
        } else {
            in_left_part = false;
        }
    }
    if (in_left_part) {
        return circular_search(array, length / 2, num);
    } else {
        return circular_search(array + length / 2, length - length / 2, num);
    }
}

int main() {
    int array[] = {8,9,1,3,5,7};
    int length = sizeof(array) / sizeof(int);
    circular_search(array, length, 9);
    for (int i = 0; i < 11; ++i) {
        std::cout << i << " " << circular_search(array, length, i) << std::endl;
    }
}
