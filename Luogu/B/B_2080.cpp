#include <bits/stdc++.h>
using namespace std;
int main()
{
    double x, n, ans = 1;
    cin >> x >> n;
    for (int i = 1; i <= n; i++)
    {
        /*
        double t = 1;
        for (int j = 1; j <= i; j++)
            t *= x;
        */
        ans += pow(x, i);
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}