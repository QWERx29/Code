// 2451317 冯久恒 计算机
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
using namespace std;

/***************************************************************************
函数名称：select_op
功    能：
输入参数：
返 回 值：对应选项
说    明：
***************************************************************************/
int select_op(const char* valid_chars)
{
	while (1)
	{
		char op = _getch();
		for (int i = 0; valid_chars[i] != '\0'; i++)
		{
			if (op == valid_chars[i] || op == tolower(valid_chars[i]))
			{
# if 1
				cout << op;
# endif
				return op;
			}
		}
	}
}

// 输出菜单测试
// simple_menu函数，支持三种菜单形式
char simple_menu(const char* menu_items, const char* valid_chars)
{
	cout << menu_items << endl;
	char op = select_op(valid_chars);
	cout << op << endl;
	return op;
}

// 重载版本：处理一维字符指针数组（以NULL结束）
char simple_menu(const char* menu_items[], const char* valid_chars)
{
	for (int i = 0; menu_items[i] != NULL; i++)
		cout << menu_items[i] << endl;
	char op = select_op(valid_chars);
	cout << op << endl;
	return op;
}

// 重载版本：处理二维字符数组（以空串""结束）
char simple_menu(const char menu_items[][80], const char* valid_chars)
{
	for (int i = 0; menu_items[i][0] != '\0'; i++)
		cout << menu_items[i] << endl;
	char op = select_op(valid_chars);
	cout << op << endl;
	return op;
}


// 汉诺塔菜单提示词
const char* hanoi_menus[] = {
		"----------------------------------",
		"1.基本解",
		"2.基本解(步数记录)",
		"3.内部数组显示(横向)",
		"4.内部数组显示(纵向+横向)",
		"5.图形解-预备-画三个圆柱",
		"6.图形解-预备-在起始柱上画n个盘子",
		"7.图形解-预备-第一次移动",
		"8.图形解-自动移动版本",
		"9.图形解-游戏版",
		"0.退出",
		"----------------------------------",
		"[请选择:]",
		""};
// 数织菜单提示词
const char* puzzle_menus[] = {
		"---------------------------------------------------------",
		"A.内部数组，原样输出",
		"B.内部数组，生成提示行列并输出",
		"C.内部数组，游戏版",
		" --------------------------------------------------------",
		"D.n * n的框架(无分隔线)，原样输出",
		"E.n * n的框架(无分隔线)，含提示行列",
		"F.n * n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标",
		"G.cmd图形界面完整版(无分隔线)",
		" --------------------------------------------------------",
		"H.n * n的框架(有分隔线)，原样输出",
		"I.n * n的框架(有分隔线)，含提示行列",
		"J.n * n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标",
		"K.cmd图形界面完整版(有分隔线)",
		" --------------------------------------------------------",
		"Q.退出",
		"---------------------------------------------------------",
		"[请选择:]",
		""};

/***************************************************************************
  函数名称：display_menu
  功    能：显示菜单选项
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void display_menu(const char* menus[])
{
	for (int i = 0; menus[i] != ""; i++)
	{
		cout << menus[i];
		if(menus[i+1] != "")
			cout << endl;
	}
}
void init()
{
	cct_cls();
	cct_setfontsize("新宋体", 16, 8);
	cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
	cct_setconsoleborder(120, 40, 120, 9001);
}
/***************************************************************************
函数名称：hanoi_menu
功    能：显示Hanoi对应菜单选项
输入参数：
返 回 值：对应选项
说    明：
***************************************************************************/
int hanoi_menu()
{
	init();
	display_menu(hanoi_menus);
	char op;
	if(1)
		op = toupper(select_op("0123456789"));
	return op - '0';
}

int puzzle_menu()
{
	init();
	display_menu(puzzle_menus);
	char op = toupper(select_op("ABCDEFGHIJKQ"));
	if (op == 'Q') return 0;
	return op - 'A' + 1;
}