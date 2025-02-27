#include <bits/stdc++.h>
using namespace std;
int n, p;
double calc(double a, double b)
{
    double x = sqrt(pow(a, 2) + pow(b, 2));
    return x * 2 / 50;
}
double x, y, ans;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x >> y >> p;
        ans += (calc(x, y) + p * 1.5);
    }
    cout << int(ceil(ans));
    return 0;
}