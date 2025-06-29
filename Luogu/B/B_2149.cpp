#include <bits/stdc++.h>
using namespace std;
double calc(double a, double b, double c)
{
    if (a + b <= c || a + c <= b || b + c <= a)
        return -1;
    else
    {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
}
int main()
{
    double a, b, c, s;
    cin >> a >> b >> c;
    s = calc(a, b, c);
    if (s == -1)
        cout << "No solution." << endl;
    else
        cout << fixed << setprecision(2) << s << endl;
    return 0;
}