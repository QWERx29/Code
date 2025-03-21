#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    int i = 2;
    for (;; i++)
    {
        if (a % i == b % i && a % i == c % i)
            break;
        else
            continue;
    }
    cout << i << endl;
    return 0;
}