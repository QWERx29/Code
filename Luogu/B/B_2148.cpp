#include <bits/stdc++.h>
using namespace std;
double f(double x, int n)
{
    if (n == 1)
        return x / (1 + x);
    else
        return x / (n + f(x, n - 1));
}
int main()
{
    int n;
    double x;
    cin >> x >> n;
    cout << fixed << setprecision(2) << f(x, n) << endl;
    return 0;
}