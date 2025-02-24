#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a, b, tot = 0;
    cin >> a >> b;
    for (int i = a; i <= b; i++)
    {
        if (i % 17 == 0)
            tot += i;
    }
    cout << tot;
    return 0;
}