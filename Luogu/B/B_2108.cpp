#include <bits/stdc++.h>
using namespace std;
int a[114][114], b[114][114], n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j], b[i][j] = a[i][j];
    for (int i = 2; i < n; i++)
        for (int j = 2; j < m; j++)
        {
            double t = (a[i - 1][j] + a[i][j - 1] + a[i][j + 1] + a[i + 1][j] + a[i][j]) * 1.0 / 5;
            b[i][j] = (int(t * 10) % 10 > 5 ? int(t) + 1 : int(t));
        }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cout << b[i][j] << " ";
        cout << endl;
    }
    return 0;
}