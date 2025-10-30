// 2451317 冯久恒 大数据
#include <iostream>
#include <Windows.h>
#include <math.h>
#include<conio.h>
using namespace std;

#include "../include/cmd_hdc_tools.h"

const double PI = 3.14159;
const int cx = 400;
const int cy = 400;
const int BLACK = RGB(0, 0, 0);

//究极利器(opt 1/2 画线/涂色  也可以1画粗线涂色,但注意此时要加一些偏移量  炒鸡好用！！！！)
// 给出三点，用弧将该三点连接，顺时针方向排列123，半径过小时会因误差过大而作图有偏差
static void FITTING_arc(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const int thinkness, const int RGB_value, int opt = 1)
{
	//计算圆心半径
	double A = x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2;
	double B = (x1 * x1 + y1 * y1) * (y3 - y2) + (x2 * x2 + y2 * y2) * (y1 - y3) + (x3 * x3 + y3 * y3) * (y2 - y1);
	double C = (x1 * x1 + y1 * y1) * (x2 - x3) + (x2 * x2 + y2 * y2) * (x3 - x1) + (x3 * x3 + y3 * y3) * (x1 - x2);
	double D = (x1 * x1 + y1 * y1) * (x3 * y2 - x2 * y3) + (x2 * x2 + y2 * y2) * (x1 * y3 - x3 * y1) + (x3 * x3 + y3 * y3) * (x2 * y1 - x1 * y2);
	double x0 = -B / (2 * A);
	double y0 = -C / (2 * A);
	double r = sqrt((B * B + C * C - 4 * A * D) / (4 * A * A));

	//计算起止角度
	double v01[2] = { x1 - x0,y1 - y0 };
	double L01 = sqrt(v01[0] * v01[0] + v01[1] * v01[1]);
	double  v03[2] = { x3 - x0,y3 - y0 };
	double L03 = sqrt(v03[0] * v03[0] + v03[1] * v03[1]);
	double Angle1_cos = (v01[0] * 0 + v01[1] * (-1)) / (L01 * 1);
	double Angle1 = acos(Angle1_cos) * 180 / PI;
	double Angle3_cos = (v03[0] * 0 + v03[1] * (-1)) / (L03 * 1);
	double Angle3 = acos(Angle3_cos) * 180 / PI;

	//利用叉乘调整顺逆
	Angle1 = Angle1 * v01[0] / abs(v01[0]);
	Angle3 = Angle3 * v03[0] / abs(v03[0]);

	if (1 == opt)
		hdc_arc((int)x0, (int)y0, (int)r, (int)Angle1, (int)Angle3, thinkness, RGB_value);
	else
		hdc_sector((int)x0, (int)y0, (int)r, (int)Angle1, (int)Angle3, true, thinkness, RGB_value);
}

const int color_1 = RGB(187, 207, 196);
static void draw_bg(const int base_x, const int base_y)
{
	hdc_rectangle(base_x - 390, base_y - 395, 780, 790, 0, true, 2, color_1);
	hdc_rectangle(base_x - 390, base_y - 390, 780, 780, 0, false, 5, BLACK);
}

