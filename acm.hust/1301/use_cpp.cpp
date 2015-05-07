// http://acm.hust.edu.cn/problem.php?id=1301
// N point count
// K light range
// (1<=N<=1000 1<=K<2^31)
// (-10^8<=Xi,Yi<=10^8)
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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

void print_array(int* array, int len)
{
    char* buffer = new char[len * 20];
    char* tmp = buffer;
    int i;

    for (i = 0; i < len; ++i) {
        int print_len = snprintf(tmp, 1000, "%d,", array[i]);
        tmp += print_len;

        if (i % 100 == 0) {
            *tmp++ = '\n';
        }
    }

    LOG("%s\n", buffer);
    delete[] buffer;
}

class JoinSet {
public:
    JoinSet(int set_size) : m_set_size(set_size) {
        m_join_set = new int[m_set_size];
        m_rank = new int[m_set_size];

        for (int i = 0; i < m_set_size; ++i) {
            m_join_set[i] = i;
        }

        memset(m_rank, 0, m_set_size * sizeof(int));
    }
    ~JoinSet() {
        delete[] m_join_set;
        delete[] m_rank;
        m_set_size = 0;
    }
    int find_root(int i);
    int join(int i, int j);
    void print() {
        print_array(m_join_set, m_set_size);
        print_array(m_rank, m_set_size);
    }
private:
    JoinSet(const JoinSet&);
    JoinSet& operator=(const JoinSet&);
private:
    int* m_join_set;
    int* m_rank;
    int m_set_size;
};
int JoinSet::find_root(int i)
{
    while (i != m_join_set[i]) {
        int parent = m_join_set[i];
        m_join_set[i] = m_join_set[parent];
        i = parent;
    }

    return i;
}
int JoinSet::join(int i, int j)
{
    if (i < 0 || j < 0 || i >= m_set_size || j >= m_set_size) {
        return -1;
    }

    int i_root = find_root(i);
    int j_root = find_root(j);

    if (i_root == j_root) {
        return 0;
    }

    LOG("i:%d j:%d m_join_set[i]:%d m_join_set[j]:%d\n", i, j, m_join_set[i], m_join_set[j]);

    if (m_rank[i_root] < m_rank[j_root]) {
        m_join_set[i_root] = j_root;
    } else {
        m_join_set[j_root] = i_root;

        if (m_rank[i_root] == m_rank[j_root]) {
            ++m_rank[i_root];
        }
    }

    LOG("i:%d j:%d m_join_set[i]:%d m_join_set[j]:%d\n", i, j, m_join_set[i], m_join_set[j]);
    return 0;
}
struct point {
    int x;
    int y;
};
const double INF = 1e20;
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
double get_sub_min_distance(
    struct point* points,
    int dest_point_count,
    int* dest_point_index,
    int point_count,
    int light_range
)
{
    int i;
    char point_is_added[point_count];
    double low_cost[point_count];
    memset(point_is_added, 0, point_count);

    for (i = 0; i < point_count; ++i) {
        low_cost[i] = INF;
    }

    int num = 0;
    int e = dest_point_index[0];
    point_is_added[e] = 1;
    double distance = 0;

    while (++num < dest_point_count) {
        double min_distance = INF;
        int min_edge = -1;
        int idx;

        for (idx = 0; idx < dest_point_count; ++idx) {
            int i = dest_point_index[idx];

            if (point_is_added[i]) {
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
        point_is_added[e] = 1;
        LOG("%d cur distance:%lf\n", e, distance);
        //++num;
    }

    return distance;
}
double get_min_distance(struct point* points, int point_count, int light_range)
{
    JoinSet join_set(point_count);
    int i, j;
    LOG("%d %d\n", point_count, light_range);

    for (i = 0; i < point_count; ++i) {
        for (j = 0; j < i; ++j) {
            int distance = judge_distance(points + i, points + j);
            //LOG("i=%d j=%d distance=%d calc_distance = %lf\n", i, j, distance,
            //    calc_distance(points + i, points + j));

            if (distance <= light_range) {
                join_set.join(i, j);
            }
        }
    }

    int root_count = 0;
    int roots[point_count];
    int leaf_count[point_count];
    memset(leaf_count, 0, point_count * sizeof(int));

    for (i = 0; i < point_count; ++i) {
        int i_root = join_set.find_root(i);

        if (i_root == i) {
            roots[root_count] = i;
            ++root_count;
            ++leaf_count[i];
        } else {
            ++leaf_count[i_root];
        }
    }

    int max_leaf_count = 0;

    for (i = 0; i < root_count; ++i) {
        LOG("%d leaf_count:%d\n", roots[i], leaf_count[roots[i]]);

        if (leaf_count[roots[i]] > max_leaf_count) {
            max_leaf_count = leaf_count[roots[i]];
        }
    }

    int root_index;
    double min_distance = INF;

    for (root_index = 0; root_index < root_count; ++root_index) {
        if (leaf_count[roots[root_index]] != max_leaf_count) {
            continue;
        }

        int dest_point_index[point_count];
        int dest_point_count = 0;

        for (i = 0; i < point_count; ++i) {
            if (join_set.find_root(i) == roots[root_index]) {
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
