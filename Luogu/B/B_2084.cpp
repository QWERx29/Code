#include <bits/stdc++.h>
using namespace std;
bool if_prime(int t)
{
    for (int i = 2; i * i <= t; i++)
        if (t % i == 0)
            return false;
    return true;
}
int main()
{
    int n, x = 1;
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        if (n % i == 0)
        {
            if (if_prime(i))
                x = max(x, i);
        }
    }
    cout << x << endl;
    return 0;
}