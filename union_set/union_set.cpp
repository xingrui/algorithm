#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define HASLOG
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
int test_case1()
{
    JoinSet set(100);
    set.print();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            set.join(i * 10 + j, i * 10 + j + 1);
        }
    }

    for (int i = 0; i < 10; ++i) {
        set.join(i * 10, (i + 1) * 10);
    }

    set.print();
    set.find_root(0);
    set.print();

    for (int i = 0; i < 100; ++i) {
        LOG("i:%d root:%d\n", i, set.find_root(i));
    }

    set.print();
    return 0;
}
int test_case2()
{
    JoinSet set(100);
    set.print();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            set.join(i * 10 + j, i * 10 + j + 1);
        }
    }

    set.print();
    set.find_root(0);
    set.print();

    for (int i = 0; i < 100; ++i) {
        LOG("i:%d root:%d\n", i, set.find_root(i));
    }

    set.print();
    return 0;
}
int test_case3()
{
    int set_size = 1000000;
    JoinSet set(set_size);
    set.print();

    for (int i = 0; i < set_size; ++i) {
        set.join(i + 1, i);
    }

    set.print();
    set.find_root(0);
    set.print();

    for (int i = 0; i < set_size; ++i) {
        LOG("i:%d root:%d\n", i, set.find_root(i));
    }

    set.print();
    return 0;
}
int main(void)
{
    test_case2();
    return 0;
}