// 画头
const int HEAD_color_1 = RGB(113, 146, 181);
const int HEAD_color_2 = RGB(78, 77, 75);
const int HEAD_color_8 = RGB(255, 248, 242);
const int HEAD_color_9 = RGB(255, 255, 255);
static void draw_head(const int base_x, const int base_y)
{
	int x1 = base_x - 81, y1 = base_y - 204;
	int x2 = base_x - 107, y2 = base_y - 276;
	hdc_circle(x2, y2, 72, 1, 1, HEAD_color_9);
	hdc_sector(x1, y1, 150, -20, 60, 1, 1, HEAD_color_1);
	hdc_sector(x2, y2, 72, 60, 280, 1, 1, HEAD_color_9);
	hdc_sector(x2, y2, 72, -80, 10, 1, 1, HEAD_color_1);
	hdc_arc(x1, y1, 150, -20, 60, 2, BLACK);
	hdc_arc(x2, y2, 72, -92, -20, 2, BLACK);
	hdc_ellipse(base_x - 46, base_y - 245, 78, 49, -28, 1, 1, HEAD_color_9);
	hdc_ellipse(base_x - 106, base_y - 254, 60, 34, -40, 1, 1, HEAD_color_9);
	hdc_ellipse(base_x - 97, base_y - 221, 53, 31, -5, 1, 1, HEAD_color_9);
	hdc_ellipse(base_x + 29, base_y - 212, 45, 38, -21, 1, 1, HEAD_color_9);
	hdc_ellipse(base_x + 57, base_y - 176, 38, 67, -20, 1, 1, HEAD_color_9);
	hdc_ellipse(base_x - 80, base_y + 142, 30, 40, -55, 1, 1, HEAD_color_8);
	FITTING_arc(base_x - 103, base_y - 303, base_x - 73, base_y - 308, base_x - 96, base_y - 289, 1, HEAD_color_9, 2);
	FITTING_arc(base_x - 101, base_y - 302, base_x - 115, base_y - 291, base_x - 139, base_y - 286, 1, HEAD_color_1, 2);
	FITTING_arc(base_x + 47, base_y - 280, base_x + 67, base_y - 268, base_x + 84, base_y - 232, 1, HEAD_color_2, 2);
	FITTING_arc(base_x + 84, base_y - 232, base_x + 105, base_y - 194, base_x + 119, base_y - 151, 1, HEAD_color_2, 2);
	
}

const int MOUTH_color_1 = RGB(200, 217, 233);
const int MOUTH_color_2 = RGB(255, 251, 239);
const int MOUTH_color_3 = RGB(202, 211, 226);
const int MOUTH_color_9 = RGB(96, 100, 109);
static void draw_mouth(const int base_x, const int base_y)
{
	hdc_triangle(base_x - 181, base_y - 270, base_x - 248, base_y - 231, base_x - 199, base_y - 223, true, 1, MOUTH_color_1);
	hdc_triangle(base_x - 292, base_y - 191, base_x - 248, base_y - 231, base_x - 259, base_y - 188, true, 1, MOUTH_color_1);
	hdc_triangle(base_x - 292, base_y - 191, base_x - 296, base_y - 180, base_x - 259, base_y - 188, true, 1, MOUTH_color_1);
	hdc_triangle(base_x - 152, base_y - 214, base_x - 248, base_y - 231, base_x - 259, base_y - 188, true, 1, MOUTH_color_1);
	hdc_triangle(base_x - 199, base_y - 223, base_x - 152, base_y - 214, base_x - 181, base_y - 270, true, 1, MOUTH_color_1);
	hdc_triangle(base_x - 203, base_y - 202, base_x - 194, base_y - 191, base_x - 147, base_y - 209, 1, 1, MOUTH_color_2);
	hdc_triangle(base_x - 158, base_y - 189, base_x - 194, base_y - 191, base_x - 147, base_y - 209, 1, 1, MOUTH_color_2);
	hdc_triangle(base_x - 158, base_y - 189, base_x - 118, base_y - 177, base_x - 147, base_y - 209, 1, 1, MOUTH_color_2);
	hdc_triangle(base_x - 132, base_y - 197, base_x - 118, base_y - 177, base_x - 147, base_y - 209, 1, 1, MOUTH_color_2);
	hdc_triangle(base_x - 132, base_y - 197, base_x - 118, base_y - 177, base_x - 100, base_y - 188, 1, 1, MOUTH_color_2);
	hdc_triangle(base_x - 148, base_y - 232, base_x - 181, base_y - 274, base_x - 144, base_y - 263, 1, 1, MOUTH_color_3);
	hdc_triangle(base_x - 148, base_y - 232, base_x - 127, base_y - 262, base_x - 144, base_y - 263, 1, 1, MOUTH_color_3);
	hdc_triangle(base_x - 148, base_y - 232, base_x - 127, base_y - 262, base_x - 97, base_y - 250, 1, 1, MOUTH_color_3);
	hdc_triangle(base_x - 108, base_y - 282, base_x - 127, base_y - 262, base_x - 97, base_y - 250, 1, 1, MOUTH_color_3);
	FITTING_arc(base_x - 296, base_y - 180, base_x - 233, base_y - 212, base_x - 177, base_y - 228, 3, MOUTH_color_9);

	FITTING_arc(base_x - 157, base_y - 188, base_x - 131, base_y - 182, base_x - 97, base_y - 164, 1, BLACK);
	FITTING_arc(base_x - 296, base_y - 180, base_x - 238, base_y - 233, base_x - 181, base_y - 265, 1, BLACK);
	FITTING_arc(base_x - 156, base_y - 191, base_x - 190, base_y - 190, base_x - 204, base_y - 199, 1, BLACK);
	FITTING_arc(base_x + 56, base_y - 227, base_x + 0, base_y - 183, base_x - 75, base_y - 181, 1, BLACK);
	FITTING_arc(base_x + 66, base_y + 149, base_x + 59, base_y + 177, base_x + 51, base_y + 195, 1, BLACK);
	FITTING_arc(base_x - 296, base_y - 181, base_x - 223, base_y - 198, base_x - 150, base_y - 207, 1, BLACK);
}

