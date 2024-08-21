#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, cnt = 1, ans = -114514, a[10086];
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 2; i <= n; i++)
    {
        if (a[i] == a[i - 1] + 1)
            cnt++;
        else
            cnt = 1;
        ans = max(ans, cnt);
        // cout << cnt << " ";
    }
    cout << ans;
    return 0;
}