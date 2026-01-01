// 2451317 冯久恒 大数据

#pragma once

#include "17-b1-TString.h"

class TStringAdv : public TString
{
public:
    // 继承基类构造函数
    TStringAdv() : TString() {}
    TStringAdv(const char *str) : TString(str) {}
    TStringAdv(const TString &other) : TString(other) {}
    TStringAdv(const TStringAdv &other) : TString(other) {}

    // assign函数（赋新值，等价于=操作）
    TStringAdv &assign(const TStringAdv &ts2);
    TStringAdv &assign(const char *s);

    // append函数（在尾部追加，等价于+=操作）
    TStringAdv &append(const TStringAdv &ts2);
    TStringAdv &append(const char *s);
    TStringAdv &append(const char &c);

    // insert函数（插入到pos开始的位置，pos∈[1..len+1]）
    TStringAdv &insert(const TStringAdv &ts2, int pos);
    TStringAdv &insert(const char *s, int pos);
    TStringAdv &insert(const char &c, int pos);

    // erase函数（删除第一个匹配的子串，等价于-=）
    TStringAdv &erase(const TStringAdv &ts2);
    TStringAdv &erase(const char *s);
    TStringAdv &erase(const char &c);

    // substr函数（从pos开始，返回长度为len的子串，pos∈[1..len]）
    const TStringAdv substr(const int pos, const int len = -1) const;

    // at函数（返回指定位置字符的值，等价于[]操作）
    char &at(const int n);

    // 使用基类的[]运算符
    using TString::operator[];
};

/* 全局函数 */
int TStringAdvLen(const TStringAdv &str);