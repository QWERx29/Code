#include <bits/stdc++.h>
using namespace std;
int digit(int n, int k)
{
    int t = 1;
    for (int i = 1; i < k; i++)
        t *= 10;
    return (n / t) % 10;
}
int main()
{
    int n, k;
    cin >> n >> k;
    cout << digit(n, k) << endl;
    return 0;
}