#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, t = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        t += x;
    }
    cout << t << " " << fixed << setprecision(5) << double(t) / n;
    return 0;
}