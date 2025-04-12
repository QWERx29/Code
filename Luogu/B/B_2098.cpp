#include <bits/stdc++.h>
using namespace std;
int n, a[20092], b[20092];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        if (b[a[i]] == 1)
            continue;
        else
        {
            cout << a[i] << " ";
            b[a[i]] = 1;
        }
    }
    return 0;
}