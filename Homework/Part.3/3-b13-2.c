#include <stdio.h>
int main()
{
    int y, m, w;
    // input year and month
    while (1)
    {
        int ret;
        printf("请输入年份(2000-2030)和月份(1-12) : ");
        ret = scanf("%d%d", &y, &m);
        if (ret != 2)
        {
            printf("输入非法，请重新输入\n");
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
        }
        else if (m < 1 || m > 12 || y < 2000 || y > 2030)
        {
            printf("输入非法，请重新输入\n");
            continue;
        }
        else
            break;
    }
    // input week no.
    while (1)
    {
        int ret;
        printf("请输入%d年%d月1日的星期(0-6表示星期日-星期六) : ", y, m);
        ret = scanf("%d", &w);
        if (ret != 1)
        {
            printf("输入非法，请重新输入\n");
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
        }
        else if (w < 0 || w > 6)
        {
            printf("输入非法，请重新输入\n");
            continue;
        }
        else
            break;
    }
    printf("\n%d年%d月的月历为:\n", y, m);
    printf("星期日  星期一  星期二  星期三  星期四  星期五  星期六\n");
    // calculate month_date
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
    int t = 1;
    for (int i = 1; i <= 8 * w; i++)
        printf(" ");
    for (int i = w; i <= 6; i++, t++)
        printf("%4d    ", t);
    printf("\n");
    while (t <= dd)
    {
        for (int i = 0; i <= 6 && t <= dd; i++, t++)
            printf("%4d    ", t);
        printf("\n");
    }

    return 0;
}