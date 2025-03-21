#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double pi = 3.14159;
int main()
{
    int a, b, x;
    cin >> a >> b >> x;
    float s = static_cast<float>(0.5 * a * b * sin(pi * x / 180));
    cout << fixed << setprecision(3) << s << endl;
    return 0;
}