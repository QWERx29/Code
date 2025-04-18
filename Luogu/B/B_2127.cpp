#include <bits/stdc++.h>
using namespace std;
bool cpt_num(int x)
{
    int u = 0;
    for (int i = 1; i < x; i++)
        if (x % i == 0)
            u += i;
    if (u == x)
        return true;
    else
        return false;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++)
        if (cpt_num(i))
            cout << i << endl;
    return 0;
}