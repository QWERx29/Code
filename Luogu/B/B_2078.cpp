#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    int k, cnt = 0;
    cin >> n >> k;
    while (n != 0)
    {
        if (n % 10 == 3)
            cnt++;
        n /= 10;
    }
    if (cnt == k)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}