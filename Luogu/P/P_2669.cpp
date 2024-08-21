#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, s = 0, t;
    cin >> n;
    for (t = 1; t <= n; t++)
    {
        if (t * (t + 1) / 2 > n)
            break;
    }
    int x = n - (t * (t - 1) / 2);
    for (int i = 1; i < t; i++)
        s += i * i;
    s += t * x;
    cout << s;
}