#include <bits/stdc++.h>
using namespace std;
int mtx[6][6];
int a, b;
int main()
{
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
            cin >> mtx[i][j];
    cin >> a >> b;
    for (int j = 1; j <= 5; j++)
        swap(mtx[a][j], mtx[b][j]);
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
            cout << mtx[i][j] << " ";
        cout << endl;
    }
    return 0;
}