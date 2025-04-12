#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a, b, c, ans = 0;
    cin >> a >> b >> c;
    for (int i = 0; i <= c / a; i++)
        if ((c - a * i) % b == 0 && (c - a * i) >= 0)
            ans++;
    cout << ans << endl;
    return 0;
}