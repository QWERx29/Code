#include <bits/stdc++.h>
using namespace std;
int a[114][114], b[114][114], n, m;
int main()
{
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> b[i][j], b[i][j] += a[i][j];
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << b[i][j] << " ";
        cout << endl;
    }
    return 0;
}