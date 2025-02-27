#include <bits/stdc++.h>
using namespace std;
int main()
{
    int m, n, x = 0;
    cin >> m >> n;
    for (int i = 1, t; i <= n; i++)
    {
        cin >> t;
        if (m - t < 0)
        {
            x++;
            continue;
        }
        else
            m -= t;
    }
    cout << x;
    return 0;
}