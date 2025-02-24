#include <bits/stdc++.h>
using namespace std;
int main()
{
    double n, t = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        double x;
        cin >> x;
        t += x;
    }
    cout << fixed << setprecision(4) << t / n;
    return 0;
}