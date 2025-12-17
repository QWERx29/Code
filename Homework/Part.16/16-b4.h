/* 学号 姓名 班级 */

#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
const int MIN_YEAR = 1900;
const int MAX_YEAR = 2099;
const int DEFAULT_YEAR = 2000;
/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date
{
private:
    int year;
    int month;
    int day;
    /* 不允许添加数据成员 */
public:
    /* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
    Date();
    Date(int y, int m, int d);
    Date(int days);

    void set(int y, int m, int d);
    void set(int y, int m);
    void set(int y);
    void get(int &y, int &m, int &d) const;
    void show() const;
    void showline() const;

    operator int() const;

    Date operator+(int days) const;
    Date operator-(int days) const;
    int operator-(const Date &d) const;

    Date &operator++();
    Date operator++(int);
    Date &operator--();
    Date operator--(int);

    bool operator>(const Date &d) const;
    bool operator>=(const Date &d) const;
    bool operator<(const Date &d) const;
    bool operator<=(const Date &d) const;
    bool operator==(const Date &d) const;
    bool operator!=(const Date &d) const;

    friend Date operator+(int days, const Date &d);
    friend ostream &operator<<(ostream &out, const Date &d);
    friend istream &operator>>(istream &in, Date &d);

    // private:
    bool isValidDate(int y, int m, int d) const;
    bool isLeapYear(int y) const;
    int daysInMonth(int y, int m) const;
    int toDays() const;
    void fromDays(int days);
};
