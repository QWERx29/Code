#include <bits/stdc++.h>
using namespace std;
bool year(int y)
{
    if (y % 4 == 0)
    {
        if (y % 100 == 0)
        {
            if (y % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}
int main()
{
    int y;
    cin >> y;
    if (year(y))
        cout << "Y" << endl;
    else
        cout << "N" << endl;
    return 0;
}