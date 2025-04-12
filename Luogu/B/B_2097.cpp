#include <bits/stdc++.h>
using namespace std;
int a[123], n, len, x;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] == a[i - 1])
            x++, len = max(len, x);
        else
            x = 0;
    }
    cout << len + 1 << endl;
    return 0;
}