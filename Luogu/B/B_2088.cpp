#include <bits/stdc++.h>
using namespace std;
int t[11];
int main()
{
    for (int i = 1; i <= 10; i++)
        cin >> t[i];
    double ans = 28.9 * t[1] + 32.7 * t[2] + 45.6 * t[3] + 78 * t[4] + 35 * t[5] + 86.2 * t[6] + 27.8 * t[7] + 43 * t[8] + 56 * t[9] + 65 * t[10];
    cout << fixed << setprecision(1) << ans << endl;
    return 0;
}