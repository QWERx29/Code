#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.14
double volume(int R, int H)
{
    return pow(R, 2) * PI * H / 1000;
}
int main()
{
    int h, r;
    cin >> h >> r;
    cout << int(20 / volume(r, h)) + 1;
    return 0;
}