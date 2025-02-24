#include <bits/stdc++.h>
using namespace std;
const double PI = 3.14;
int main()
{
    int r;
    double v;
    cin >> r;
    v = PI * pow(r, 3) * 4 / 3;
    cout << fixed << setprecision(5) << v;
}