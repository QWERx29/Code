// 2451317 冯久恒 大数据
#include <math.h>
#include <conio.h>
using namespace std;

#include "../include/cmd_hdc_tools.h"

static const double PI = 3.14159;
const int cx = 400;
const int cy = 400;

void hdc_draw_Mathematical_curve_2451317()
{
	hdc_cls();
	
	double a = 80, k = 4, rotation = 0;
	const double deg2rad = PI / 180.0;
	double rot = rotation * deg2rad;
	double cos_t = cos(rot), sin_t = sin(rot);
	while (1)
	{
		hdc_cls();
		cct_showstr(2, 1, "<可变化的玫瑰曲线 - r=asin(kθ)>", 7, 0);
		cct_showstr(2, 2, "[按 a 变大；按 d 变小；按 w 增加花瓣数；按 s 减少花瓣数；按 p 切换奇数/偶数瓣；按 c 退出] ", 7, 0);
		double step = 1.0 / a;

		for (double theta = 0.0; theta <= 360.0; theta += step)
		{
			double rad = theta * deg2rad;
			double r = a * sin(k * rad);

			// 极坐标转直角坐标
			double x_local = r * cos(rad), y_local = r * sin(rad);

			// 应用整体旋转（顺时针为正）
			double x_rot = x_local * cos_t - y_local * sin_t, y_rot = x_local * sin_t + y_local * cos_t;

			// 绘制点
			int x = static_cast<int>(cx + x_rot + 0.5), y = static_cast<int>(cy + y_rot + 0.5);
			hdc_point(x, y);
		}
		char ch;
		int loop = 1;
		while (loop)
		{
			ch = _getch();
			switch (ch)
			{
			case 'a':
				a += 10;
				loop = 0;
				break;
			case 'd':
				if (a > 10)
					a -= 10;
				loop = 0;
				break;
			case 's':
				if (k > 3)
					k -= 2;
				loop = 0;
				break;
			case 'w':
				k += 2;
				loop = 0;
				break;
			case 'p':
				if (static_cast<int>(k) % 2 == 0)
					k++;
				else
					k--;
				loop = 0;
				break;
			case 'c':  //按C退出
				return;
			default:
				continue;
				break;
			}
		}
	}
}