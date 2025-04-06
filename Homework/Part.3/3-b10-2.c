#include <stdio.h>
#include <windows.h>
int main()
{
    LARGE_INTEGER tick, begin, end;

    QueryPerformanceFrequency(&tick); // 获得计数器频率
    QueryPerformanceCounter(&begin);

    int tot = 0;
    for (int i = 123; i < 1000; i++)
    {
        int _1, _2, _3;
        _1 = i / 100, _2 = (i / 10) % 10, _3 = i % 10;

        if (_1 == _2 || _1 == _3 || _2 == _3 || _1 == 0 || _2 == 0 || _3 == 0)
            continue;
        for (int j = i; j < 1000; j++)
        {
            int _4, _5, _6;
            _4 = j / 100, _5 = (j / 10) % 10, _6 = j % 10;
            if (_4 == _5 || _4 == _6 || _5 == _6 || _4 == _1 || _4 == _2 || _4 == _3 || _5 == _1 || _5 == _2 || _5 == _3 || _6 == _1 || _6 == _2 || _6 == _3 || _4 == 0 || _5 == 0 || _6 == 0)
                continue;
            int k = 1953 - i - j;
            int _7, _8, _9;
            _7 = k / 100, _8 = (k / 10) % 10, _9 = k % 10;
            if (_7 == _8 || _7 == _9 || _8 == _9 || _7 == _1 || _7 == _2 || _7 == _3 || _7 == _4 || _7 == _5 || _7 == _6 || _8 == _1 || _8 == _2 || _8 == _3 || _8 == _4 || _8 == _5 || _8 == _6 || _9 == _1 || _9 == _2 || _9 == _3 || _9 == _4 || _9 == _5 || _9 == _6 || _7 == 0 || _8 == 0 || _9 == 0)
                continue;
            else if (k < i || k < j || k > 1000 || k < 100)
                continue;
            else
            {
                tot++;
                printf("No.%3d : %d+%d+%d=1953\n", tot, i, j, k);
            }
        }
    }
    printf("total=%d\n", tot);

    QueryPerformanceCounter(&end);

    printf("计数器频率 : %lldHz\n", tick.QuadPart);
    printf("计数器计数 : %lld\n", end.QuadPart - begin.QuadPart);
    printf("%.6f秒\n", (double)(end.QuadPart - begin.QuadPart) / tick.QuadPart);

    return 0;
}