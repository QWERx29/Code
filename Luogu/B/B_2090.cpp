#include <bits/stdc++.h>
using namespace std;
int t[5], n;
int main()
{
    cin >> n;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        if (x >= 0 && x <= 18)
            t[1]++;
        else if (x >= 19 && x <= 35)
            t[2]++;
        else if (x >= 36 && x <= 60)
            t[3]++;
        else if (x >= 61)
            t[4]++;
    }
    for (int i = 1; i <= 4; i++)
    {
        double m = t[i] * 1.0 / n;
        cout << fixed << setprecision(2) << m * 100 << "%" << endl;
    }
    return 0;
}