#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, x, k;
    cin >> n;
    n /= 364;
    if (n <= 100)
    {
        n -= 3, cout << n << "\n1";
    }
    else
    {
        k = 0;
        while (n > 100)
            n -= 3, k++;
        cout << n << endl
             << k;
    }
    return 0;
}