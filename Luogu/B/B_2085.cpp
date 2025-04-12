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
    int x, cnt = 0, i = 2;
    cin >> x;
    while (1)
    {
        if (if_prime(i))
            cnt++;
        if (cnt == x)
            break;
        i++;
    }
    cout << i << endl;
    return 0;
}