#include <iostream>
using namespace std;
int n, a, b, c, d, e;
int main()
{
    cin >> n;
    a = n / 10000;
    b = n / 1000 % 10;
    c = n / 100 % 10;
    d = n / 10 % 10;
    e = n % 10000 % 10;
    cout << "万位 : " << a << endl;
    cout << "千位 : " << b << endl;
    cout << "百位 : " << c << endl;
    cout << "十位 : " << d << endl;
    cout << "个位 : " << e << endl;
    return 0;
}