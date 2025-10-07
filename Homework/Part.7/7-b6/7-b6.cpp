/* 学号 姓名 班级 */
#include <iostream>
#include <conio.h>
#include "7-b6.h"
using namespace std;
bool ifrn(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int getDays(int y, int m)
{
        if (m < 1 || m > 12) return 0;
        if (m == 2) {
            return ifrn(y) ? 29 : 28;
        }
        const int days[] = { 0, 31,0,31,30,31,30,31,31,30,31,30,31 };
        return days[m];
}

Date::Date()
{
    Date::year = 2000;
    Date::month = 1;
    Date::day = 1;
}
Date::Date(int y, int m, int d) 
{
    set(y, m, d);
}

Date::Date(int n) 
{
    year = 1900;
    month = 1;
    day = 0;
    while (n > 0) 
    {
        if (year > 2099)
        {
            year = 2099;
            month = 12;
			day = 31;
            break;
        }
        int daysInCurrMonth = getDays(year, month);
        if (day + n <= daysInCurrMonth) 
        {
            day += n;
            break;
        }
        else 
        {
            n -= (daysInCurrMonth - day + 1);
            day = 1;
            month++;
            if (month > 12) 
            {
                month = 1;
                year++;
            }
        }
    }
}
void Date::set(int y, int m, int d) 
{
    int origYear = Date::year, origMonth = Date::month, origDay = Date::day;
    if (y != 0)
    {
        if (y < 1900 || y > 2099)
            year = 2000;
        else
            year = y;
    }
    else
        year = origYear;
    if (m != 0) 
        month = (m < 1 || m > 12) ? 1 : m;
    else 
         month = origMonth;
    if (d != 0) 
        day = (d < 1 || d > getDays(year, month)) ? 1 : d;
    else 
        day = origDay;
    if (day > getDays(year, month)) 
        day = 1;
}

    // 获取当前日期
void Date::get(int& y, int& m, int& d)
{
    y = year;
    m = month;
    d = day;
}

void Date::show()
{
    cout << year << "." << month << "." << day << endl;
}




/* 给出 Date 类的所有成员函数的体外实现 */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

/* 如果有需要的其它全局函数的实现，可以写于此处 */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
