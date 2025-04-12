#include <bits/stdc++.h>
using namespace std;
int a[10086], n, x;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> x;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == x)
        {
            cout << i - 1 << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}