const int BODY_color_1 = RGB(187, 187, 179);
const int BODY_color_2 = RGB(168, 157, 137);
const int BODY_color_3 = RGB(198, 202, 203);
const int BODY_color_9 = RGB(255, 255, 255);
static void draw_body(const int base_x, const int base_y)
{
	hdc_ellipse(base_x - 23, base_y - 51, 123, 209, -8, 1, 1, BODY_color_9);
	hdc_ellipse(base_x + 11, base_y - 235, 45, 63, -34, 1, 1, BODY_color_9);
	hdc_triangle(base_x - 139, base_y - 67, base_x - 143, base_y + 81, base_x - 89, base_y + 82, true, 1, BODY_color_3);
	hdc_triangle(base_x - 91, base_y + 67, base_x - 143, base_y + 81, base_x - 89, base_y + 82, true, 1, BODY_color_3);
	hdc_triangle(base_x - 91, base_y + 67, base_x - 143, base_y + 117, base_x - 89, base_y + 82, true, 1, BLACK);
}

// 画眼睛
const int EYE_color_1 = RGB(233, 104, 98);
const int EYE_color_2 = RGB(51, 59, 106);
const int EYE_color_3 = RGB(80, 31, 30);
const int EYE_color_4 = RGB(255, 200, 199);
static void draw_eye(const int base_x, const int base_y)
{
	int x1 = base_x - 87, y1 = base_y - 279;
	int x2 = base_x - 89, y2 = base_y - 279;
	int x3 = base_x - 78, y3 = base_y - 287;
	hdc_ellipse(x1, y1, 20, 16, -18, 1, 1, EYE_color_1);
	hdc_ellipse(x2, y2, 8, 7, -20, 1, 1, EYE_color_2);
	hdc_ellipse(x1, y1, 21, 17, -22, 0, 2, EYE_color_3);
	hdc_ellipse(x3, y3, 4, 5, -34, 1, 1, EYE_color_4);
}

