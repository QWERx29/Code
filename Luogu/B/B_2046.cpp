#include <bits/stdc++.h>
using namespace std;
int main()
{
    double d;
    cin >> d;
    double time_walk, time_bike;
    time_walk = d / 1.2, time_bike = (d / 3.0) + 50;
    if (time_bike < time_walk)
        cout << "Bike";
    else if (time_bike == time_walk)
        cout << "All";
    else
        cout << "Walk";
    return 0;
}