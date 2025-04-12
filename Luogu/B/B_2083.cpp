#include <bits/stdc++.h>
using namespace std;
int main()
{
    int x, y, f;
    char c;
    cin >> y >> x >> c >> f;
    if (f == 1)
    {
        for (int i = 1; i <= y; i++)
        {
            for (int j = 1; j <= x; j++)
                cout << c;
            cout << endl;
        }
    }
    else
    {
        for (int i = 1; i <= x; i++)
            cout << c;
        cout << endl;
        for (int i = 2; i <= y - 1; i++)
        {
            cout << c;
            for (int j = 2; j <= x - 1; j++)
                cout << ' ';
            cout << c << endl;
        }
        for (int i = 1; i <= x; i++)
            cout << c;
    }
    return 0;
}