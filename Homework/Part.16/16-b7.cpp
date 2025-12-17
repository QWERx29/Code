#include "16-b7.h"

string to_lower(const string &s)
{
    string result = s;
    for (size_t i = 0; i < result.length(); i++)
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = result[i] - 'A' + 'a';
    return result;
}

int week_to_int(week w)
{
    return static_cast<int>(w);
}

week int_to_week(int n)
{
    n %= 7;
    if (n < 0)
        n += 7;
    return static_cast<week>(n);
}

string week_to_chinese(week w)
{
    static const char *chinese_week[] =
        {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};

    int index = week_to_int(w);
    if (index >= 0 && index < 7)
        return chinese_week[index];
    return "错误";
}

week string_to_week(const string &s)
{
    string lower_str = to_lower(s);

    if (lower_str == "sun")
        return sun;
    if (lower_str == "mon")
        return mon;
    if (lower_str == "tue")
        return tue;
    if (lower_str == "wed")
        return wed;
    if (lower_str == "thu")
        return thu;
    if (lower_str == "fri")
        return fri;
    if (lower_str == "sat")
        return sat;

    return static_cast<week>(99);
}

bool is_valid_week_string(const string &s)
{
    string lower_str = to_lower(s);

    const char *valid_strings[] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};

    for (int i = 0; i < 7; i++)
        if (lower_str == valid_strings[i])
            return true;
    return false;
}

bool is_valid_week(week w)
{
    int value = week_to_int(w);
    return value >= 0 && value < 7;
}

ostream &operator<<(ostream &out, week w)
{
    out << week_to_chinese(w);
    return out;
}

istream &operator>>(istream &in, week &w)
{
    string input;
    if (in >> input)
    {
        if (is_valid_week_string(input))
            w = string_to_week(input);
        else
        {
            w = static_cast<week>(99);
            in.clear();
        }
    }
    return in;
}

week &operator++(week &w)
{
    if (is_valid_week(w))
    {
        int value = week_to_int(w);
        value = (value + 1) % 7;
        w = static_cast<week>(value);
    }
    return w;
}

week operator++(week &w, int)
{
    week temp = w;
    ++w;
    return temp;
}

week &operator--(week &w)
{
    if (is_valid_week(w))
    {
        int value = week_to_int(w);
        value = (value + 6) % 7;
        w = static_cast<week>(value);
    }
    return w;
}

week operator--(week &w, int)
{
    week temp = w;
    --w;
    return temp;
}

week operator+(week w, int n)
{
    if (is_valid_week(w))
    {
        int value = week_to_int(w);
        value = (value + n) % 7;
        if (value < 0)
            value += 7;
        return static_cast<week>(value);
    }
    return w;
}

week operator+(int n, week w)
{
    return w + n;
}

week operator-(week w, int n)
{
    return w + (-n);
}

int operator-(week w1, week w2)
{
    if (is_valid_week(w1) && is_valid_week(w2))
    {
        int v1 = week_to_int(w1);
        int v2 = week_to_int(w2);
        return (v1 - v2 + 7) % 7;
    }
    return 0;
}

week &operator+=(week &w, int n)
{
    if (is_valid_week(w))
        w = w + n;
    return w;
}

week &operator-=(week &w, int n)
{
    if (is_valid_week(w))
        w = w - n;
    return w;
}