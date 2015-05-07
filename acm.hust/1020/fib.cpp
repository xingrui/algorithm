#include<iostream>
using namespace std;
int main()
{
    int array[100] = {0};
    array[0] = 1;
    array[1] = 1;

    for (int i = 0; i < 100; ++i) {
        array[i + 2] = array[i] + array[i + 1];
        printf("[%d:%d]:%d:%d\n", 1 << (i + 1), 3 << i, i + 2, array[i + 2]);

        if (array[i + 2] >= 1000000) {
            break;
        }
    }

    return 0;
}
