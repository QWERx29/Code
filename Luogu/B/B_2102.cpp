#include <bits/stdc++.h>
using namespace std;
const int INF = INT_MAX;
int t[6][6], x, y, a = -INF, b = INF;
bool o = true;
int main()
{
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
            cin >> t[i][j];
    for (int i = 1; i <= 5; i++)
    {
        a = -INF, b = INF;
        o = false;
        for (int j = 1; j <= 5; j++)
            if (t[i][j] > a)
                y = j, a = t[i][j];
        for (int u = 1; u <= 5; u++)
            if (t[u][y] < b)
                x = u, b = t[u][y];
        if (a == b)
        {
            cout << x << " " << y << " " << t[x][y] << endl;
            return 0;
        }
    }
    cout << "not found" << endl;
    return 0;
}