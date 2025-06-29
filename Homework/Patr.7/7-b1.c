/* 学号 姓名 班级 */
#define _CRT_SECURE_NO_WARNINGS // 使用了VS认为unsafe的函数
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <string.h> //Dev/CB的strlen需要

struct tj_time
{
    int tj_year;   // 表示年份
    int tj_month;  // 表示月(1-12)
    int tj_day;    // 表示日(1-28/29/30/31)
    int tj_hour;   // 表示小时(0-23)
    int tj_minute; // 表示分(0-59)
    int tj_second; // 表示秒(0-59)
};

void wait_for_enter()
{
    printf("\n按回车键继续");
    while (_getch() != '\r')
        ;
    printf("\n\n");
}

void system_time_output(const time_t input_time) // time_t的本质是64位无符号整数
{
    struct tm *tt; // struct tm 为系统定义的结构体

    tt = localtime(&input_time); // localtime为系统函数

    /* tm_*** 为struct tm中的成员，和本题的struct tj_time具体的内容不完全符合，具体含义自己查找相关资料 */
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", tt->tm_year + 1900, tt->tm_mon + 1, tt->tm_mday, tt->tm_hour, tt->tm_min, tt->tm_sec);

    return;
}

void tj_time_output(const struct tj_time *const tp)
{
    /* 实现自定义结构的输出，输出形式与system_time_output相同 */
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", tp->tj_year, tp->tj_month, tp->tj_day, tp->tj_hour, tp->tj_minute, tp->tj_second);
}

struct tj_time *tj_time_convert(int input_time)
{
    static struct tj_time result; // 定义静态局部变量，不准动
    /* 实现过程开始，在下面添加相应的定义及执行语句即可 */
    result.tj_second = input_time % 60;
    result.tj_minute = (input_time / 60) % 60;
    result.tj_hour = (input_time / 3600 + 8) % 24;
    int yr = 1970, days = (input_time / 3600) / 24 + 1, mon = 0;
    if (result.tj_hour < 8)
        days++;
    int date[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (days > 365)
    {
        yr++;
        date[2] = 28;
        if (yr % 4 == 0 && yr % 100 != 0)
            date[2] = 29;
        else if (yr % 400 == 0)
            date[2] = 29;
        if (date[2] == 29)
            days -= 366;
        else
            days -= 365;
    }
    if (date[2] == 29)
        days++;
    result.tj_year = yr;
    for (int i = 0; i <= 12 && days > date[i]; i++)
    {
        days -= date[i];
        mon++;
    }
    result.tj_day = days, result.tj_month = mon;
    /* 实现过程结束 */

    return &result; // 注意，返回的是静态局部变量的地址，本语句不准动
}

int main()
{
    int read_time;
    struct tj_time *tp;
    for (;;)
    {
        int ret = scanf("%d", &read_time); // 因为采用输入重定向，此处不加任何提示
        /* 输入错误或<0则退出循环 */
        if (ret != 1)
            break;
        printf("秒数             : %d\n", read_time);
        printf("系统转换的结果   : ");
        system_time_output(read_time);
        printf("自定义转换的结果 : ");
        tp = tj_time_convert(read_time);
        tj_time_output(tp);
        wait_for_enter();
    }
    if (1)
    {
        struct tj_time *tp;
        int t = (int)time(0); // 系统函数，取当前系统时间（从1970-01-01 00:00:00开始的秒数）
        printf("当前系统时间     : %d\n", t);
        printf("系统转换的结果   : ");
        system_time_output(t);
        printf("自定义转换的结果 : ");
        tp = tj_time_convert(t);
        tj_time_output(tp);
        wait_for_enter();
    }
    return 0;
}