#include <stdio.h>
int feb_date(int year)
{
    int x = 0;
    int feb = 28;
    if (year % 4 == 0 && year % 100 != 0)
    {
        x = 1;
        if (year % 400 == 0)
            x = 1;
    }
    if (x == 1)
        feb = 29;
    return feb;
}
int calc(int m, int d, int date[])
{
    int sum = d;
    switch (m)
    {
    case 1:
        break;
    case 2:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 3:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 4:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 5:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 6:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 7:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 8:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 9:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 10:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 11:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    case 12:
        for (int i = 1; i < m; i++)
            sum += date[i];
        break;
    }
    return sum;
}
int main()
{
    int y, m, d, date[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int sum = 0;
    printf("请输入年，月，日\n");
    scanf("%d%d%d", &y, &m, &d);
    // int jan = 31, feb = 28, mar = 31, apr = 30, may = 31, jun = 30, jul = 31, aug = 31, sep = 30, oct = 31, nov = 30, dec = 31;
    //  check if valid input
    if (m < 1 || m > 12)
    {
        printf("输入错误-月份不正确\n");
        return 0;
    }
    if (d > 31 || d < 1)
    {
        printf("输入错误-日与月的关系非法");
        return 0;
    }
    else if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
    {
        printf("输入错误-日与月的关系非法");
        return 0;
    }
    date[2] = feb_date(y);
    if (m == 2 && d > date[2])
    {
        printf("输入错误-日与月的关系非法");
        return 0;
    }
    // calculate

    printf("%d-%d-%d是%d年的第%d天\n", y, m, d, y, calc(m, d, date));
    return 0;
}