#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, max = -1;
    cin >> n;
    for (int i = 1, t; i <= n; i++)
    {
        cin >> t;
        if (t > max)
            max = t;
    }
    cout << max;
    return 0;
}