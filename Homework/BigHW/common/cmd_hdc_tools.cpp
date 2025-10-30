// 2451317 冯久恒 大数据

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */
static const double DEG = PI / 180.0;
/* 此处允许添加自定义函数，但仅限static，即外部不可见 */

/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
            const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);
	
	cct_setcursor(CCT_CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
    /* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
            const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画一个指定粗细的点(用画实心圆来模拟)
  输入参数：const int x			：x坐标，左上角为(0,0)
            const int y			：y坐标，左上角为(0,0)
			const int thickness	：点的粗细，下限位1，上限不限(如过大会导致不完全填充)（有缺省值）
			const int RGB_value	：点的颜色（有缺省值）
  返 回 值：
  说    明：改进运行效率
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

	const int tn_end = (tn <= 1) ? 1 : tn/2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/* 用画圆的方式模拟粗点 */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle ++) {
			/* 注意，系统的坐标轴，0°在圆的最下方 */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}
#if 0
	/* 放开此注释，可以看到一个粗点用了几个像素点组成 */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_base_point/hdc_base_line函数的组合
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：画线段
  输入参数：const int x1		：起点的x
            const int y1		：起点的y
			const int x2		：终点的x
			const int y2		：终点的y
			const int thickness	：线段的粗细（有缺省值）
			const int RGB_value	：线段的颜色（有缺省值）
  返 回 值：
  说    明：本函数可以用基于hdc_point的组合（速度慢）
                  也可以用hdc_base_point/hdc_base_line的组合（速度快）
