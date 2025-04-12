#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, t[123];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i];
    cin >> m;
    for (int i = 1; i <= n; i++)
        if (t[i] == m)
            cnt++;
    cout << cnt << endl;
    return 0;
}