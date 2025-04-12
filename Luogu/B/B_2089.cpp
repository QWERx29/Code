#include <bits/stdc++.h>
using namespace std;
int n, t[123];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> t[i];
    for (int i = n; i >= 1; i--)
        cout << t[i] << " ";
    return 0;
}