#include <bits/stdc++.h>
using namespace std;
int a[114][114], b[114][114], c[114][114], n, m, k;
int main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= k; j++)
            cin >> b[i][j];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
            for (int t = 1; t <= m; t++)
                c[i][j] += a[i][t] * b[t][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
            cout << c[i][j] << " ";
        cout << endl;
    }
    return 0;
}