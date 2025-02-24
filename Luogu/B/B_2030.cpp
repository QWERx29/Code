#include <bits/stdc++.h>
using namespace std;
int main()
{
    double x_1, x_2, y_1, y_2;
    cin >> x_1 >> y_1 >> x_2 >> y_2;
    double d = sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
    cout << fixed << setprecision(3) << d;
}