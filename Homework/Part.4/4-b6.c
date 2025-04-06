/* 学号 姓名 班级 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int GCD(int m, int n)
{
    if (n == 0)
        return m;
    else
    {
        int t = m % n;
        return GCD(n, t);
    }
}
int LCM(int m, int n)
{
    return m * n / GCD(m, n);
}

int main()
{
    int m, n;
    printf("请输入两个正整数\n");
    scanf("%d %d", &m, &n); // 不考虑输入错误
    printf("最大公约数 : %d\n", GCD(m, n));
    printf("最小公倍数 : %d\n", LCM(m, n));
    return 0;
}
