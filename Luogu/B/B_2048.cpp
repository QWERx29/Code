#include <bits/stdc++.h>
using namespace std;
int main()
{
    int m;
    char c;
    cin >> m >> c;
    int w = 8;
    if (m > 1000)
    {
        m -= 1000;
        int t = m / 500;
        if (m % 500 != 0)
            t++;
        w += t * 4;
    }
    if (c == 'y')
        w += 5;
    cout << w;
    return 0;
}