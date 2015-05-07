#include <iostream>
#include <cstdio>
using namespace std;
long long get_value(long long input)
{
    if (input == 0 || input == 1)
        return input;

    int k = 0; //k<60
    long long l = 4;

    while (l < input) {
        ++k;
        l <<= 1;
    }

    l >>= 1;
    long long pos = input - l;
    long long len = l + 1;

    if (pos > (len / 2)) pos = len - pos - 1;

    if (pos == 0) {
        return 1;
    }

    long long vall, valr, posl, posr;
    vall = valr = 1;
    posl = 0;
    posr = len - 1;
    long long bpos = len / 2;
    long long bval = vall + valr;

    while (bpos != pos) {
        if (pos < bpos) {
            valr = bval;
            posr = bpos;
        } else if (pos > bpos) {
            vall = bval;
            posl = bpos;
        }

        bpos = (posl + posr) / 2;
        bval = vall + valr;
    }

    return bval;
}
int main()
{
    long long n;
    char buffer[30];

    while (fgets(buffer, 30, stdin)) {
        sscanf(buffer, "%lld", &n);
        long long output = get_value(n);
        printf("%lld\n", output);
    }

    return 0;
}
