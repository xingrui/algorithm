#include<iostream>
#include<cstdio>
using namespace std;
const int PRIME_NUM = 7;
class Matrix {
public:
    long long x1;
    long long x2;
    long long y1;
    long long y2;
public:
    Matrix(long long a, long long b, long long c, long long d) :
        x1(a), x2(b), y1(c), y2(d) {}
    Matrix& operator*=(const Matrix& obj) {
        long long t_x1 = x1 * obj.x1 + x2 * obj.y1;
        long long t_x2 = x1 * obj.x2 + x2 * obj.y2;
        long long t_y1 = y1 * obj.x1 + y2 * obj.y1;
        long long t_y2 = y1 * obj.x2 + y2 * obj.y2;
        this->x1 = t_x1 % PRIME_NUM;
        this->x2 = t_x2 % PRIME_NUM;
        this->y1 = t_y1 % PRIME_NUM;
        this->y2 = t_y2 % PRIME_NUM;
        return *this;
    }
    static const Matrix IDENTITY;
};
const Matrix Matrix::IDENTITY = Matrix(1, 0, 0, 1);
Matrix MatrixPow(const Matrix& m, long long n)
{
    Matrix result = Matrix::IDENTITY;
    Matrix tmp = m;

    for (; n; n >>= 1) {
        if (n & 1) {
            result *= tmp;
        }

        tmp *= tmp;
    }

    return result;
}
int main()
{
    char buffer[100];

    while (fgets(buffer, 100, stdin)) {
        long long a, b, n;
        sscanf(buffer, "%ld%ld%ld", &a, &b, &n);

        if ((a | b | n) == 0) {
            break;
        }

        if (n < 3) {
            puts("1");
            continue;
        }

        Matrix matrix(a, b, 1, 0);
        Matrix an = MatrixPow(matrix, n - 2);
        printf("%ld\n", (an.x1 + an.x2) % PRIME_NUM);
    }

    return 0;
}
