//螺旋打印二位数组
#include<iostream>
#include<vector>
class RotateRect {
private:
    int m_row;
    int m_column;
    std::vector<int> m_vectData;
    static const int STEP_I[4];
    static const int STEP_J[4];
public:
    RotateRect(int row, int column): m_row(row), m_column(column), m_vectData(m_row * m_column, 0) {}
    void printArray() const {
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_column; ++j) {
                std::cout << getData(i, j) << "\t";
            }
            std::cout << std::endl;
        }
    }
    void fillRect() {
        int i = 0, j = 0;
        // 0:> 1:V 2:< 3:^
        int direction = 0;
        for (int n = 1; n <= m_row * m_column; ++n) {
            // 设置当前单元格的值
            setData(i, j, n);
            // 按照之前方向尝试能否移动
            if (try_move(i, j, direction)) {continue;}
            // 换下一个方向尝试能否移动
            direction = nextDirection(direction);
            if (try_move(i, j, direction)) {continue;}
            // 两个方向都不能移动，说明已经填满了
            break;
        }
    }
private:
    static int nextDirection(int direction) {
        return (direction + 1) % 4;
    }
    static void move(int i, int j, int& res_i, int& res_j, int direction) {
        res_i = i + STEP_I[direction];
        res_j = j + STEP_J[direction];
    }
private:
    //尝试看下能否移动
    bool try_move(int& i, int& j, int direction) const {
        int next_i, next_j;
        move(i, j, next_i, next_j, direction);
        if (checkValid(next_i, next_j)) {
            i = next_i;
            j = next_j;
            return true;
        }
        return false;
    }
    bool checkValid(int i, int j) const {
        if (i < 0 || i >= m_row) {return false;}
        if (j < 0 || j >= m_column) {return false;}
        if (getData(i, j) != 0) {return false;}
        return true;
    }
    int getData(int i, int j) const {
        return m_vectData[i * m_column + j];
    }
    void setData(int i, int j, int val) {
        m_vectData[i * m_column + j] = val;
    }
};
const int RotateRect::STEP_I[4] = {0, 1, 0, -1};
const int RotateRect::STEP_J[4] = {1, 0, -1 , 0};
int getRow(int sum)
{
    int res = 1;
    for (int i = 1; i * i <= sum; ++i) {
        if (sum % i == 0) {res = i;}
    }
    return res;
}
int main()
{
    int sum = 35;
    int row = getRow(sum);
    int column = sum / row;
    RotateRect r(row, column);
    r.fillRect();
    r.printArray();
    return 0;
}
