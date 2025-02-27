#include <bits/stdc++.h>
using namespace std;
double ans;
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
            ans += (-1.0 / i);
        else
            ans += (1.0 / i);
    }
    cout << fixed << setprecision(4) << ans << endl;
    return 0;
}