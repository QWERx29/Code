// 2451317 冯久恒 大数据 
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/* --- 给出Date类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */

bool Date::isLeapYear(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int y, int m)
{
	static int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (m == 2 && isLeapYear(y))
		return 29;
	return days[m - 1];
}

bool Date::isValidDate(int y, int m, int d)
{
	if (y < 1900 || y > 2099)
		return false;
	if (m < 1 || m > 12)
		return false;
	if (d < 1 || d > daysInMonth(y, m))
		return false;
	return true;
}

int Date::toDays() const
{
	int total = 0;
	for (int y = 1900; y < year; y++)
		total += isLeapYear(y) ? 366 : 365;
	for (int m = 1; m < month; m++)
		total += daysInMonth(year, m);

	total += day - 1;
	return total;
}

void Date::fromDays(int days)
{
	const int TOTAL_DAYS = 73049;

	days %= TOTAL_DAYS;
	if (days < 0)
		days += TOTAL_DAYS;

	year = 1900;
	month = 1;
	day = 1;

	while (days >= (isLeapYear(year) ? 366 : 365))
	{
		days -= isLeapYear(year) ? 366 : 365;
		year++;
	}

	while (days >= daysInMonth(year, month))
	{
		days -= daysInMonth(year, month);
		month++;
	}

	day += days;
}

Date::Date() : year(1900), month(1), day(1) {}

Date::Date(int y, int m, int d)
{
	if (isValidDate(y, m, d))
	{
		year = y;
		month = m;
		day = d;
	}
	else
	{
		year = 1900;
		month = 1;
		day = 1;
	}
}

Date::Date(int days)
{
	fromDays(days);
}

void Date::set(int y, int m, int d)
{
	if (y == 0 || m == 0 || d == 0 || !isValidDate(y, m, d))
	{
		year = 1900;
		month = 1;
		day = 1;
	}
	else
	{
		year = y;
		month = m;
		day = d;
	}
}

void Date::get(int &y, int &m, int &d) const
{
	y = year;
	m = month;
	d = day;
}

void Date::show() const
{
	cout << setfill('0') << setw(4) << year << "-" << setw(2) << month << "-" << setw(2) << day << setfill(' ') << endl;
}

// 类型转换
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

int Date::operator-(const Date &other) const
{
	return this->toDays() - other.toDays();
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

bool Date::operator>(const Date &other) const
{
	return toDays() > other.toDays();
}

bool Date::operator>=(const Date &other) const
{
	return toDays() >= other.toDays();
}

bool Date::operator<(const Date &other) const
{
	return toDays() < other.toDays();
}

bool Date::operator<=(const Date &other) const
{
	return toDays() <= other.toDays();
}

bool Date::operator==(const Date &other) const
{
	return toDays() == other.toDays();
}

bool Date::operator!=(const Date &other) const
{
	return toDays() != other.toDays();
}

Date operator+(int days, const Date &date)
{
	return date + days;
}

ostream &operator<<(ostream &os, const Date &date)
{
	os << setfill('0') << setw(4) << date.year << "-" << setw(2) << date.month << "-" << setw(2) << date.day << setfill(' ');
	return os;
}

istream &operator>>(istream &is, Date &date)
{
	int y, m, d;
	is >> y >> m >> d;
	date.set(y, m, d);
	return is;
}
