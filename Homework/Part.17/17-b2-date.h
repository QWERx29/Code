// 2451317 冯久恒 大数据 
#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

/* Date类的声明 */
class Date
{
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */
	int year;
	int month;
	int day;

	static bool isLeapYear(int y);
	static int daysInMonth(int y, int m);
	static bool isValidDate(int y, int m, int d);
	int toDays() const;
	void fromDays(int days);

public:
	/* 允许需要的成员函数及友元函数的声明 */
	Date();
	Date(int y, int m, int d);
	Date(int days);

	void set(int y = 1900, int m = 1, int d = 1);
	void get(int &y, int &m, int &d) const;

	void show() const;

	operator int() const;

	Date operator+(int days) const;
	Date operator-(int days) const;
	int operator-(const Date &other) const;

	Date &operator++();
	Date operator++(int);
	Date &operator--();
	Date operator--(int);

	bool operator>(const Date &other) const;
	bool operator>=(const Date &other) const;
	bool operator<(const Date &other) const;
	bool operator<=(const Date &other) const;
	bool operator==(const Date &other) const;
	bool operator!=(const Date &other) const;

	/* 允许加入友元声明（如果有必要） */
	friend Date operator+(int days, const Date &date);
	friend ostream &operator<<(ostream &os, const Date &date);
	friend istream &operator>>(istream &is, Date &date);
};
