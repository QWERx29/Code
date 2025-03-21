#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double n;
    cin >> n;
    n = fabs(n);
    long long a = n;
    long double b = n - a;
    long long _1, _2, _3, _4, _5, _6, _7, _8, _9, _0;
    _1 = a % 10, a /= 10;
    _2 = a % 10, a /= 10;
    _3 = a % 10, a /= 10;
    _4 = a % 10, a /= 10;
    _5 = a % 10, a /= 10;
    _6 = a % 10, a /= 10;
    _7 = a % 10, a /= 10;
    _8 = a % 10, a /= 10;
    _9 = a % 10, a /= 10;
    _0 = a % 10, a /= 10;

        cout << "十亿位 : " << _0 << endl
         << "亿位   : " << _9 << endl
         << "千万位 : " << _8 << endl
         << "百万位 : " << _7 << endl
         << "十万位 : " << _6 << endl
         << "万位   : " << _5 << endl
         << "千位   : " << _4 << endl
         << "百位   : " << _3 << endl
         << "十位   : " << _2 << endl
         << "圆     : " << _1 << endl;
    b = round(b * 100);
    int x = (int)b, __1, __2;
    __1 = x / 10, __2 = x % 10;
    cout << "角     : " << __1 << endl
         << "分     : " << __2 << endl;
    return 0;
}
