/* 学号 姓名 班级 */
#include <iostream>
#include <string>
using namespace std;

template <typename T, int ROW, int COL>
class matrix
{
private:
    T value[ROW][COL];

public:
    // 默认构造函数
    matrix()
    {
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
                value[i][j] = T(); // 使用类型T的默认值
    }

    // 重载+运算符
    matrix<T, ROW, COL> operator+(const matrix<T, ROW, COL> &other) const
    {
        matrix<T, ROW, COL> result;
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
                result.value[i][j] = value[i][j] + other.value[i][j];
        return result;
    }

    // 重载赋值运算符
    matrix<T, ROW, COL> &operator=(const matrix<T, ROW, COL> &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < ROW; i++)
                for (int j = 0; j < COL; j++)
                    value[i][j] = other.value[i][j];
        }
        return *this;
    }

    // 友元函数声明
    template <typename U, int R, int C>
    friend ostream &operator<<(ostream &os, const matrix<U, R, C> &m);

    template <typename U, int R, int C>
    friend istream &operator>>(istream &is, matrix<U, R, C> &m);
};

// 输出运算符重载
template <typename T, int ROW, int COL>
ostream &operator<<(ostream &os, const matrix<T, ROW, COL> &m)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            os << m.value[i][j];
            if (j < COL - 1)
                os << " ";
        }
        os << endl;
    }
    return os;
}

// 输入运算符重载
template <typename T, int ROW, int COL>
istream &operator>>(istream &is, matrix<T, ROW, COL> &m)
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            is >> m.value[i][j];
    return is;
}