#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, ans[4] = {0};
    cin >> n;
    for (int i = 1, t; i <= n; i++)
    {
        cin >> t;
        if (t == 1)
            ans[1]++;
        else if (t == 5)
            ans[2]++;
        else if (t == 10)
            ans[3]++;
    }
    for (int i = 1; i <= 3; i++)
        cout << ans[i] << endl;
    return 0;
}