#include <bits/stdc++.h>
using namespace std;
const double PI = 3.14159;
int main()
{
    double r, d, c, s;
    cin >> r;
    cout << fixed << setprecision(4);
    d = r * 2, c = d * PI, s = PI * r * r;
    cout << d << ' ' << c << ' ' << s;
}