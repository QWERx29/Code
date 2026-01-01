
#include <iostream>
#include <cmath>
#include "18-b2.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：fun_integral不准动，思考一下，integral应如何定义
***************************************************************************/
void fun_integral(integral &fRef)
{
  cin >> fRef; // 输入上下限、划分数，不考虑输入错误
  cout << fRef.value() << endl;
  return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
  integral_sin s1;
  integral_cos s2;
  integral_exp s3;

  fun_integral(s1); // 计算sinxdx的值
  fun_integral(s2); // 计算cosxdx的值
  fun_integral(s3); // 计算expxdx的值

  return 0;
}

// 注：矩形计算取右值，输出为正常double格式
