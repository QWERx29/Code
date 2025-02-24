#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, t[4] = {0};
    cin >> n;
    for (int i = 1, a, b, c; i <= n; i++)
    {
        cin >> a >> b >> c;
        t[0] += a, t[1] += b, t[2] += c;
        t[3] += (a + b + c);
    }
    for (int i = 0; i <= 3; i++)
        cout << t[i] << ' ';
    return 0;
}