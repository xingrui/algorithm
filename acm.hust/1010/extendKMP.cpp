#include<cstdio>
#include<cstring>
void printArray(const char* name, int* array, int length)
{
    int i;
    puts(name);

    for (i = 0; i < length; ++i)
        printf("%d ", array[i]);

    puts("");
}

void extendKMPNext(const char* pattern, int* next, int length)
{
    int matchedIndex = 0;
    int index;

    while (matchedIndex + 1 < length && pattern[matchedIndex]
            == pattern[matchedIndex + 1])
        ++matchedIndex;

    next[0] = 0;
    next[1] = matchedIndex;
    int sumMaxIndex = 1;
    int maxSearchLength;

    for (index = 2; index < length; ++index) {
        maxSearchLength = sumMaxIndex + next[sumMaxIndex];

        if (next[index - sumMaxIndex] + index < maxSearchLength)
            next[index] = next[index - sumMaxIndex];
        else {
            matchedIndex = (0 > maxSearchLength - index) ? 0 : maxSearchLength
                    - index;

            while (index + matchedIndex < length && pattern[matchedIndex]
                    == pattern[index + matchedIndex])
                ++matchedIndex;

            next[index] = matchedIndex;
            sumMaxIndex = index;
        }
    }
}

int main()
{
    char buffer[1000002];
    int extend[1000002];

    while (fgets(buffer, 1000002, stdin)) {
        int len = strlen(buffer);
        --len;

        if (0 == len) {
            printf("%d\n", 0);
        }

        int i;
        extendKMPNext(buffer, extend, len);

        for (i = 1; i < len; ++i) {
            if (i + extend[i] == len) {
                break;
            }
        }

        printf("%d\n", i);
    }

    return 0;
}
