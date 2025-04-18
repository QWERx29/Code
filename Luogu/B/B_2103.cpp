#include <bits/stdc++.h>
using namespace std;
int a[114][114], b[114][114], n, m, cnt;
double ans;
int main()
{
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> b[i][j];
            if (b[i][j] == a[i][j])
                cnt++;
        }
    ans = cnt * 100.0 / (m * n);
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}