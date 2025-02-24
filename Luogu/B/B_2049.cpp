#include <bits/stdc++.h>
#define INF 2147483647
using namespace std;
int main()
{
    long long a, b, c;
    cin >> a >> b >> c;
    long long m = -INF;
    if (a > m)
        m = a;
    if (b > m)
        m = b;
    if (c > m)
        m = c;
    cout << m;
    return 0;
}