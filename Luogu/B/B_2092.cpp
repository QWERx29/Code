#include <bits/stdc++.h>
using namespace std;
bool l[5033];
int n;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            if (j % i == 0)
                l[j] = !l[j];
    }
    for (int i = 1; i <= n; i++)
        if (l[i])
            cout << i << " ";
    return 0;
}