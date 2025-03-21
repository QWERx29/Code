#include <iostream>
#include <iomanip>
using namespace std;
const double pi = 3.14159;
int main()
{
    double r, h;
    cout << "请输入半径和高度\n";
    cin >> r >> h;
    double c, s1, s2, v1, v2;
    c = 2 * pi * r, s1 = pi * r * r, s2 = 4 * pi * r * r, v1 = 4.0 / 3 * pi * r * r * r, v2 = s1 * h;
    cout << fixed << setprecision(2) << "圆周长     : " << c << endl;
    cout << fixed << setprecision(2) << "圆面积     : " << s1 << endl;
    cout << fixed << setprecision(2) << "圆球表面积 : " << s2 << endl;
    cout << fixed << setprecision(2) << "圆球体积   : " << v1 << endl;
    cout << fixed << setprecision(2) << "圆柱体积   : " << v2 << endl;
    return 0;
}