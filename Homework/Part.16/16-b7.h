/* 学号 姓名 班级 */
#pragma once

#include <iostream>
using namespace std;

enum week
{
    sun,
    mon,
    tue,
    wed,
    thu,
    fri,
    sat
};

/* 允许添加相应的函数声明 */
ostream &operator<<(ostream &out, week w);
istream &operator>>(istream &in, week &w);

week &operator++(week &w);     // 前缀++
week operator++(week &w, int); // 后缀++
week &operator--(week &w);     // 前缀--
week operator--(week &w, int); // 后缀--

week operator+(week w, int n);
week operator+(int n, week w);
week operator-(week w, int n);
int operator-(week w1, week w2);

week &operator+=(week &w, int n);
week &operator-=(week &w, int n);

int week_to_int(week w);
week int_to_week(int n);
string week_to_chinese(week w);
week string_to_week(const string &s);
bool is_valid_week_string(const string &s);