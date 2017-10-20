#include <stdio.h>
#include <stdlib.h>

int count(int num) {
    int i = 0;
    while(num) {
        num &= (num - 1);
        ++i;
    }
    return i;
}

int main() {
    int i;
    for(i = 0; i < 100; ++i) {
        printf("i=%d count_i=%d\n", i, count(i));
    }
    return 0;
}
