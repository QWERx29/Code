/* 学号 姓名 班级 */
#include <iostream>
#include "16-b4.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */
Date::Date() : year(2000), month(1), day(1) {}

Date::Date(int y, int m, int d)
{
    set(y, m, d);
}

Date::Date(int days)
{
    fromDays(days);
}

void Date::set(int y, int m, int d)
{
    if (y == 0)
        y = year;
    else if (y < MIN_YEAR || y > MAX_YEAR)
        y = DEFAULT_YEAR;
    if (m == 0)
        m = month;
    else if (m < 1 || m > 12)
        m = 1;
    if (d == 0)
        d = day;
    else if (d < 1 || d > daysInMonth(y, m))
        d = 1;
    year = y;
    month = m;
    day = d;
    if (day > daysInMonth(year, month))
        day = 1;
}

void Date::set(int y, int m)
{
    set(y, m, 1);
}

void Date::set(int y)
{
    set(y, 1, 1);
}

void Date::get(int &y, int &m, int &d) const
{
    y = year;
    m = month;
    d = day;
}

void Date::show() const
{
    cout << year << "年" << month << "月" << day << "日" << endl;
}

void Date::showline() const
{
    cout << year << "年" << month << "月" << day << "日";
}

Date::operator int() const
{
    return toDays();
}

Date Date::operator+(int days) const
{
    Date result = *this;
    result.fromDays(result.toDays() + days);
    return result;
}

Date Date::operator-(int days) const
{
    return *this + (-days);
}

int Date::operator-(const Date &d) const
{
    return this->toDays() - d.toDays();
}

Date &Date::operator++()
{
    *this = *this + 1;
    return *this;
}

Date Date::operator++(int)
{
    Date temp = *this;
    ++(*this);
    return temp;
}

Date &Date::operator--()
{
    *this = *this - 1;
    return *this;
}

Date Date::operator--(int)
{
    Date temp = *this;
    --(*this);
    return temp;
}

bool Date::operator>(const Date &d) const
{
    return toDays() > d.toDays();
}

bool Date::operator>=(const Date &d) const
{
    return toDays() >= d.toDays();
}

bool Date::operator<(const Date &d) const
{
    return toDays() < d.toDays();
}

bool Date::operator<=(const Date &d) const
{
    return toDays() <= d.toDays();
}

bool Date::operator==(const Date &d) const
{
    return toDays() == d.toDays();
}

bool Date::operator!=(const Date &d) const
{
    return toDays() != d.toDays();
}

Date operator+(int days, const Date &d)
{
    return d + days;
}

ostream &operator<<(ostream &out, const Date &d)
{
    d.showline();
    return out;
}

istream &operator>>(istream &in, Date &d)
{
    int y, m, day;
    in >> y >> m >> day;
    d.set(y, m, day);
    return in;
}

bool Date::isValidDate(int y, int m, int d) const
{
    if (y < MIN_YEAR || y > MAX_YEAR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > daysInMonth(y, m))
        return false;
    return true;
}

bool Date::isLeapYear(int y) const
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int y, int m) const
{
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y))
    {
        return 29;
    }
    return days[m - 1];
}

int Date::toDays() const
{
    int totalDays = 0;

    // 累加年份天数
    for (int y = MIN_YEAR; y < year; y++)
    {
        totalDays += isLeapYear(y) ? 366 : 365;
    }

    // 累加月份天数
    for (int m = 1; m < month; m++)
    {
        totalDays += daysInMonth(year, m);
    }

    // 累加日期天数
    totalDays += day;

    return totalDays;
}

void Date::fromDays(int days)
{
    if (days < 1)
    {
        year = MIN_YEAR;
        month = 1;
        day = 1;
        return;
    }

    // 计算最大天数
    int maxDays = 0;
    for (int y = MIN_YEAR; y <= MAX_YEAR; y++)
    {
        maxDays += isLeapYear(y) ? 366 : 365;
    }

    if (days > maxDays)
    {
        year = MAX_YEAR;
        month = 12;
        day = 31;
        return;
    }

    // 计算实际日期
    year = MIN_YEAR;
    month = 1;
    day = 1;

    int remainingDays = days;

    // 计算年份
    while (remainingDays > (isLeapYear(year) ? 366 : 365))
    {
        remainingDays -= isLeapYear(year) ? 366 : 365;
        year++;
    }

    // 计算月份
    while (remainingDays > daysInMonth(year, month))
    {
        remainingDays -= daysInMonth(year, month);
        month++;
    }

    // 计算日期
    day = remainingDays;
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */