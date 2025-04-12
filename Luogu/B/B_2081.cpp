#include <bits/stdc++.h>
using namespace std;
bool seven(int t)
{
    if (t % 7 == 0)
        return true;
    else
    {
        while (t != 0)
        {
            if (t % 10 == 7)
                return true;
            t /= 10;
        }
        return false;
    }
}
int main()
{
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        if (!seven(i))
            ans += (i * i);
    cout << ans << endl;
    return 0;
}