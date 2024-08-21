#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, s[1145];
    double tot;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    sort(s + 1, s + n + 1);
    for (int i = 2; i < n; i++)
        tot += s[i];
    double pt = tot / (n - 2);
    printf("%.2lf", pt);
    return 0;
}