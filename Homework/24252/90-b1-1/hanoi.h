// 2451317 冯久恒 计算机
#pragma once

/* 将所有const常量定义的头文件包含进来 */
#include "hanoi_const_value.h"

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

int menu();
void input(int& n, char& src, char& tmp, char& dst, int mode);
void wait(int op);
void hanoi(int n, char src, char tmp, char dst,int mode);
void output1(int n, char src, char dst);
void output2(int n, char src, char dst, bool show);
void output3(int n, char src, char dst);
void output3_init(int n, char src, char dst, int op);
void output4(int n, char src, char dst, int op);
void output5(int n, char src, char dst ,int op);
void output6(int n, char src, char dst, int md);
void output_text(int n, char src, char dst, int mode);
void hanoi_game(int n, char s, char t, char d);

//void hdc_start();