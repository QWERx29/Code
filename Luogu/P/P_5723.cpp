#include <bits/stdc++.h>
using namespace std;
bool is_prime(int q)
{
    if (q < 2)
        return 0;
    for (int i = 2; i * i <= q; i++)
        if (q % i == 0)
            return 0;
    return 1;
}
int main()
{
    int n, cnt = 0, tot = 0;
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime(i) == 1)
        {
            tot += i;
            if (tot > n)
                break;
            cout << i << endl, cnt++;
        }
    }
    cout << cnt;
}