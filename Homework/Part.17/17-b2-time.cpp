// 2451317 冯久恒 大数据 
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- 给出Time类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */

bool Time::isValidTime(int h, int m, int s)
{
    return (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60);
}

int Time::toSeconds() const
{
    return hour * 3600 + minute * 60 + second;
}

void Time::fromSeconds(int secs)
{
    const int TOTAL_SECONDS = 86400;

    secs %= TOTAL_SECONDS;
    if (secs < 0)
        secs += TOTAL_SECONDS;

    hour = secs / 3600;
    secs %= 3600;
    minute = secs / 60;
    second = secs % 60;
}

Time::Time() : hour(0), minute(0), second(0) {}

Time::Time(int h, int m, int s)
{
    if (isValidTime(h, m, s))
    {
        hour = h;
        minute = m;
        second = s;
    }
    else
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

Time::Time(int seconds)
{
    fromSeconds(seconds);
}

void Time::set(int h, int m, int s)
{
    if (!isValidTime(h, m, s))
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
    else
    {
        hour = h;
        minute = m;
        second = s;
    }
}

void Time::get(int &h, int &m, int &s) const
{
    h = hour;
    m = minute;
    s = second;
}

void Time::show() const
{
    cout << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << ":" << setw(2) << second << setfill(' ') << endl;
}

Time::operator int() const
{
    return toSeconds();
}

Time Time::operator+(int seconds) const
{
    Time result = *this;
    result.fromSeconds(result.toSeconds() + seconds);
    return result;
}

Time Time::operator-(int seconds) const
{
    return *this + (-seconds);
}

int Time::operator-(const Time &other) const
{
    return this->toSeconds() - other.toSeconds();
}

Time &Time::operator++()
{
    *this = *this + 1;
    return *this;
}

Time Time::operator++(int)
{
    Time temp = *this;
    ++(*this);
    return temp;
}

Time &Time::operator--()
{
    *this = *this - 1;
    return *this;
}

Time Time::operator--(int)
{
    Time temp = *this;
    --(*this);
    return temp;
}

bool Time::operator>(const Time &other) const
{
    return toSeconds() > other.toSeconds();
}

bool Time::operator>=(const Time &other) const
{
    return toSeconds() >= other.toSeconds();
}

bool Time::operator<(const Time &other) const
{
    return toSeconds() < other.toSeconds();
}

bool Time::operator<=(const Time &other) const
{
    return toSeconds() <= other.toSeconds();
}

bool Time::operator==(const Time &other) const
{
    return toSeconds() == other.toSeconds();
}

bool Time::operator!=(const Time &other) const
{
    return toSeconds() != other.toSeconds();
}

Time operator+(int seconds, const Time &time)
{
    return time + seconds;
}

ostream &operator<<(ostream &os, const Time &time)
{
    os << setfill('0') << setw(2) << time.hour << ":" << setw(2) << time.minute << ":" << setw(2) << time.second << setfill(' ');
    return os;
}

istream &operator>>(istream &is, Time &time)
{
    int h, m, s;
    is >> h >> m >> s;
    time.set(h, m, s);
    return is;
}
