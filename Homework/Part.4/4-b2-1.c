// 2451317 冯久恒 计算机
#include <stdio.h>
int calc_date(int y, int m)
{
    int dd;
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        dd = 31;
    else if (m != 2)
        dd = 30;
    else
    {
        if (y % 4 == 0 && y % 100 != 0)
        {
            dd = 29;
        }
        else
        {
            if (y % 400 == 0)
                dd = 29;
            else
                dd = 28;
        }
    }
    return dd;
}
int calc_week(int y, int m, int d)
{
    int c, yy, ww;
    if (m <= 2)
        m += 12, y--;
    c = y / 100, yy = y % 100;
    ww = yy + (yy / 4) + (c / 4) - (2 * c) + ((m + 1) * 13 / 5) + (d - 1);
    if (ww < 0)
        ww += 7;
    ww %= 7;
    return ww;
}
void output(int w)
{
    printf("星期");
    switch (w)
    {
    case 0:
        printf("日\n");
        break;
    case 1:
        printf("一\n");
        break;
    case 2:
        printf("二\n");
        break;
    case 3:
        printf("三\n");
        break;
    case 4:
        printf("四\n");
        break;
    case 5:
        printf("五\n");
        break;
    case 6:
        printf("六\n");
        break;
    }
}
int main()
{
    int y, m, d;
    while (1)
    {
        int ret;
        printf("请输入年[1900-2100]、月、日：");
        ret = scanf("%d%d%d", &y, &m, &d);
        if (ret != 3)
        {
            printf("输入非法，请重新输入\n");
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
        }
        else if (m < 1 || m > 12)
        {
            printf("月份不正确，请重新输入\n");
            continue;
        }
        else if (y < 1900 || y > 2100)
        {
            printf("年份不正确，请重新输入\n");
            continue;
        }
        else if (d > calc_date(y, m) || d < 0)
        {
            printf("日不正确，请重新收入\n");
            continue;
        }
        else
            break;
    }
    int w = calc_week(y, m, d);
    printf("\n");
    output(w);

    return 0;
}