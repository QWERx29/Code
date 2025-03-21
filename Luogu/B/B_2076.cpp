#include <bits/stdc++.h>
using namespace std;
int main()
{
    double h, s = 0, x = 0;
    cin >> h;
    s += h, x = h;
    for (int i = 1; i <= 10; i++)
    {
        x = x / 2.0;
        s += x * 2.0;
        // cout << s << ' ' << x << '\n';
    }
    cout << s - x * 2.0 << '\n'
         << x;
    return 0;
}