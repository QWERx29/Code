#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double n;
    cin >> n;
    n = fabs(n);
    int a = n;
    double b = n - a;
    int _1, _2, _3, _4, _5, _6, _7, _8, _9, _0;
    long double tmp = a;
    long double divisor = 1;
    _1 = a % 10, a /= 10;
    _2 = a % 10, a /= 10;
    cout << _1 << " " << _2;
    while (divisor * 10 <= tmp)
    {
        divisor *= 10;
    }
    while (divisor >= 1)
    {
        cout << (int)(tmp / divisor) << " ";
        temp = fmod(temp, divisor);
        divisor /= 10;
    }

    // 处理小数部分
    if (b > 0)
    {
        cout << ". ";
        b = round(b * 1000); // 保留三位小数
        int fracInt = (int)b;
        cout << fracInt / 100 << " ";
        cout << (fracInt / 10) % 10 << " ";
        cout << fracInt % 10;
    }

    cout << endl;
    return 0;
}
