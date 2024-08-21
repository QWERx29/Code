#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n[3];
    for (int i = 0; i < 3; i++)
        cin >> n[i];
    string s;
    cin >> s;
    sort(n, n + 3);
    for (int i = 0; i < 3; i++)
        cout << n[s[i] - 65] << " ";
}