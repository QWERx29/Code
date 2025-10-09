#include <iostream>
using namespace std;
int main()
{
    double ave;
    for (int i = 1; i <= 12; i++)
    {
        double t;
        cin >> t;
        ave += t;
    }
    ave /= 12;
    cout << "¥" << ave << endl;
    return 0;
}