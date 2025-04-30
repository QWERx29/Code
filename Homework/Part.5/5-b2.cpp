#include <iostream>
using namespace std;
int main()
{
    int l[105];
    for (int i = 1; i <= 100; i++)
        l[i] = -1;
    for (int i = 1; i <= 100; i++)
    {
        for (int j = 1; j <= 100; j++)
            if (j % i == 0)
                l[j] = -l[j];
    }
    int b[11], t = 1;
    for (int i = 1; i <= 100; i++)
        if (l[i] == 1)
            b[t] = i, t++;
    for (int i = 1; i < t - 1; i++)
        cout << b[i] << " ";
    cout << b[t - 1] << endl;
    return 0;
}