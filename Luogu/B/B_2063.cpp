#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    double a;
    cin >> a >> n;
    for (int i = 1; i <= n; i++)
        a *= 1.001;
    cout << fixed << setprecision(4) << a;
    return 0;
}