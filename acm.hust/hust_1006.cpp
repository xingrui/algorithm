#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

//#define HASLOG
#ifdef HASLOG
#define LOG(_fmt_, args...) \
    do\
    {\
        printf("[%s][%d][%s]"_fmt_, __FILE__, __LINE__, __FUNCTION__, ##args);\
    } while (0)
#else
#define LOG(_fmt_, args...) do {} while (0)
#endif

using namespace std;
int a[] = {14, 10, 56, 7, 83, 22, 36, 91, 3, 47, 72, 0};
int test()
{
    priority_queue<int>que;
    int i;

    for (i = 0; a[i]; i++) {
        que.push(a[i]);
    }

    while (!que.empty()) {
        printf("%3d", que.top());
        que.pop();
    }

    puts("");
    return 0;
}

int main()
{
    int T = 0;
    scanf("%d", &T);
    LOG("T:%d\n", T);

    while (T-- > 0) {
        int stone_num = 0;
        scanf("%d", &stone_num);
        LOG("stone_num:%d\n", stone_num);
        std::vector<priority_queue<int> >total_vect(150000);
        int max_stone_distance = 0;

        while (stone_num-- > 0) {
            int location;
            int distance;
            scanf("%d %d", &location, &distance);
            LOG("loc:%d dis:%d\n", location, distance);
            total_vect[location].push(-distance);

            if (location > max_stone_distance) {
                max_stone_distance = location;
            }
        }

        int flag = 1;

        for (int i = 0; i <= max_stone_distance; ++i) {
            LOG("i:%d size:%d\n", i , total_vect[i].size());

            while (!total_vect[i].empty()) {
                if (flag) {
                    int e = total_vect[i].top();
                    total_vect[i - e].push(e);

                    if (max_stone_distance < i - e) {
                        max_stone_distance = i - e;
                    }
                }

                total_vect[i].pop();
                flag = 1 - flag;
            }
        }

        printf("%d\n", max_stone_distance);
    }

    return 0;
}
