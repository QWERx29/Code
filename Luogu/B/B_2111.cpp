#include <bits/stdc++.h>
using namespace std;
int main()
{
    double t;
    string a, b;
    cin >> t >> a >> b;
    int s = 0;
    for (int i = 0; i < a.length(); i++)
        if (a[i] == b[i])
            s++;
    if ((double)s * 1.0 / a.length() > t)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}