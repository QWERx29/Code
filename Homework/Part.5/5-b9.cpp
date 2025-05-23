#include <iostream>
using namespace std;

int main()
{
    int sk[10][10];
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            while (1)
            {
                cin >> sk[i][j];
                if (cin.good() != 1)
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
                else if (sk[i][j] > 9 || sk[i][j] < 1)
                    continue;
                else
                    break;
            }
        }
    }
    int used[10];
    for (int i = 1; i <= 9; i++)
    {
        for (int t = 1; t <= 9; t++)
            used[t] = 0;
        for (int j = 1; j <= 9; j++)
            used[sk[i][j]]++;
        for (int t = 1; t <= 9; t++)
        {
            if (used[t] != 1)
            {
                cout << "不是数独的解" << endl;
                return 0;
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        for (int t = 1; t <= 9; t++)
            used[t] = 0;
        for (int j = 1; j <= 9; j++)
            used[sk[j][i]]++;
        for (int t = 1; t <= 9; t++)
        {
            if (used[t] != 1)
            {
                cout << "不是数独的解" << endl;
                return 0;
            }
        }
    }
    for (int s = 1; s <= 9; s += 3)
    {
        for (int t = 1; t <= 9; t += 3)
        {
            for (int u = 1; u <= 9; u++)
                used[u] = 0;
            for (int i = s; i <= s + 2; i++)
                for (int j = t; j <= t + 2; j++)
                    used[sk[i][j]]++;
            for (int u = 1; u <= 9; u++)
            {
                if (used[u] != 1)
                {
                    cout << "不是数独的解" << endl;
                    return 0;
                }
            }
        }
    }
    cout << "是数独的解" << endl;
    return 0;
}