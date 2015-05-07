// http://acm.hust.edu.cn/problem.php?id=1301
// N point count
// K light range
// (1<=N<=1000 1<=K<2^31)
// (-10^8<=Xi,Yi<=10^8)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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
struct point {
    int x;
    int y;
};
const double INF = 1e20;
void print_array(int* array, int len)
{
    char buffer[100000];
    char* tmp = buffer;
    int i;

    for (i = 0; i < len; ++i) {
        int print_len = snprintf(tmp, 1000, "%d,", array[i]);
        tmp += print_len;
    }

    LOG("%s", buffer);
}
int judge_distance(struct point* p1, struct point* p2)
{
    int dx = p1->x - p2->x;
    int dy = p1->y - p2->y;
    return abs(dx) + abs(dy);
}
double calc_distance(struct point* p1, struct point* p2, int light_range)
{
    if (judge_distance(p1, p2) > light_range)
        return INF;

    long long dx = p1->x - p2->x;
    long long dy = p1->y - p2->y;
    return sqrt(dx * dx + dy * dy);
}
int find_root(int* join_set, int i)
{
    int query_id = i;
    LOG("<<<<<<< i:%d join_set[i]:%d\n", i, join_set[i]);

    while (join_set[query_id] >= 0) {
        LOG("******* query_id:%d join_set:%d\n", query_id, join_set[query_id]);
        int next_id = join_set[query_id];

        if (join_set[next_id] >= 0) {
            join_set[query_id] = join_set[next_id];
            query_id = next_id;
        } else {
            query_id = next_id;
            break;
        }
    }

    LOG("<<<<<<< i:%d root:%d\n", i, query_id);
    return query_id;
}
void join(int* join_set, int i, int j)
{
    int i_root = find_root(join_set, i);
    int j_root = find_root(join_set, j);
    if (i_root == j_root) {
        return;
    }

    LOG("i:%d j:%d join_set[i]:%d join_set[j]:%d\n", i, j, join_set[i], join_set[j]);

    if (join_set[i] < 0) {
        join_set[i] = j_root;
    } else if (join_set[j] < 0) {
        join_set[j] = i_root;
    } else {
        join_set[j_root] = i_root;
    }

    LOG("i:%d j:%d join_set[i]:%d join_set[j]:%d\n", i, j, join_set[i], join_set[j]);
}
double get_sub_min_distance(
    struct point* points,
    int dest_point_count,
    int* dest_point_index,
    int point_count,
    int light_range
)
{
    int i;
    char tmp_join_set[point_count];
    double low_cost[point_count];
    memset(tmp_join_set, 0, point_count);

    for (i = 0; i < point_count; ++i) {
        low_cost[i] = INF;
    }

    int num = 0;
    int e = dest_point_index[0];
    tmp_join_set[e] = 1;
    double distance = 0;

    while (++num < dest_point_count) {
        double min_distance = INF;
        int min_edge = -1;
        int idx;

        for (idx = 0; idx < dest_point_count; ++idx) {
            int i = dest_point_index[idx];

            if (tmp_join_set[i]) {
                continue;
            }

            double cur_cost = calc_distance(points + i,
                    points + e, light_range);

            if (cur_cost < low_cost[i]) {
                low_cost[i] = cur_cost;
            }

            if (low_cost[i] < min_distance) {
                min_edge = i;
                min_distance = low_cost[i];
            }

            LOG("i=%d e=%d low_cost:%lf\n", i, e, low_cost[i]);
        }

        distance += min_distance;
        e = min_edge;
        tmp_join_set[e] = 1;
        LOG("%d cur distance:%lf\n", e, distance);
        //++num;
    }

    return distance;
}
double get_min_distance(struct point* points, int point_count, int light_range)
{
    int join_set[point_count];
    int i, j;
    LOG("%d %d\n", point_count, light_range);

    for (i = 0; i < point_count; ++i) {
        LOG("%d %d\n", points[i].x, points[i].y);
        join_set[i] = -1;
    }

    for (i = 0; i < point_count; ++i) {
        for (j = 0; j < i; ++j) {
            int distance = judge_distance(points + i, points + j);
            //LOG("i=%d j=%d distance=%d calc_distance = %lf\n", i, j, distance,
            //    calc_distance(points + i, points + j));

            if (distance <= light_range) {
                join(join_set, i, j);
            }
        }
    }

    int root_count = 0;
    int roots[point_count];

    for (i = 0; i < point_count; ++i) {
        if (join_set[i] < 0) {
            roots[root_count] = i;
            ++root_count;
        } else {
            --join_set[find_root(join_set, i)];
        }
    }

    int max_leaf_count = 0;

    for (i = 0; i < root_count; ++i) {
        LOG("%d leaf_count:%d\n", roots[i], -join_set[roots[i]]);

        if (-join_set[roots[i]] > max_leaf_count) {
            max_leaf_count = -join_set[roots[i]];
        }
    }

    int root_index;
    double min_distance = INF;

    for (root_index = 0; root_index < root_count; ++root_index) {
        if (-join_set[roots[root_index]] != max_leaf_count) {
            continue;
        }

        int dest_point_index[point_count];
        int dest_point_count = 0;

        for (i = 0; i < point_count; ++i) {
            if (find_root(join_set, i) == roots[root_index]) {
                dest_point_index[dest_point_count] = i;
                ++dest_point_count;
            }
        }

        double distance = get_sub_min_distance(
                points,
                dest_point_count,
                dest_point_index,
                point_count,
                light_range);

        if (min_distance > distance) {
            min_distance = distance;
        }
    }

    printf("%d %.2f\n", max_leaf_count, min_distance);
    return min_distance;
}
int main(void)
{
    int test_case_num;
    int i;
    char buffer[100];
    struct point points[1000];
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d", &test_case_num);

    for (i = 0; i < test_case_num; ++i) {
        int N, K;
        int j;
        fgets(buffer, 100, stdin);
        sscanf(buffer, "%d %d", &N, &K);
        LOG("iiiiiiiiiiiiiiiiiiiiiiii N=%d K=%d\n", N, K);

        for (j = 0; j < N; ++j) {
            fgets(buffer, 100, stdin);
            sscanf(buffer, "%d %d", &points[j].x, &points[j].y);
        }

        get_min_distance(points, N, K);
    }

    return 0;
}