const int LEG_color_1 = RGB(208, 200, 188);
const int LEG_color_2 = RGB(225, 189, 137);
const int LEG_color_3 = RGB(255, 253, 228);
static void draw_legs(const int base_x, const int base_y)
{
	// 左腿
	hdc_rectangle(base_x - 147, base_y + 80, 55, 31, 7, 1, 2, LEG_color_1);
	hdc_triangle(base_x - 146, base_y + 99, base_x - 92, base_y + 112, base_x - 134, base_y + 174, true, 1, LEG_color_1);
	hdc_triangle(base_x - 98, base_y + 150, base_x - 92, base_y + 112, base_x - 134, base_y + 174, true, 1, LEG_color_1);
	hdc_triangle(base_x - 98, base_y + 150, base_x - 98, base_y + 178, base_x - 134, base_y + 174, true, 1, LEG_color_1);
	hdc_triangle(base_x - 128, base_y + 203, base_x - 98, base_y + 178, base_x - 134, base_y + 174, true, 1, LEG_color_1);
	hdc_triangle(base_x - 128, base_y + 203, base_x - 98, base_y + 178, base_x - 112, base_y + 202, true, 1, LEG_color_1);
	hdc_triangle(base_x - 128, base_y + 203, base_x - 109, base_y + 220, base_x - 112, base_y + 202, true, 1, LEG_color_1);
	hdc_triangle(base_x - 131, base_y + 220, base_x - 109, base_y + 220, base_x - 112, base_y + 202, true, 1, LEG_color_1);
	hdc_triangle(base_x - 132, base_y + 219, base_x - 110, base_y + 220, base_x - 137, base_y + 240, true, 1, LEG_color_2);
	hdc_triangle(base_x - 102, base_y + 257, base_x - 110, base_y + 220, base_x - 137, base_y + 240, true, 1, LEG_color_2);
	hdc_triangle(base_x - 102, base_y + 257, base_x - 114, base_y + 291, base_x - 137, base_y + 240, true, 1, LEG_color_2);
	hdc_triangle(base_x - 138, base_y + 289, base_x - 114, base_y + 291, base_x - 137, base_y + 240, true, 1, LEG_color_2);
	hdc_triangle(base_x - 115, base_y + 292, base_x - 149, base_y + 365, base_x - 136, base_y + 277, 1, 1, LEG_color_3);
	hdc_triangle(base_x - 115, base_y + 292, base_x - 149, base_y + 365, base_x - 129, base_y + 364, 1, 1, LEG_color_3);
		
	// 右腿
	hdc_triangle(base_x + 25, base_y + 183, base_x + 71, base_y + 129, base_x + 15, base_y + 231, 1, 1, LEG_color_1);
	hdc_triangle(base_x + 50, base_y + 197, base_x + 71, base_y + 129, base_x + 15, base_y + 231, 1, 1, LEG_color_1);
	hdc_triangle(base_x + 50, base_y + 197, base_x + 52, base_y + 229, base_x + 15, base_y + 231, 1, 1, LEG_color_1);
	hdc_triangle(base_x + 16, base_y + 230, base_x + 51, base_y + 223, base_x + 17, base_y + 255, 1, 1, LEG_color_2);
	hdc_triangle(base_x + 52, base_y + 285, base_x + 51, base_y + 223, base_x + 17, base_y + 255, 1, 1, LEG_color_2);
	hdc_triangle(base_x + 52, base_y + 285, base_x + 24, base_y + 291, base_x + 17, base_y + 255, 1, 1, LEG_color_2);
	hdc_triangle(base_x + 53, base_y + 273, base_x + 52, base_y + 366, base_x + 25, base_y + 283, 1, 1, LEG_color_3);
	hdc_triangle(base_x + 53, base_y + 273, base_x + 52, base_y + 366, base_x + 67, base_y + 366, 1, 1, LEG_color_3);
}


