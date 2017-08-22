#include<iostream>
#include<cstring>
class RotateRect {
private:
    int m_row;
    int m_column;
    int* m_pData;
    RotateRect(const RotateRect&);
    RotateRect& operator=(const RotateRect&);
public:
    RotateRect(int row, int column): m_row(row), m_column(column), m_pData(NULL) {
        int size = m_row * m_column;
        m_pData = new int[size];
        memset(m_pData, 0, size * sizeof(int));
    }
    ~RotateRect() {
        delete[] m_pData;
        m_pData = NULL;
    }
    void printArray() const {
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_column; ++j) {
                std::cout << getData(i, j) << "\t";
            }
            std::cout << std::endl;
        }
    }
    int fillRect() {
        int i = 0, j = 0;
        // 0:> 1:V 2:< 3:^
        int direction = 0;
        for (int n = 1; n <= m_row * m_column; ++n) {
            setData(i, j, n);
            if (try_move(i, j, direction)) {continue;}
            direction = nextDirection(direction);
            if (try_move(i, j, direction)) {continue;}
            break;
        }
    }
private:
    int nextDirection(int direction) const {
        return (direction + 1) % 4;
    }
    int try_move(int& i, int& j, int direction) {
        int next_i, next_j;
        move(i, j, next_i, next_j, direction);
        if (checkValid(next_i, next_j)) {
            i = next_i;
            j = next_j;
            return 1;
        }
        return 0;
    }
    int move(int i, int j, int& res_i, int& res_j, int direction) const {
        int step_i[4] = {0, 1, 0, -1};
        int step_j[4] = {1, 0, -1 , 0};
        res_i = i + step_i[direction];
        res_j = j + step_j[direction];
    }
    bool checkValid(int i, int j) const {
        if (i < 0 || i >= m_row) {return false;}
        if (j < 0 || j >= m_column) {return false;}
        if (getData(i, j) != 0) {return false;}
        return true;
    }
    int getData(int i, int j) const {
        return m_pData[i * m_column + j];
    }
    int setData(int i, int j, int val) {
        m_pData[i * m_column + j] = val;
    }
};

int getRow(int sum)
{
    int res = 0;
    for (int i = 1; i * i <= sum; ++i) {
        if (sum % i == 0) {
            res = i;
        }
    }
    return res;
}

int main()
{
    int sum = 30;
    int row = getRow(sum);
    int column = sum / row;
    RotateRect r(row, column);
    r.fillRect();
    r.printArray();
    return 0;
}