***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	const double dx = x2 - x1;
	const double dy = y2 - y1;
	const double len = sqrt(dx * dx + dy * dy);

	if (len < 1e-6)
		return;
	const double nx = -dy / len;
	const double ny = dx / len;
	const double half = (thickness - 1) / 2.0;

	for (double k = -half; k <= half; k += 1.0) 
	{
		double sx1 = x1 + nx * k;
		double sy1 = y1 + ny * k;
		double sx2 = x2 + nx * k;
		double sy2 = y2 + ny * k;
		double dx2 = sx2 - sx1;
		double dy2 = sy2 - sy1;
		int steps = (int)(fabs(dx2) > fabs(dy2) ? fabs(dx2) : fabs(dy2));
		double xInc = dx2 / steps;
		double yInc = dy2 / steps;
		double x = sx1, y = sy1;
		for (int i = 0; i <= steps; i++) 
		{
			hdc_point((int)(x + 0.5), (int)(y + 0.5), 1);
			x += xInc;
			y += yInc;
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
            const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);
	// 绘制三条边
	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x2, y2, x3, y3, thickness, RGB_value);
	hdc_line(x3, y3, x1, y1, thickness, RGB_value);

	if (!filled)
		return;

	int minY = min(y1, min(y2, y3)), maxY = max(y1, max(y2, y3));
	for (int y = minY; y <= maxY; ++y) 
	{
		double xints[3];
		int cnt = 0;
		static void (*intersect)(int, int, int, int, int, double*, int&) = [](int xa, int ya, int xb, int yb, int yscan, double* arr, int& count) 
		{
			if ((yscan >= ya && yscan < yb) || (yscan >= yb && yscan < ya)) 
			{
				double xint = xa + (double)(yscan - ya) * (xb - xa) / (yb - ya);
				arr[count++] = xint;
			}
		};
		intersect(x1, y1, x2, y2, y, xints, cnt);
		intersect(x2, y2, x3, y3, y, xints, cnt);
		intersect(x3, y3, x1, y1, y, xints, cnt);
		if (cnt >= 2) 
		{
			if (xints[0] > xints[1]) swap(xints[0], xints[1]);
			hdc_base_line((int)xints[0], y, (int)xints[1], y);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
            const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	const int w = (width < 1 ? 1 : width);
	const int h = (high < 1 ? 1 : high);

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	if (rotation_angles == 0) 
	{
		int x1 = left_up_x;
		int y1 = left_up_y;
		int x2 = x1 + w;
		int y2 = y1 + h - 1;
		if (x1 < 0 || x2 >= _Width_ || y1 < 0 || y2 >= _High)
			return;
		if (h == 1) 
		{
			hdc_base_line(x1, y1, x2, y1);
			return;
		}
		// 不填充：画边框
		if (!filled) 
		{
			hdc_line(x1, y1, x2, y1, thickness, RGB_value); // 上边
			hdc_line(x1, y2, x2, y2, thickness, RGB_value); // 下边
			hdc_line(x1, y1, x1, y2, thickness, RGB_value); // 左边
			hdc_line(x2, y1, x2, y2, thickness, RGB_value); // 右边
		}
		else
			for (int y = y1; y <= y2; ++y)
				hdc_base_line(x1, y, x2, y);
		return;
	}

	double theta = rotation_angles * PI / 180.0;
	double cos_t = cos(theta), sin_t = sin(theta);
	int x1 = left_up_x, y1 = left_up_y;
	int x2 = static_cast<int>(x1 + w * cos_t), y2 = static_cast<int>(y1 + w * sin_t);
	int x3 = static_cast<int>(x2 - h * sin_t), y3 = static_cast<int>(y2 + h * cos_t);
	int x4 = static_cast<int>(x1 - h * sin_t), y4 = static_cast<int>(y1 + h * cos_t);

	if (h <= 1) 
	{
		hdc_base_line(x1, y1, x2, y2);
		return;
	}
	hdc_line(x1, y1, x2, y2, thickness, RGB_value);
	hdc_line(x2, y2, x3, y3, thickness, RGB_value);
	hdc_line(x3, y3, x4, y4, thickness, RGB_value);
	hdc_line(x4, y4, x1, y1, thickness, RGB_value);

	if (!filled)
		return;

	int minY = min(min(y1, y2), min(y3, y4)), maxY = max(max(y1, y2), max(y3, y4));
	for (int y = minY; y <= maxY; ++y) 
	{
		double xints[4];
		int cnt = 0;
		if ((y >= y1 && y < y2) || (y >= y2 && y < y1))
			xints[cnt++] = x1 + (double)(y - y1) * (x2 - x1) / (y2 - y1);
		if ((y >= y2 && y < y3) || (y >= y3 && y < y2))
			xints[cnt++] = x2 + (double)(y - y2) * (x3 - x2) / (y3 - y2);
		if ((y >= y3 && y < y4) || (y >= y4 && y < y3))
			xints[cnt++] = x3 + (double)(y - y3) * (x4 - x3) / (y4 - y3);
		if ((y >= y4 && y < y1) || (y >= y1 && y < y4))
			xints[cnt++] = x4 + (double)(y - y4) * (x1 - x4) / (y1 - y4);
		if (cnt >= 2) 
		{
			for (int i = 0; i < cnt - 1; ++i)
				for (int j = i + 1; j < cnt; ++j)
					if (xints[i] > xints[j])
						swap(xints[i], xints[j]);
			for (int i = 0; i + 1 < cnt; i += 2)
				hdc_base_line(static_cast<int>(xints[i]), y, static_cast<int>(xints[i + 1]), y);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及边长，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
            const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	if (radius <= 0)
		return;

	double start_rad = angle_begin * DEG;
	double end_rad = angle_end * DEG;
	if (start_rad > end_rad)
		end_rad += 2 * PI;

	const double step = 1.0 / radius;
	for (int t = 0; t < thickness; ++t) 
	{
		double offset = (t - (thickness - 1) / 2.0);
		for (double theta = start_rad; theta <= end_rad; theta += step)
		{
			int x = static_cast<int>(point_x + (radius + offset) * sin(theta) + 0.5);
			int y = static_cast<int>(point_y - (radius + offset) * cos(theta) + 0.5);
			hdc_point(x, y, 1);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	if (radius <= 0)
		return;

	double start_rad = angle_begin * DEG;
	double end_rad = angle_end * DEG;
	if (start_rad > end_rad)
		end_rad += 2 * PI;

	const double step = 1.0 / radius;
	if (filled) 
	{
		const double step = 1.0 / radius;
		for (double theta = start_rad; theta <= end_rad; theta += step)
		{
			int x = static_cast<int>(point_x + radius * sin(theta) + 0.5);
			int y = static_cast<int>(point_y - radius * cos(theta) + 0.5);
			hdc_line(point_x, point_y, x, y, thickness);
		}
	}
	else
		hdc_arc(point_x, point_y, radius, angle_begin, angle_end, thickness, RGB_value);

	int diff = abs((angle_end - angle_begin) % 360);
	if (diff != 0) 
	{
		int xs = static_cast<int>(point_x + radius * sin(start_rad) + 0.5);
		int ys = static_cast<int>(point_y - radius * cos(start_rad) + 0.5);
		int xe = static_cast<int>(point_x + radius * sin(end_rad) + 0.5);
		int ye = static_cast<int>(point_y - radius * cos(end_rad) + 0.5);
		hdc_line(point_x, point_y, xs, ys, thickness);
		hdc_line(point_x, point_y, xe, ye, thickness);
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	if (radius <= 0)
		return;

	if (filled)
		hdc_sector(point_x, point_y, radius, 0, 360, true, 1, RGB_value);
	else
		hdc_arc(point_x, point_y, radius, 0, 360, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	if (radius_a <= 0 || radius_b <= 0)
		return;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	const double rot = rotation_angles * DEG;
	const double cos_t = cos(rot), sin_t = sin(rot);
	const double step = 1.0 / max(radius_a, radius_b);

	for (int t = 0; t < thickness; ++t) 
	{
		double offset = (t - (thickness - 1) / 2.0);
		for (double theta = 0; theta <= 2 * PI + step; theta += step) 
		{
			double x_local = (radius_a + offset) * cos(theta);
			double y_local = (radius_b + offset) * sin(theta);
			double x_rot = x_local * cos_t - y_local * sin_t;
			double y_rot = x_local * sin_t + y_local * cos_t;
			int x = static_cast<int>(point_x + x_rot + 0.5), y = static_cast<int>(point_y + y_rot + 0.5);

			hdc_point(x, y);
		}
	}
	if (filled) 
	{
		for (int j = -radius_b; j <= radius_b; ++j) 
		{
			double y_local = static_cast<double>(j);
			double term = 1.0 - (y_local * y_local) / (radius_b * radius_b);
			if (term < 0.0)
				continue;
			double x_local = radius_a * sqrt(term);
			double xl = -x_local, yl = y_local;
			double xr = x_local, yr = y_local;

			double xl_rot = xl * cos_t - yl * sin_t;
			double yl_rot = xl * sin_t + yl * cos_t;
			double xr_rot = xr * cos_t - yr * sin_t;
			double yr_rot = xr * sin_t + yr * cos_t;

			int x1 = static_cast<int>(point_x + xl_rot + 0.5);
			int y1 = static_cast<int>(point_y + yl_rot + 0.5);
			int x2 = static_cast<int>(point_x + xr_rot + 0.5);
			int y2 = static_cast<int>(point_y + yr_rot + 0.5);

			hdc_line(x1, y1, x2, y2, thickness, RGB_value);
		}
	}
}

#endif !HDC_SERIES_BY_TEACHER
