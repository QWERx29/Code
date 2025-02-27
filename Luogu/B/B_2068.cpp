#include <bits/stdc++.h>
using namespace std;
int n, ans;
bool cmp(int x)
{
    int a, b, c, d;
    a = x / 1000, b = (x / 100) % 10, c = (x / 10) % 10, d = x % 10;
    if (d - a - b - c > 0)
        return true;
    else
        return false;
}
int main()
{
    cin >> n;
    for (int i = 1, t; i <= n; i++)
    {
        cin >> t;
        if (cmp(t) == true)
            ans++;
    }
    cout << ans;
    return 0;
}