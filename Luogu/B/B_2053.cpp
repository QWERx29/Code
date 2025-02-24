#include <bits/stdc++.h>
using namespace std;
double delta(double a, double b, double c)
{
    return pow(b, 2) - 4 * a * c;
}
void calc(double a, double b, double c)
{
    if (delta(a, b, c) > 0)
    {
        double x1, x2;
        x1 = (sqrt(delta(a, b, c)) - b) / (2 * a), x2 = (-sqrt(delta(a, b, c)) - b) / (2 * a);
        if (x1 > x2)
            swap(x1, x2);
        cout << fixed << setprecision(5) << "x1=" << x1 << ";x2=" << x2;
    }
    else if (delta(a, b, c) == 0)
        cout << fixed << setprecision(5) << "x1=x2=" << (-b / (2 * a));
    else
        cout << "No answer!";
}
int main()
{
    double a, b, c;
    cin >> a >> b >> c;
    calc(a, b, c);
    return 0;
}