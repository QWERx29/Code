#include <iostream>
#include <cmath>
using namespace std;
int H, T;
void print_hr()
{
    int hr = 8 - H;
    if (hr < 0)
        hr += 24;
    if (hr >= 0 && hr < 10)
        cout << "0" << hr;
    else
        cout << hr;
}
void print_min()
{
    int min = 60 - T;
    if (min < 10)
        cout << "0" << min;
    else
        cout << min;
}
void print()
{
    print_hr();
    cout << ":";
    print_min();
}
int main()
{
    double s, v;
    cin >> s >> v;
    double t = s / v;
    T = ceil(t) + 10, H = 0;
    H = T / 60 + 1, T %= 60;
    print();
}