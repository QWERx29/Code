// 2451317 冯久恒 计算机
#include <stdio.h>
#include <math.h>
int main()
{
    double n;
    printf("请输入[0-100 亿)之间的数字: \n");
    scanf("%lf", &n);
    n = fabs(n);
    long long a = (long long)(n);
    long double b = n - a;
    long long _1, _2, _3, _4, _5, _6, _7, _8, _9, _0;
    _1 = a % 10, a /= 10;
    _2 = a % 10, a /= 10;
    _3 = a % 10, a /= 10;
    _4 = a % 10, a /= 10;
    _5 = a % 10, a /= 10;
    _6 = a % 10, a /= 10;
    _7 = a % 10, a /= 10;
    _8 = a % 10, a /= 10;
    _9 = a % 10, a /= 10;
    _0 = a % 10, a /= 10;
    printf("十亿位 : %d\n", _0);
    printf("亿位   : %d\n", _9);
    printf("千万位 : %d\n", _8);
    printf("百万位 : %d\n", _7);
    printf("十万位 : %d\n", _6);
    printf("万位   : %d\n", _5);
    printf("千位   : %d\n", _4);
    printf("百位   : %d\n", _3);
    printf("十位   : %d\n", _2);
    printf("圆     : %d\n", _1);
    b = round(b * 100);
    int x = (int)b, __1, __2;
    __1 = x / 10, __2 = x % 10;
    printf("角     : %d\n", __1);
    printf("分     : %d\n", __2);
    return 0;
}
