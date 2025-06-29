#include <bits/stdc++.h>
using namespace std;
int t[30], u[30];
int main()
{
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
    {
        t[s[i] - 'a']++;
        u[s[i] - 'a'] = i;
    }
    int m = 1234;
    for (int i = 0; i < 26; i++)
        if (t[i] == 1)
            m = min(m, u[i]);
    if (m == 1234)
        cout << "no" << endl;
    else
        cout << s[m] << endl;
    return 0;
}