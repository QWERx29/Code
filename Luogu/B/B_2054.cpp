#include <bits/stdc++.h>
using namespace std;
int main()
{
    double n, t = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        t += x;
    }
    cout << fixed << setprecision(2) << t / n;
    return 0;
}