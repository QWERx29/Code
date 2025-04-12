#include <bits/stdc++.h>
using namespace std;
int main()
{
    double ans = 1.0;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        double t = 1.0;
        for (int j = 1; j <= i; j++)
            t *= 1.0 / j;
        ans += t;
    }
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}