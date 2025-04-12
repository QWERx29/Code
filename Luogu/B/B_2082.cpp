#include <bits/stdc++.h>
using namespace std;
int count(int x)
{
    int t = 0;
    while (x != 0)
    {
        if (x % 10 == 2)
            t++;
        x /= 10;
    }
    return t;
}
int main()
{
    int L, R, cnt = 0;
    cin >> L >> R;
    for (int i = L; i <= R; i++)
        cnt += count(i);
    cout << cnt << endl;
    return 0;
}