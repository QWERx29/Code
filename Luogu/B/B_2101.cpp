#include <bits/stdc++.h>
using namespace std;
int m, n, a[114][114];
int sum;
int main()
{
    cin >> m >> n;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];

    if (m == 1 && n == 1)
    {
        cout << a[1][1] << endl;
        return 0;
    }
    for (int i = 1; i <= n; i++)
        sum += (a[1][i] + a[m][i]);
    for (int i = 1; i <= m; i++)
        sum += (a[i][1] + a[i][n]);
    sum -= (a[1][1] + a[1][n] + a[m][1] + a[m][n]);
    cout << sum << endl;
    return 0;
}