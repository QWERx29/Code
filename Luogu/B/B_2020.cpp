#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a[6], e = 0;
    for (int i = 1; i <= 5; i++)
        cin >> a[i];
    for (int i = 1; i <= 5; i++)
    {
        e += a[i] % 3;
        if (i == 1)
            a[5] += a[1] / 3, a[2] += a[1] / 3, a[1] /= 3;
        else if (i == 5)
            a[1] += a[5] / 3, a[4] += a[5] / 3, a[5] /= 3;
        else
            a[i - 1] += a[i] / 3, a[i + 1] += a[i] / 3, a[i] /= 3;
    }
    for (int i = 1; i <= 5; i++)
        cout << a[i] << " ";
    cout << endl
         << e;
}