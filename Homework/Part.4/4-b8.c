/* 学号 姓名 班级 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void convert(int n)
{
    if (n == 0)
    {
        printf("0");
        return;
    }
    if (n < 0)
    {
        int t = -(n % 10);
        printf("%c", (char)t + '0');
        if (n / 10 != 0)
        {
            printf(" ");
            convert(n / 10);
        }
        else
            printf(" -");
    }
    else
    {
        int t = n % 10;
        printf("%c", (char)t + '0');
        if (n / 10 != 0)
        {
            printf(" ");
            convert(n / 10);
        }
    }
}

int main()
{
    int n;
    printf("请输入一个整数\n");
    scanf("%d", &n);
    convert(n);
    printf("\n");
    return 0;
}