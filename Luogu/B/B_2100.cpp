#include <bits/stdc++.h>
using namespace std;
int n, a, b;
int main()
{
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
        cout << "(" << a << "," << i << ") ";
    cout << endl;
    for (int i = 1; i <= n; i++)
        cout << "(" << i << "," << b << ") ";
    cout << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i - j == a - b)
                cout << "(" << i << "," << j << ") ";
    cout << endl;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i + j == a + b)
                cout << "(" << j << "," << i << ") ";
    return 0;
}