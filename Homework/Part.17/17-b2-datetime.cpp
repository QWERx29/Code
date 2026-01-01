// 2451317 冯久恒 大数据 
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

/* --- 给出DateTime类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */

long long DateTime::toTotalSeconds() const
{
    return static_cast<long long>(Date::toDays()) * 86400 + Time::toSeconds();
}

void DateTime::fromTotalSeconds(long long secs)
{
    const long long TOTAL_SECONDS = 6311433600LL; // 73049天 * 86400

    secs %= TOTAL_SECONDS;
    if (secs < 0)
        secs += TOTAL_SECONDS;

    int days = static_cast<int>(secs / 86400);
    int seconds = static_cast<int>(secs % 86400);

    Date::fromDays(days);
    Time::fromSeconds(seconds);
}

DateTime::DateTime() : Date(), Time() {}

DateTime::DateTime(int y, int m, int d, int h, int min, int s)
{
    set(y, m, d, h, min, s);
}

DateTime::DateTime(long long seconds)
{
    fromTotalSeconds(seconds);
}

void DateTime::set(int y, int m, int d, int h, int min, int s)
{
    if (Date::isValidDate(y, m, d) && Time::isValidTime(h, min, s))
    {
        Date::set(y, m, d);
        Time::set(h, min, s);
    }
    else
    {
        Date::set(1900, 1, 1);
        Time::set(0, 0, 0);
    }
}

void DateTime::get(int &y, int &m, int &d, int &h, int &min, int &s) const
{
    Date::get(y, m, d);
    Time::get(h, min, s);
}

void DateTime::show() const
{
    cout << setfill('0') << setw(4) << year << "-" << setw(2) << month << "-" << setw(2) << day << setfill(' ') << " ";
    cout << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << ":" << setw(2) << second << setfill(' ') << endl;
}

DateTime::operator long long() const
{
    return toTotalSeconds();
}

DateTime DateTime::operator+(long long seconds) const
{
    DateTime result = *this;
    result.fromTotalSeconds(result.toTotalSeconds() + seconds);
    return result;
}

DateTime DateTime::operator+(int seconds) const
{
    return *this + static_cast<long long>(seconds);
}

DateTime DateTime::operator-(long long seconds) const
{
    return *this + (-seconds);
}
DateTime DateTime::operator-(int seconds) const
{
    return *this - static_cast<long long>(seconds);
}

long long DateTime::operator-(const DateTime &other) const
{
    return this->toTotalSeconds() - other.toTotalSeconds();
}

DateTime &DateTime::operator++()
{
    *this = *this + 1LL;
    return *this;
}

DateTime DateTime::operator++(int)
{
    DateTime temp = *this;
    ++(*this);
    return temp;
}

DateTime &DateTime::operator--()
{
    *this = *this - 1LL;
    return *this;
}

DateTime DateTime::operator--(int)
{
    DateTime temp = *this;
    --(*this);
    return temp;
}

bool DateTime::operator>(const DateTime &other) const
{
    return toTotalSeconds() > other.toTotalSeconds();
}

bool DateTime::operator>=(const DateTime &other) const
{
    return toTotalSeconds() >= other.toTotalSeconds();
}

bool DateTime::operator<(const DateTime &other) const
{
    return toTotalSeconds() < other.toTotalSeconds();
}

bool DateTime::operator<=(const DateTime &other) const
{
    return toTotalSeconds() <= other.toTotalSeconds();
}

bool DateTime::operator==(const DateTime &other) const
{
    return toTotalSeconds() == other.toTotalSeconds();
}

bool DateTime::operator!=(const DateTime &other) const
{
    return toTotalSeconds() != other.toTotalSeconds();
}

DateTime operator+(long long seconds, const DateTime &dt)
{
    return dt + seconds;
}

ostream &operator<<(ostream &os, const DateTime &dt)
{
    os << static_cast<const Date &>(dt) << " " << static_cast<const Time &>(dt);
    return os;
}

istream &operator>>(istream &is, DateTime &dt)
{
    int y, m, d, h, min, s;
    is >> y >> m >> d >> h >> min >> s;
    dt.set(y, m, d, h, min, s);
    return is;
}

DateTime operator+(int seconds, const DateTime &dt)
{
    return dt + static_cast<long long>(seconds);
}
