#include<sys/time.h>
#include<stdint.h>
#include<string>
#include<iostream>

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

void trim(std::string& s)
{
    int index = 0;

    if (!s.empty()) {
        while ((index = s.find(' ', index)) != std::string::npos) {
            s.erase(index, 1);
        }
    }

}

void trim1(std::string& s)
{
    size_t length = s.length();
    size_t j = 0;

    for (size_t i = 0; i < length; ++i) {
        if (s[i] != ' ') {
            s[j++] = s[i];
        }
    }

    s.erase(j);
}

int main()
{

    const int TIMES = 1000000;
    const std::string str = "    1   2   3   4   5   6    ";
    {
        std::string a(str);
        trim(a);
        std::cout << a << ":" << a.length() << std::endl;
    }
    {
        std::string a(str);
        trim1(a);
        std::cout << a << ":" << a.length() << std::endl;
    }
    START_COUNT_TIME(trim);

    for (int i = 0; i < TIMES; ++i) {
        std::string a(str);
        trim(a);
    }

    END_COUNT_TIME(trim);
    START_COUNT_TIME(trim1);

    for (int i = 0; i < TIMES; ++i) {
        std::string a(str);
        trim1(a);
    }

    END_COUNT_TIME(trim1);
}
