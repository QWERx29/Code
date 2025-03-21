#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a, b;
    cin >> a >> b;
    int x = 1;
    for (int i = 1; i <= b; i++)
    {
        x *= a;
        x %= 1000;
    }
    if (x >= 100)
        cout << x;
    else if (x >= 10)
        cout << "0" << x;
    else
        cout << "00" << x;
    return 0;
}