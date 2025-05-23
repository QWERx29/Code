#include <iostream>
using namespace std;
#define N 10

int main()
{
    char str[256], *p;
    int a[N] = {0}, *pnum, *pa;
    cout << "请输入间隔含有若干正负数字的字符串" << endl;
    cin.getline(str, 256, '\n');
    p = str, pa = a;
    while (*p != '\0' && pa - a < N)
    {
        while (*p != '\0' && (*p < '0' || *p > '9'))
            p++;
        if (*p == '\0')
            break;
        while (*p >= '0' && *p <= '9')
        {
            *pa = *pa * 10 + (*p - '0');
            p++;
        }
        pa++;
    }
    cout << "共有" << pa - a << "个整数" << endl;
    for (pnum = a; pnum < pa; pnum++)
        cout << *pnum << " ";
    cout << endl;
    return 0;
}