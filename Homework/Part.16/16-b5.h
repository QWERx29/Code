/* 学号 姓名 班级 */

#pragma once

#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString
{
private:
    char *content;
    int len;
    /* 根据需要定义所需的数据成员、成员函数、友元函数等 */
    void init_CStr(const char *str);
    void allocateMemory(int length);

public:
    /* 根据需要定义所需的数据成员、成员函数、友元函数等 */
    TString();
    TString(const char *str);
    TString(const TString &other);

    ~TString();

    TString &operator=(const TString &other);
    TString &operator=(const char *str);

    friend istream &operator>>(istream &in, TString &str);
    friend ostream &operator<<(ostream &out, const TString &str);

    TString operator+(const TString &other) const;
    TString operator+(const char *str) const;
    friend TString operator+(const char *str, const TString &tstr);
    TString operator+(char ch) const;
    friend TString operator+(char ch, const TString &tstr);

    TString &operator+=(const TString &other);
    TString &operator+=(const char *str);
    TString &operator+=(char ch);

    TString &append(const TString &other);
    TString &append(const char *str);
    TString &append(char ch);

    TString operator-(const TString &other) const;
    TString operator-(const char *str) const;
    TString operator-(char ch) const;

    TString &operator-=(const TString &other);
    TString &operator-=(const char *str);
    TString &operator-=(char ch);

    TString operator*(int n) const;

    TString &operator*=(int n);

    TString operator!() const;

    bool operator==(const TString &other) const;
    bool operator!=(const TString &other) const;
    bool operator<(const TString &other) const;
    bool operator<=(const TString &other) const;
    bool operator>(const TString &other) const;
    bool operator>=(const TString &other) const;

    bool operator==(const char *str) const;
    bool operator!=(const char *str) const;
    bool operator<(const char *str) const;
    bool operator<=(const char *str) const;
    bool operator>(const char *str) const;
    bool operator>=(const char *str) const;

    friend bool operator==(const char *str, const TString &tstr);
    friend bool operator!=(const char *str, const TString &tstr);
    friend bool operator<(const char *str, const TString &tstr);
    friend bool operator<=(const char *str, const TString &tstr);
    friend bool operator>(const char *str, const TString &tstr);
    friend bool operator>=(const char *str, const TString &tstr);

    int length() const;
    const char *c_str() const;

    char &operator[](int index);
    const char &operator[](int index) const;

    void clear();
    bool empty() const;
};

/* 如果有其它全局函数需要声明，写于此处 */
int TStringLen(const TString &str);

/* 如果有需要的宏定义、只读全局变量等，写于此处 */