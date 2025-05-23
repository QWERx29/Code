// 2451317 冯久恒 计算机
#include <iostream>
#include <conio.h>
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"
#include "hanoi.h"

using namespace std;
/* ----------------------------------------------------------------------------------

     本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

     本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

int main()
{
	cout << "请确认当前cmd窗口的大小为40行*120列以上，字体为新宋体/16，按C继续，Q退出" << endl;
	while (1) {
		char ch = _getch();
		if (ch == 'C' || ch == 'c')
			break;
		if (ch == 'Q' || ch == 'q')
			return 0;
	}
	const int   win_width = 1400, win_high = 900;	//设定屏幕宽度
	const int   win_bgcolor = 7, win_fgcolor = 0;
	const int   color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B
	hdc_init(win_bgcolor, win_fgcolor, win_width, win_high);		//用(背景色，前景色，宽度，高度）初始化窗口
	hdc_cls();
	int n = 0;
	char src = 0, tmp = 0, dst = 0;
	while(1)
	{
		cct_cls();
		int op = menu();
		if (op == 0)
			break;
		cout << endl;
		if ((op >= 1 && op <= 4))
		{
			input(&n, &src, &tmp, &dst, op);
			if (op == 4)
				output_text(n, src, dst, 4);
			hanoi(n, src, tmp, dst, op);
		}
		else if (op == 5)
			output4(5, 'A', 'A', op);
		else if (op >= 6 && op <= 9)
		{
			input(&n, &src, &tmp, &dst, op);
			output5(n, src, dst, op);
			if (op >= 7 && op <= 8)
				hanoi(n, src, tmp, dst, op);
			else if(op == 9)
				hanoi_game(n, src, tmp, dst);
		}
		wait(op);
	}
	return 0;
}