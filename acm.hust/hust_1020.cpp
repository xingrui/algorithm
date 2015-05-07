//http://acm.hust.edu.cn/problem/show/1020
#include<iostream>
#include<cstdio>
#include<cstring>
//#define DEBUG
using namespace std;
struct location {
    int depth;
    long long index;
};
int array[100] = {0};
int init()
{
    array[0] = 1;
    array[1] = 1;

    for (int i = 0; i < 100; ++i) {
        array[i + 2] = array[i] + array[i + 1];
    }

    return 0;
}
int search_value(long long left, long long right, long long value, int depth, location* p_loc)
{
    int max, min;

    if (left > right) {
        max = left;
        min = right;
    } else {
        max = right;
        min = left;
    }

    int max_value = array[depth] * max + array[depth - 1] * min;

    if (value > max_value) {
        return 1;
    }

#ifdef DEBUG
    printf("left:%llu right:%llu value:%llu, depth:%d\n", left, right, value, depth);
#endif
    // 1.judge possiblity first.
    // 2.search
    // depth control is caller's responsbility
    // only search one by one here.
    int tmp_array[(1 << depth) + 1];
    tmp_array[0] = left;
    tmp_array[1 << depth] = right;
    int cur_depth = 1;

    for (cur_depth = 1; cur_depth <= depth; ++cur_depth) {
        int base = 1 << (depth - cur_depth);

        for (int i = 0; i < (1 << (cur_depth - 1)); ++i) {
            int tmp_index = 2 * i + 1;
            tmp_array[tmp_index * base] = tmp_array[2 * i * base] + tmp_array[2 * (i + 1) * base];

            if (tmp_array[tmp_index * base] == value) {
                // return tmp_index + (1 << (cur_depth + input_depth));
                p_loc->depth = cur_depth;
                p_loc->index = tmp_index;
                return 0;
            }
        }
    }

    return 1;
}
int main()
{
    init();
    int base_bit = 20;
    int range = 1 << base_bit;
    int* a = new int[range];
    //const int RANGE = 400000;
    const int RANGE = 400000;
    int* least_num = new int[RANGE];
    memset(least_num, 0, RANGE * sizeof(int));

    int i;
    a[0] = 0;
    a[1] = 1;

    for (i = 2; i < range; ++i) {
        if (i & 1) {
            a[i] = a[i / 2] + a[i / 2 + 1];
        } else {
            a[i] = a[i / 2];
        }
    }

    for (i = 1; i < range; ++i) {
        if (a[i] < RANGE && least_num[a[i]] == 0) {
            least_num[a[i]] = i;
        }
    }

    for (i = 1; i < RANGE; ++i) {
        if (least_num[i] == 0) {
            break;
        }
    }

    char buffer[30];

    while (fgets(buffer, 30, stdin)) {
        int num;
        sscanf(buffer, "%d", &num);

        if (num < 0 || num >= RANGE) {
            fprintf(stderr, "input out of range\n");
            return 1;
        } else if (least_num[num] != 0) {
            printf("%d\n", least_num[num]);
        } else {
            // Search
            bool b_is_found = false;

            for (int depth = 1; depth < 16; ++depth) {
                for (int i = 1 << (base_bit - 1); i < (3 << (base_bit - 2)); ++i) {
                    location loc;
                    long long res = search_value(a[i], a[i + 1], num, depth, &loc);

                    if (res == 0) {
                        printf("%lld\n", (i << loc.depth) + loc.index);
                        b_is_found = true;
                        break;
                    }
                }

                if (b_is_found)break;
            }
        }
    }
	
	return 0;
}
