#include <bits/stdc++.h>
#define PI 3.141593
using namespace std;
int main()
{
    int t;
    cin >> t;
    if (t == 1)
        cout << "I love Luogu!";
    else if (t == 2)
        cout << "6 4";
    else if (t == 3)
        cout << 14 / 4 << endl
             << 14 - 14 % 4 << endl
             << 14 % 4;
    else if (t == 4)
        cout << fixed << setprecision(3) << 1.0 * 500 / 3;
    else if (t == 5)
        cout << (260 + 220) / (12 + 20);
    else if (t == 6)
        cout << sqrt(pow(6, 2) + pow(9, 2));
    else if (t == 7)
        cout << "110\n90\n0\n";
    else if (t == 8)
        cout << PI * 10 << endl
             << PI * 25 << endl
             << 4 / 3.0 * PI * 125 << endl;
    else if (t == 9)
        cout << 22;
    else if (t == 10)
        cout << 9;
    else if (t == 11)
        cout << 1.0 * 100 / 3;
    else if (t == 12)
        cout << (int)('M' - 'A') + 1 << endl
             << (char)(18 + 'A' - 1);
    else if (t == 13)
        cout << (int)(pow(4256 * PI / 3, 1.0 * 1 / 3));
    else if (t == 14)
        cout << 50;
    return 0;
}
