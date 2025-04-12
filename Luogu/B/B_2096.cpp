#include <bits/stdc++.h>
using namespace std;
int n, Fmax, a[114514], b[114514];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], Fmax = max(a[i], Fmax), b[a[i]]++;
    for (int i = 0; i <= Fmax; i++)
        cout << b[i] << endl;
    return 0;
}