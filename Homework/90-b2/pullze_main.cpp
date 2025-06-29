// 2451317 冯久恒 计算机
#include<iostream>
#include<conio.h>
#include"pullze.h"
#include"cmd_console_tools.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

/* 提示：空文件，仅为了提醒你不要忘记首行 && 不要把文件名弄错 */

int main()
{
	cct_setconsoletitle("Puzzle_Game 数织游戏");
	while(1)
	{
		int a, b;
		a = menu();
		if (a == 17)
			break;
		b = size();
		if (a >= 1 && a <= 11)
			puzzle_base(b, a);
	}
	cct_cls();
	cct_gotoxy(0, 20);
	cout << "请按任意键继续...";
	char c = _getch();
	return 0;
}