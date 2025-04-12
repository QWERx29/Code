#include <bits/stdc++.h>
using namespace std;
int n, a[123], m, ans;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], m = max(m, a[i]);
    for (int i = 1; i <= n; i++)
        if (a[i] != m)
            ans += a[i];
    cout << ans << endl;
    return 0;
}