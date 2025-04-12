#include <bits/stdc++.h>
using namespace std;
int a[1024], b[1024], n, ans;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        ans += a[i] * b[i];
    cout << ans << endl;
    return 0;
}