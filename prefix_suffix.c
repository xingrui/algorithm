void extendKMPNext(const char* pattern, int* next, int length)
{
    int matchedIndex = 0;
    int index;

    while (matchedIndex + 1 < length && pattern[matchedIndex] == pattern[matchedIndex + 1])
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
            matchedIndex = (0 > maxSearchLength - index) ? 0 : maxSearchLength - index;

            while (index + matchedIndex < length && pattern[matchedIndex] == pattern[index + matchedIndex])
                ++matchedIndex;

            next[index] = matchedIndex;
            sumMaxIndex = index;
        }
    }
}

int extendKMP(const char* S, int lenS, const char* T, int lenT, int* extend)
{
    int* next = malloc(lenT * sizeof(int));
    int index;
    extendKMPNext(T, next, lenT);

    int matchedIndex = 0;
    int minLen = lenS < lenT ? lenS : lenT;

    while (matchedIndex < minLen && T[matchedIndex] == S[matchedIndex])
        ++matchedIndex;

    extend[0] = matchedIndex;
    int sumMaxIndex = 0;
    int maxSearchLength;

    for (index = 1; index < lenS; ++index) {
        maxSearchLength = sumMaxIndex + extend[sumMaxIndex];

        if (next[index - sumMaxIndex] + index < maxSearchLength)
            extend[index] = next[index - sumMaxIndex];
        else {
            matchedIndex = (0 > maxSearchLength - index) ? 0 : maxSearchLength - index;

            while (index + matchedIndex < lenS && matchedIndex < lenT
                    && T[matchedIndex] == S[index + matchedIndex])
                ++matchedIndex;

            extend[index] = matchedIndex;
            sumMaxIndex = index;
        }
    }

    free(next);
    return 0;
}

int main()
{
    //char* prefix_string = "abababababcababababab";
    //char* suffix_string = "ababababababababababc";
    char* prefix_string = "ababababababababababa";
    char* suffix_string = "ababababababababababa";
    //char* prefix_string = "654321123456";
    //char* suffix_string = "123456654321";
    int index = 0;
    char* T = prefix_string;
    char* S = suffix_string;
    int lenS = strlen(S);
    int lenT = strlen(T);
    int* extend = malloc(lenS * sizeof(int));
    extendKMP(S, strlen(S), T, strlen(T), extend);

    for (index = 0; index < lenS; ++index) {
        if (index + extend[index] == lenS) {
            printf("found string : %s\n", suffix_string + index);
        }
    }

    if (index == lenS) {
        puts("empty string found.");
    }

    return 0;
}