const int WING_color_1 = RGB(147, 163, 186);
const int WING_color_2 = RGB(18, 19, 27);
const int WING_color_3 = RGB(193, 196, 201);
const int WING_color_4 = RGB(220, 210, 208);
const int WING_color_5 = RGB(255, 255, 255);
const int WING_color_6 = RGB(124, 105, 88);
const int WING_color_7 = RGB(118, 118, 116);
static void draw_wings(const int base_x, const int base_y)
{
	// 左翅
	hdc_ellipse(base_x - 16, base_y + 185, 38, 43, 0, 1, 1, WING_color_4);
	hdc_triangle(base_x - 50, base_y + 172, base_x - 15, base_y + 229, base_x - 97, base_y + 141, 1, 1, WING_color_7);
	hdc_triangle(base_x - 32, base_y + 251, base_x - 15, base_y + 229, base_x - 97, base_y + 141, 1, 1, WING_color_7);
	hdc_triangle(base_x - 32, base_y + 251, base_x - 104, base_y + 178, base_x - 97, base_y + 141, 1, 1, WING_color_7);
	
	hdc_triangle(base_x - 157, base_y - 189, base_x - 172, base_y - 166, base_x - 113, base_y - 172, 1, 1, WING_color_1);
	hdc_triangle(base_x - 163, base_y - 157, base_x - 172, base_y - 166, base_x - 113, base_y - 172, 1, 1, WING_color_1);
	hdc_triangle(base_x - 163, base_y - 157, base_x - 176, base_y - 80, base_x - 113, base_y - 172, 1, 1, WING_color_1);
	hdc_triangle(base_x - 139, base_y - 101, base_x - 176, base_y - 80, base_x - 113, base_y - 172, 1, 1, WING_color_1);
	hdc_triangle(base_x - 177, base_y - 78, base_x - 139, base_y - 102, base_x - 180, base_y - 35, 1, 1, WING_color_1);
	hdc_triangle(base_x - 163, base_y - 8, base_x - 139, base_y - 102, base_x - 180, base_y - 35, 1, 1, WING_color_1);
	hdc_triangle(base_x - 163, base_y - 8, base_x - 166, base_y + 31, base_x - 180, base_y - 35, 1, 1, WING_color_1);
	hdc_triangle(base_x - 165, base_y + 31, base_x - 178, base_y + 26, base_x - 180, base_y - 35, 1, 1, WING_color_1);
	hdc_triangle(base_x - 139, base_y - 104, base_x - 128, base_y - 52, base_x - 144, base_y + 5, 1, 1, WING_color_3);
	hdc_triangle(base_x - 139, base_y - 104, base_x - 168, base_y - 7, base_x - 147, base_y + 85, 1, 1, WING_color_3);
	hdc_triangle(base_x - 165, base_y + 33, base_x - 158, base_y + 95, base_x - 168, base_y + 70, 1, 1, WING_color_1);
	hdc_triangle(base_x - 165, base_y + 33, base_x - 178, base_y + 27, base_x - 168, base_y + 70, 1, 1, WING_color_1);
	hdc_triangle(base_x - 165, base_y + 33, base_x - 158, base_y + 95, base_x - 148, base_y + 84, 1, 1, WING_color_1);
	hdc_triangle(base_x - 151, base_y + 118, base_x - 158, base_y + 95, base_x - 148, base_y + 84, 1, 1, WING_color_2);
	hdc_triangle(base_x - 151, base_y + 118, base_x - 143, base_y + 109, base_x - 148, base_y + 84, 1, 1, WING_color_2);
	hdc_triangle(base_x - 151, base_y + 118, base_x - 143, base_y + 109, base_x - 139, base_y + 138, 1, 1, WING_color_2);
	hdc_line(base_x - 163, base_y - 149, base_x - 171, base_y - 120, 2, BLACK);
	hdc_line(base_x - 163, base_y + 27, base_x - 146, base_y + 82, 3, BLACK);
	hdc_line(base_x - 150, base_y + 78, base_x - 129, base_y - 47, 3, BLACK);

	// 右翅
	hdc_ellipse(base_x + 60, base_y + 56, 68, 140, 10, 1, 1, WING_color_5);
	hdc_ellipse(base_x + 74, base_y - 65, 56, 125, 0, 1, 1, WING_color_5);
	hdc_triangle(base_x + 91, base_y + 103, base_x + 102, base_y + 151, base_x + 57, base_y + 187, 1, 1, WING_color_6);
	hdc_triangle(base_x + 135, base_y + 24, base_x + 104, base_y + 146, base_x + 130, base_y - 76, 1, 1, WING_color_5);
	hdc_triangle(base_x + 135, base_y + 24, base_x + 104, base_y + 146, base_x + 100, base_y + 70, 1, 1, WING_color_4);
	hdc_triangle(base_x + 122, base_y - 65, base_x + 91, base_y + 105, base_x + 82, base_y - 67, 1, 1, WING_color_4);
	hdc_triangle(base_x + 122, base_y - 65, base_x + 86, base_y - 180, base_x + 82, base_y - 67, 1, 1, WING_color_5);
	hdc_triangle(base_x + 122, base_y - 65, base_x + 91, base_y + 105, base_x + 130, base_y + 7, 1, 1, WING_color_4);
	

	// 肚子
	hdc_ellipse(base_x + 22, base_y - 92, 95, 148, -8, 1, 1, BODY_color_9);

	FITTING_arc(base_x - 128, base_y + 205, base_x - 138, base_y + 150, base_x - 145, base_y + 87, 1, BLACK);
	FITTING_arc(base_x - 91, base_y + 75, base_x - 97, base_y + 147, base_x - 110, base_y + 202, 1, BLACK);
	FITTING_arc(base_x - 134, base_y + 288, base_x - 137, base_y + 256, base_x - 128, base_y + 205, 1, BLACK);
	FITTING_arc(base_x - 110, base_y + 202, base_x - 103, base_y + 255, base_x - 115, base_y + 289, 1, BLACK);
	FITTING_arc(base_x - 66, base_y + 72, base_x - 107, base_y + 26, base_x - 130, base_y - 92, 1, BLACK);
	FITTING_arc(base_x + 15, base_y + 85, base_x - 20, base_y + 92, base_x - 66, base_y + 72, 1, BLACK);
	FITTING_arc(base_x + 68, base_y + 10, base_x + 48, base_y + 49, base_x + 15, base_y + 85, 1, BLACK);
	FITTING_arc(base_x + 44, base_y + 87, base_x - 26, base_y + 124, base_x - 94, base_y + 98, 1, BLACK);
	FITTING_arc(base_x - 141, base_y + 139, base_x - 181, base_y - 32, base_x - 171, base_y - 120, 1, BLACK);
	FITTING_arc(base_x + 132, base_y - 73, base_x + 137, base_y - 6, base_x + 104, base_y + 152, 1, BLACK);
	FITTING_arc(base_x - 163, base_y - 149, base_x - 168, base_y - 169, base_x - 162, base_y - 188, 1, BLACK);
	FITTING_arc(base_x - 13, base_y + 233, base_x - 21, base_y + 246, base_x - 37, base_y + 250, 1, BLACK);
	FITTING_arc(base_x - 37, base_y + 250, base_x - 72, base_y + 218, base_x - 105, base_y + 178, 1, BLACK);
	FITTING_arc(base_x + 131, base_y - 42, base_x + 125, base_y + 28, base_x + 96, base_y + 102, 1, BLACK);
	FITTING_arc(base_x + 65, base_y - 30, base_x + 85, base_y + 33, base_x + 97, base_y + 102, 1, BLACK);
	FITTING_arc(base_x + 51, base_y - 274, base_x + 129, base_y - 95, base_x + 135, base_y - 33, 1, BLACK);
	FITTING_arc(base_x + 92, base_y + 107, base_x + 89, base_y + 159, base_x + 58, base_y + 186, 1, BLACK);
	FITTING_arc(base_x + 12, base_y + 227, base_x - 2, base_y + 235, base_x - 16, base_y + 229, 1, BLACK);
	FITTING_arc(base_x + 26, base_y + 289, base_x + 14, base_y + 251, base_x + 26, base_y + 186, 1, BLACK);
	FITTING_arc(base_x - 94, base_y + 145, base_x - 50, base_y + 177, base_x - 17, base_y + 232, 1, BLACK);
	FITTING_arc(base_x + 23, base_y + 112, base_x + 28, base_y + 172, base_x + 13, base_y + 216, 1, BLACK);
	hdc_line(base_x + 52, base_y + 194, base_x + 53, base_y + 279, 1, BLACK);

	hdc_line(base_x - 140, base_y + 285, base_x - 149, base_y + 364, 1, BLACK);
	hdc_line(base_x - 113, base_y + 291, base_x - 129, base_y + 364, 1, BLACK);
	hdc_line(base_x + 28, base_y + 292, base_x + 48, base_y + 364, 1, BLACK);
	hdc_line(base_x + 54, base_y + 288, base_x + 68, base_y + 364, 1, BLACK);

}

void hdc_draw_cartoon_2451317(const int base_x, const int base_y)
{
	hdc_cls();
	draw_bg(base_x, base_y);
	draw_head(base_x, base_y);
	draw_body(base_x, base_y);
	draw_legs(base_x, base_y);
	draw_wings(base_x, base_y);
	draw_mouth(base_x, base_y);
	draw_eye(base_x, base_y);
}