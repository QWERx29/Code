#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int ans = 0;
    for (int i = 2; i <= n; i++)
        ans = (ans + m % i) % i;
    cout << ans << endl;
    return 0;
}