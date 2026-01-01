// 2451317  冯久恒 大数据 
#include <iostream>
#include <cmath>
#include "18-b2.h"
using namespace std;

// 输入运算符重载实现
istream &operator>>(istream &in, integral &obj)
{
    cout << "请输入" << obj.funcName() << "的下限、上限及区间划分数量:" << endl;
    in >> obj.a >> obj.b >> obj.n;
    return in;
}

// integral_sin类的value函数实现
double integral_sin::value() const
{
    cout << funcName() << "=[" << a << "~" << b << "/n=" << n << "] : ";

    double sum = 0.0;
    double dx = (b - a) / n; // 每个小矩形的宽度

    for (int i = 1; i <= n; i++)
    {
        double x = a + i * dx; // 取右端点
        sum += sin(x) * dx;
    }
    cout << sum << endl;
    return sum;
}

// integral_cos类的value函数实现
double integral_cos::value() const
{
    cout << funcName() << "=[" << a << "~" << b << "/n=" << n << "] : ";

    double sum = 0.0;
    double dx = (b - a) / n; // 每个小矩形的宽度

    for (int i = 1; i <= n; i++)
    {
        double x = a + i * dx; // 取右端点
        sum += cos(x) * dx;
    }
    cout << sum << endl;
    return sum;
}

// integral_exp类的value函数实现
double integral_exp::value() const
{
    cout << funcName() << "=[" << a << "~" << b << "/n=" << n << "] : ";

    double sum = 0.0;
    double dx = (b - a) / n; // 每个小矩形的宽度

    for (int i = 1; i <= n; i++)
    {
        double x = a + i * dx; // 取右端点
        sum += exp(x) * dx;
    }
    cout << sum << endl;
    return sum;
}
