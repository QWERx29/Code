#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        int f[40];
        f[1] = f[2] = 1;
        for (int i = 3; i <= a; i++)
            f[i] = f[i - 1] + f[i - 2];
        cout << f[a] << endl;
    }
    return 0;
}