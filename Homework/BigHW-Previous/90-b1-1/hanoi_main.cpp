// 2451317 冯久恒 计算机

#include <iostream>
#include <conio.h>
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"
#include "hanoi.h"
/*
#define _CRT_SECURE_NO_WARNINGS
#include "stb_image.h"

using namespace std;


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
	cct_cls();
	const int   win_width = 1400, win_high = 900;	//设定屏幕宽度
	const int   win_bgcolor = 7, win_fgcolor = 0;
	const int   color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B
	hdc_init(win_bgcolor, win_fgcolor, win_width, win_high);		//用(背景色，前景色，宽度，高度）初始化窗口
	hdc_cls();
	int n;
	char src, tmp, dst;
	while(1)
	{
		cct_cls();
		int op = menu();
		if (op == 0)
			break;
		cout << endl;
		if ((op >= 1 && op <= 4))
		{
			input(n, src, tmp, dst, op);
			if (op == 4)
				output_text(n, src, dst, 4);
			hanoi(n, src, tmp, dst, op);
		}
		else if (op == 5)
			output4(5, 'A', 'A', op);
		else if (op >= 6 && op <= 9)
		{
			input(n, src, tmp, dst, op);
			output5(n, src, dst, op);
			if (op >= 7 && op <= 8)
				hanoi(n, src, tmp, dst, op);
			else if(op == 9)
				hanoi_game(n, src, tmp, dst);
		}
		wait(op);
	}

		// 初始化画布：背景黑色，前景白色，分辨率800x600
		// hdc_init(BLACK, WHITE, 800, 600);

		// 在坐标(100, 50)处绘制图片
		hdc_draw_image(100, 50, "E:/Downloads/shmetrolines2035.png");

		// 释放资源
		hdc_release();
	return 0;
}

# include<iostream>
# include<conio.h>
# include "cmd_console_tools.h"
# include "cmd_hdc_tools.h"
*/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

extern char addr[500];
extern int a;

int main()
{
	// 初始化画布：背景黑色，前景白色，分辨率800x600

	
	cout << "请输入图片路径：" << endl;
	cin >> addr;
	cout << "请输入像素高度" << endl;
	cin >> a;
	cout << "请确认当前cmd窗口的大小为40行*120列以上，字体为新宋体/16，按C继续，Q退出" << endl;
	cout << "请检查图像分辨率不超过1500*250" << endl;
	while (1) {
		char ch = _getch();
		if (ch == 'C' || ch == 'c')
			break;
		if (ch == 'Q' || ch == 'q')
			return 0;
	}
	cct_cls();
	const int   win_width = 2500, win_high = 1400;	//设定屏幕宽度
	const int   win_bgcolor = 7, win_fgcolor = 0;
	const int   color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B
	hdc_init(win_bgcolor, win_fgcolor, win_width, win_high);		//用(背景色，前景色，宽度，高度）初始化窗口
	hdc_cls();
	int n;
	char src, tmp, dst;
	while (1)
	{
		cct_cls();
		int op = menu();
		// 在坐标(50, 50)处绘制图片
		
		if (op == 0)
			break;
		cout << endl;
		if ((op >= 1 && op <= 4))
		{
			input(n, src, tmp, dst, op);
			if (op == 4)
				output_text(n, src, dst, 4);
			hanoi(n, src, tmp, dst, op);
		}
		else if (op == 5)
			output4(5, 'A', 'A', op);
		else if (op >= 6 && op <= 9)
		{
			input(n, src, tmp, dst, op);
			output5(n, src, dst, op);
			if (op >= 7 && op <= 8)
				hanoi(n, src, tmp, dst, op);
			else if (op == 9)
				hanoi_game(n, src, tmp, dst);
		}
		wait(op);
	}
	/*
	// 在坐标(50, 50)处绘制图片
	hdc_draw_image(50, 25, addr);

	// 释放资源
	hdc_release();
	Sleep(1000);
	*/
	return 0;
}