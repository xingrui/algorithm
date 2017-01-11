/*
 * https://en.wikipedia.org/wiki/Find_first_set
 * an important function : ffs
 * using hardware instruction to compute __builtin_clz
 */

/*
 * __builtin_ffs
 * __builtin_clz
 * __builtin_ctz
 * __builtin_ctzl
 * __builtin_ctzll
 */

#include <strings.h>
#include<iostream>
#include<cstdio>
#include<stdint.h>
#include<cmath>
#include<algorithm>
#include <sys/time.h>

inline uint64_t timediff_us(const struct timeval& s, const struct timeval& e)
{
    /*{{{*/
    uint64_t start = s.tv_sec * 1000000L + s.tv_usec;
    uint64_t end = e.tv_sec * 1000000L + e.tv_usec;
    return (end > start) ? (end - start) : 0;
    // FOLLOW OLD CODE WILL HAVE BUG.
    // If e.tv_usec < s.tv_usec then (e.tv_usec - s.tv_usec) will be minus number.
    // and will change to very big number because the first number is a unsigned int number.
    // return (e.tv_sec - s.tv_sec) * total_count0UL + (e.tv_usec - s.tv_usec);
}/*}}}*/

#define START_COUNT_TIME(proc_name) \
    timeval time_start_##proc_name = {0, 0}; \
    timeval time_end_##proc_name = {0, 0}; \
    gettimeofday(&time_start_##proc_name, NULL)

#define END_COUNT_TIME(proc_name) \
    {gettimeofday(&time_end_##proc_name, NULL); \
        uint64_t time_##proc_name = timediff_us(time_start_##proc_name, time_end_##proc_name);\
        std::cout << #proc_name << ":" << time_##proc_name << "us" << std::endl;}

int f1(unsigned int x)
{
    int n = 1;

    // if(x==0) return -1;
    if ((x >> 16) == 0) {
        n += 16;
        x <<= 16;
    }

    if ((x >> 24) == 0) {
        n += 8;
        x <<= 8;
    }

    if ((x >> 28) == 0) {
        n += 4;
        x <<= 4;
    }

    if ((x >> 30) == 0) {
        n += 2;
        x <<= 2;
    }

    n = n - (x >> 31);
    return 31 - n;
}

int f2(unsigned int x)
{
    return 31 - __builtin_clz(x);
}

int f3(unsigned int x)
{
    return int(trunc(log2(x)));
}

int main()
{
    int total_count = 10000000;
    START_COUNT_TIME(f1);

    for (int i = 0; i < total_count; ++i) {
        f1(i);
    }

    END_COUNT_TIME(f1);
    START_COUNT_TIME(f2);

    for (int i = 0; i < total_count; ++i) {
        f2(i);
    }

    END_COUNT_TIME(f2);
    START_COUNT_TIME(f3);

    for (int i = 0; i < total_count; ++i) {
        f3(i);
    }

    END_COUNT_TIME(f3);

    for (int i = 0; i < total_count; ++i) {
        int n1 = f1(i);
        int n2 = f1(i);
        int n3 = f1(i);

        if (n1 != n2 || n1 != n3) {
            printf("ERROR\n");
        }
    }

}

