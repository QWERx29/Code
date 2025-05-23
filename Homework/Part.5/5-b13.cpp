#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    char ms[11][27] = {0};
    srand((unsigned int)(time(0))); // 生成伪随机数的种子，只需在程序开始时执行一次即可
    for (int i = 1, t = 1; t <= 50; i++)
    {
        int x = rand() % 10 + 1, y = rand() % 26 + 1;
        if (ms[x][y] != '*')
        {
            ms[x][y] = '*';
            t++;
        }
        else
            continue;
    }
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 26; j++)
        {
            if (ms[i][j] != '*')
            {
                for (int q = i - 1; q <= i + 1; q++)
                {
                    for (int w = j - 1; w <= j + 1; w++)
                    {
                        if (ms[q][w] == '*')
                            ms[i][j]++;
                    }
                }
                ms[i][j] += '0';
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 26; j++)
            cout << ms[i][j] << " ";
        cout << endl;
    }
    return 0;
}