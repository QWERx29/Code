#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    double a = 0.00, b = 1.00;
    cout << fixed << setprecision(2);
    for (int i = 1; i <= n; ++i)
    {
        // cout << "F(" << i << ") = " << a << endl;
        double next = a + b;
        a = b;
        b = next;
    }
    cout << a;
    return 0;
}
