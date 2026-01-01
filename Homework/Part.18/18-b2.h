// 2451317 冯久恒 大数据 
#pragma once

#include <iostream>
using namespace std;

// 基类定义
class integral
{
protected:
    double a; // 积分下限
    double b; // 积分上限
    int n;    // 划分数

public:
    virtual double value() const = 0;                       // 纯虚函数，计算定积分值
    virtual string funcName() const = 0;                    // 纯虚函数，返回函数名称
    virtual string funcSymbol() const = 0;                  // 纯虚函数，返回函数符号
    friend istream &operator>>(istream &in, integral &obj); // 输入运算符重载
};

// 派生类：计算sin(x)的定积分
class integral_sin : public integral
{
public:
    double value() const override; // 计算sin(x)的定积分
    string funcName() const override { return "sinxdx"; }
    string funcSymbol() const override { return "sinx"; }
};

// 派生类：计算cos(x)的定积分
class integral_cos : public integral
{
public:
    double value() const override; // 计算cos(x)的定积分
    string funcName() const override { return "cosxdx"; }
    string funcSymbol() const override { return "cosx"; }
};

// 派生类：计算exp(x)的定积分
class integral_exp : public integral
{
public:
    double value() const override; // 计算exp(x)的定积分
    string funcName() const override { return "e^xdx"; }
    string funcSymbol() const override { return "e^x"; }
};
