#include <iostream>
using namespace std;
int main()
{
    while (1)
    {
        int n;
        cin >> n;
        if (n == -1)
            return 0;
        else if (n == 0)
            cout << "0 1" << endl;
        else if (n == 1)
            cout << "1 2" << endl;
        else
        {
            long long a = 0;
            long long b = 1;
            long long c;
            for (int i = 2; i <= n; i++)
            {
                c = b + a + 1;
                a = b;
                b = c;
            }
            cout << b << " " << 1 + a + b << endl;
        }
    }
    return 0;
}