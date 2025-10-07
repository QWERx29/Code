#include <iostream>
using namespace std;
int main()
{
    int n, m;
    long long w[200092];
    cin >> n >> m;
    m %= n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = n - m + 1; i <= n; i++)
        cout << w[i] << " ";
    for (int i = 1; i <= n - m; i++)
        cout << w[i] << " ";
    return 0;
}