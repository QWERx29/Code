#include <stdio.h>
#include <stdbool.h>
int main()
{
    int y, m, d;
    int sum = 0;
    printf("请输入年，月，日\n");
    scanf("%d%d%d", &y, &m, &d);
    int jan = 31, feb = 28, mar = 31, apr = 30, may = 31, jun = 30, jul = 31, aug = 31, sep = 30, oct = 31, nov = 30, dec = 31;
    // check if valid input
    if (m < 1 || m > 12)
    {
        printf("输入错误-月份不正确\n");
        return 0;
    }
    if (d > 31 || d < 1)
    {
        printf("输入错误-日与月的关系非法\n");
        return 0;
    }
    else if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
    {
        printf("输入错误-日与月的关系非法\n");
        return 0;
    }
    bool x = false;
    if (y % 4 == 0 && y % 100 != 0)
    {
        x = true;
        if (y % 400 == 0)
            x = true;
    }
    if (x == true)
        feb = 29;
    else
    {
        if (m == 2 && d > 28)
        {
            printf("输入错误-日与月的关系非法\n");
            return 0;
        }
    }
    // calculate
    switch (m)
    {
    case 1:
        sum += d;
        break;
    case 2:
        sum += jan + d;
        break;
    case 3:
        sum += jan + feb + d;
        break;
    case 4:
        sum += jan + feb + mar + d;
        break;
    case 5:
        sum += jan + feb + mar + apr + d;
        break;
    case 6:
        sum += jan + feb + mar + apr + may + d;
        break;
    case 7:
        sum += jan + feb + mar + apr + may + jun + d;
        break;
    case 8:
        sum += jan + feb + mar + apr + may + jun + jul + d;
        break;
    case 9:
        sum += jan + feb + mar + apr + may + jun + jul + aug + d;
        break;
    case 10:
        sum += jan + feb + mar + apr + may + jun + jul + aug + sep + d;
        break;
    case 11:
        sum += jan + feb + mar + apr + may + jun + jul + aug + sep + oct + d;
        break;
    case 12:
        sum += jan + feb + mar + apr + may + jun + jul + aug + sep + oct + nov + d;
        break;
    }
    printf("%d-%d-%d是%d年的第%d天\n", y, m, d, y, sum);
    return 0;
}