#include <iostream>
using namespace std;
int main()
{
    const char *month[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int n;
    cout << "ÇëÊäÈëÔÂ·Ý(1-12)" << endl;
    cin >> n;
    if (n >= 1 && n <= 12)
        cout << month[n] << endl;
    else
        cout << "Invalid" << endl;
    return 0;
}