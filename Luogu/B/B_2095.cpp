#include <bits/stdc++.h>
const double INF = DBL_MAX;
using namespace std;
int n;
double t[329], maxt = -INF, mint = INF, ave, sum, x = -INF;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i];
    sort(t + 1, t + n + 1);
    for (int i = 2; i <= n - 1; i++)
        sum += t[i];
    ave = sum / (n - 2);
    for (int i = 2; i <= n - 1; i++)
        x = max(x, fabs(t[i] - ave));
    cout << fixed << setprecision(2) << ave << " " << x;
    return 0;
}