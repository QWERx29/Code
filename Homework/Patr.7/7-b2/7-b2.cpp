// 2451317 冯久恒 计算机
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<Windows.h>
#include"cmd_console_tools.h"
#include"7-b2.h"
using namespace std;

/* 1、按需加入头文件
   2、不允许定义全局变量，包括静态全局，但不限制const及define
   3、允许定义需要的结构体、函数等，但仅限本源程序文件使用 */
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：定义仅本源程序文件需要的函数，设置为static即可
***************************************************************************/
static bool calc_len(const int l, const char* title)
{
	int _l = strlen(title);
	if (_l <= l)
		return false;
	else
		return true;
}
static void show_border_1(const char* left, const char* middle, const char* right, int stt_x, int stt_y, int len, int fc, int bc)
{
	cct_showstr(stt_x, stt_y, left, fc, bc, 1, -1);
	cct_showstr(stt_x + 2, stt_y, middle, fc, bc, len, -1);
	cct_showstr(stt_x + (len + 1) * 2, stt_y, right, fc, bc, 1, -1);
}
static int read_arrow(int kc2)
{
	int arr = 0;
	switch (kc2)
	{
		case KB_ARROW_UP:
			arr = -1;
			break;
		case KB_ARROW_DOWN:
			arr = +1;
			break;
	}
	return arr;
}

static void show_title(const int x, const int y, const int len, const char* title, const int fc, const int bc)
{
	int stt_x, stt_y;
	if (calc_len(len,title))
		stt_x = x + 2, stt_y = y;
	else
		stt_x = x + len / 2 - 2, stt_y = y;
	if (stt_x % 2 == 1)
		stt_x++;
	cct_showstr(stt_x, stt_y, title, fc, bc, 1, -1);
}
static void refresh_menu_display(const char menu[][MAX_ITEM_LEN], const struct PopMenu* original_para, int top_index, int selected, int total_items, int len)
{
	int _l = len;
	int cols, lines, buffer_cols, buffer_lines;
	bool f = false;
	cct_getconsoleborder(cols, lines, buffer_cols, buffer_lines);
	for (int i = 0; i < original_para->high; i++)
	{
		int cnt = 0;
		int item_index = top_index + i;
		int y_pos = original_para->start_y + i + 1;
		_l = len;
		cct_showstr(original_para->start_x + 2, y_pos, " ", original_para->bg_color, original_para->fg_color, _l, -1);
		if (item_index < total_items)
		{
			int bg = (item_index == selected) ? original_para->fg_color : original_para->bg_color;
			int fg = (item_index == selected) ? original_para->bg_color : original_para->fg_color;
			int t = strlen(menu[item_index]);
			if (t < original_para->width)
			{
				if (original_para->start_x + t >= cols)
				{
					int menu_pos = 0;
					int display_pos = 0;
					while (display_pos < cols - original_para->start_x - 2 && menu[item_index][menu_pos] != '\0')
					{
						unsigned char c = (unsigned char)menu[item_index][menu_pos];
						if (c < 0x80)
							display_pos++, menu_pos++;
						else if (c >= 0xA1 && c <= 0xFE)
						{
							if (display_pos + 2 > cols - original_para->start_x - 2)
								break;
							unsigned char next_c = (unsigned char)menu[item_index][menu_pos + 1];
							if (next_c >= 0xA1 && next_c <= 0xFE)
								display_pos += 2, menu_pos += 2;
							else
								display_pos += 2, menu_pos += 2;
						}
						else
							display_pos++, menu_pos++;
					}
					if (display_pos < cols - original_para->start_x - 2)
						_l = len - 1;
				}
				cct_showstr(original_para->start_x + 2, y_pos, menu[item_index], bg, fg, 1, _l);
			}
			else
			{
				int menu_pos = 0;
				int display_pos = 0;
				while (display_pos < _l && menu[item_index][menu_pos] != '\0')
				{
					unsigned char c = (unsigned char)menu[item_index][menu_pos];
					if (c < 0x80)
						display_pos++, menu_pos++;
					else if (c >= 0xA1 && c <= 0xFE)
					{
						if (display_pos + 2 > _l)
							break;
						unsigned char next_c = (unsigned char)menu[item_index][menu_pos + 1];
						if (next_c >= 0xA1 && next_c <= 0xFE)
							display_pos += 2, menu_pos += 2;
						else
							display_pos += 2, menu_pos += 2;
					}
					else
						display_pos++, menu_pos++;
				}
				char new_menu[MAX_ITEM_LEN] = { 0 };
				strncpy(new_menu, menu[item_index], menu_pos);
				new_menu[menu_pos] = '\0';
				if (display_pos < _l)
				{
					int spc = _l - display_pos;
					for (int k = 0; k < spc; k++)
						strcat(new_menu, " ");
				}
				cct_showstr(original_para->start_x + 2, y_pos, new_menu, bg, fg, 1, -1);
			}
		}
	}
}
/***************************************************************************
  函数名称：
  功    能：供测试用例调用的函数，函数声明在头文件中
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int pop_menu(const char menu[][MAX_ITEM_LEN], const struct PopMenu* original_para)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int row = 0;
	int len = calc_len(original_para->width, original_para->title) ? strlen(original_para->title) : original_para->width;
	if (len % 2 == 1)
		len++;
	for (int i = 0; ; i++)
	{
		if (menu[i] == NULL || menu[i][0] == '\0')
			break;
		row++;
	}
	int top_index = 0;
	int selected = 0;
	cct_gotoxy(original_para->start_x, original_para->start_y);
	show_border_1("╔", "═", "╗", original_para->start_x, original_para->start_y, len / 2, original_para->bg_color, original_para->fg_color);
	show_title(original_para->start_x, original_para->start_y, original_para->width, original_para->title, original_para->bg_color, original_para->fg_color);
	for (int i = 0; i < original_para->high; i++)
	{
		cct_gotoxy(original_para->start_x + 2, original_para->start_y + i + 1);
		show_border_1("║", "  ", "║", original_para->start_x, original_para->start_y + i + 1,	len / 2, original_para->bg_color, original_para->fg_color);
	}
	show_border_1("╚", "═", "╝", original_para->start_x,	original_para->start_y + original_para->high + 1, len / 2, original_para->bg_color, original_para->fg_color);
	refresh_menu_display(menu, original_para, top_index, selected, row, len);
	while (1)
	{
		int mx = 0, my = 0, ma = 0, kc1 = 0, kc2 = 0;
		int ev = cct_read_keyboard_and_mouse(mx, my, ma, kc1, kc2);
		int prev_selected = selected;
		if (ev == CCT_KEYBOARD_EVENT) 
		{
			if (kc1 == 13)
				break;
			if (kc1 == 0xe0) 
			{
				int op = read_arrow(kc2);
				if (op != 0) 
				{
					int new_selected = selected + op;
					if (new_selected >= 0 && new_selected < row) 
					{
						selected = new_selected;
						if (selected < top_index)
							top_index = selected;
						else if (selected >= top_index + original_para->high)
							top_index = selected - original_para->high + 1;
					}
				}
			}
		}
		if (prev_selected != selected || (selected >= top_index && selected < top_index + original_para->high))
			refresh_menu_display(menu, original_para, top_index, selected, row, len);
	}
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	if (row == 0) 
		return 0;
	else
		return (selected >= 0 && selected < row) ? selected + 1 : 0;
}
