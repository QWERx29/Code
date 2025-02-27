#include <bits/stdc++.h>
using namespace std;
int n;
double calc(int r, int s)
{
    return (s * 1.0 / r * 1.0) * 100;
}
int cmp(double x, double y)
{
    if (x - y > 5)
        return -1;
    else if (y - x > 5)
        return 1;
    else
        return 100;
}
int main()
{
    cin >> n;
    double v;
    for (int i = 1, a, b; i <= n; i++)
    {
        cin >> a >> b;
        // cout << calc(a, b);
        if (i == 1)
        {
            v = calc(a, b);
            continue;
        }
        if (cmp(v, calc(a, b)) == -1)
            cout << "worse";
        else if (cmp(v, calc(a, b)) == 1)
            cout << "better";
        else
            cout << "same";
        cout << '\n';
    }
    return 0;
}