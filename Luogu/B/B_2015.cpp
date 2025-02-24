#include <bits/stdc++.h>
using namespace std;
int main()
{
    double r, r1, r2;
    cin >> r1 >> r2;
    r = 1 / (1 / r1 + 1 / r2);
    cout << fixed << setprecision(2) << r;
}