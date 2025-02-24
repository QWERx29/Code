#include <bits/stdc++.h>
using namespace std;
double dist(double a1, double b1, double a2, double b2)
{
    double d;
    d = sqrt(pow((a1 - a2), 2) + pow((b1 - b2), 2));
    return d;
}
int main()
{
    double x1, x2, x3, y1, y2, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    double a, b, c;
    a = dist(x1, y1, x2, y2), b = dist(x2, y2, x3, y3), c = dist(x3, y3, x1, y1);
    double p = (a + b + c) / 2;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    cout << fixed << setprecision(2) << s;
}