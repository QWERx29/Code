#include <bits/stdc++.h>
using namespace std;
int n, p = 1, q = 2;
double ans;
int main()
{
    cin >> n;
    for (int i = 1, t; i <= n; i++)
    {
        ans += q * 1.0 / p * 1.0;
        t = q, q += p, p = t;
    }
    cout << fixed << setprecision(4) << ans;
    return 0;
}