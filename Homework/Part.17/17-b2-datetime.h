// 2451317 冯久恒 大数据 

#pragma once

#include "17-b2-date.h"
#include "17-b2-time.h"

/* 如果有其它全局函数需要声明，写于此处 */

/* DateTime类的基本要求：
	1、不允许定义任何数据成员
	2、尽量少定义成员函数
*/

class DateTime : public Date, public Time
{
protected:
	/* 不允许再定义任何数据成员 */
	long long toTotalSeconds() const;
	void fromTotalSeconds(long long secs);

public:
	/* 不允许再定义任何数据成员，允许需要的成员函数及友元函数的声明 */
	DateTime();
	DateTime(int y, int m, int d, int h = 0, int min = 0, int s = 0);
	DateTime(long long seconds);

	void set(int y = 1900, int m = 1, int d = 1, int h = 0, int min = 0, int s = 0);
	void get(int &y, int &m, int &d, int &h, int &min, int &s) const;

	void show() const;

	operator long long() const;

	DateTime operator+(long long seconds) const;
	DateTime operator+(int seconds) const;
	DateTime operator-(long long seconds) const;
	DateTime operator-(int seconds) const;
	long long operator-(const DateTime &other) const;

	DateTime &operator++();
	DateTime operator++(int);
	DateTime &operator--();
	DateTime operator--(int);

	bool operator>(const DateTime &other) const;
	bool operator>=(const DateTime &other) const;
	bool operator<(const DateTime &other) const;
	bool operator<=(const DateTime &other) const;
	bool operator==(const DateTime &other) const;
	bool operator!=(const DateTime &other) const;

	/* 允许加入友元声明（如果有必要） */
	friend DateTime operator+(long long seconds, const DateTime &dt);
	friend DateTime operator+(int seconds, const DateTime &dt);
	friend ostream &operator<<(ostream &os, const DateTime &dt);
	friend istream &operator>>(istream &is, DateTime &dt);
};
