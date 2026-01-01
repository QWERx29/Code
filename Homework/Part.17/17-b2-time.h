// 2451317 冯久恒 大数据 

#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

/* Time类的声明 */
class Time
{
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */
	int hour;
	int minute;
	int second;

	static bool isValidTime(int h, int m, int s);
	int toSeconds() const;
	void fromSeconds(int secs);

public:
	/* 允许需要的成员函数及友元函数的声明 */
	Time();
	Time(int h, int m, int s);
	Time(int seconds);

	void set(int h = 0, int m = 0, int s = 0);
	void get(int &h, int &m, int &s) const;

	void show() const;

	operator int() const;

	Time operator+(int seconds) const;
	Time operator-(int seconds) const;
	int operator-(const Time &other) const;

	Time &operator++();
	Time operator++(int);
	Time &operator--();
	Time operator--(int);

	bool operator>(const Time &other) const;
	bool operator>=(const Time &other) const;
	bool operator<(const Time &other) const;
	bool operator<=(const Time &other) const;
	bool operator==(const Time &other) const;
	bool operator!=(const Time &other) const;

	/* 允许加入友元声明（如果有必要） */
	friend Time operator+(int seconds, const Time &time);
	friend ostream &operator<<(ostream &os, const Time &time);
	friend istream &operator>>(istream &is, Time &time);
};
