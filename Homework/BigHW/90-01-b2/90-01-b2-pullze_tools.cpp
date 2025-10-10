// 2451317 冯久恒 计算机
#include<iostream>
#include<conio.h>
#include<cstring>
#include"../include/cmd_console_tools.h"
using namespace std;


/***************************************************************************
  函数名称：menu
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
/*
int menu()
{
	cct_cls();
	cct_setfontsize("新宋体", 16, 8);
	cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
	cct_setconsoleborder(120, 40, 120, 9001);
	cout << "---------------------------------------------------------" << endl;
	cout << "A.内部数组，原样输出" << endl;
	cout << "B.内部数组，生成提示行列并输出" << endl;
	cout << "C.内部数组，游戏版" << endl;
	cout << " --------------------------------------------------------" << endl;
	cout << "D.n * n的框架(无分隔线)，原样输出" << endl;
	cout << "E.n * n的框架(无分隔线)，含提示行列" << endl;
	cout << "F.n * n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标" << endl;
	cout << "G.cmd图形界面完整版(无分隔线)" << endl;
	cout << " --------------------------------------------------------" << endl;
	cout << "H.n * n的框架(有分隔线)，原样输出" << endl;
	cout << "I.n * n的框架(有分隔线)，含提示行列" << endl;
	cout << "J.n * n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标" << endl;
	cout << "K.cmd图形界面完整版(有分隔线)" << endl;
	cout << " --------------------------------------------------------" << endl;
	cout << "Q.退出" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "[请选择:]";
	char op;
	while (1)
	{
		op = _getch();
		if ((op >= 'A' && op <= 'K') || op == 'Q' || (op >= 'a' && op <= 'k') || op == 'q')
		{
			cout << op;
			break;
		}
	}
	op = toupper(op);
	return op - 'A' + 1;
}
*/
int size()
{
	cct_cls();
	int s;
	while (1)
	{
		cout << "请输入区域大小(5/10/15) ：";
		cin >> s;
		if (cin.good() != 1 || s <= 0 || s > 15 || s % 5 != 0)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		else
			break;
	}
	return s;
}

void end()
{
	int _x, _y;
	cout << "输入错误，请重新输入";
	cct_getxy(_x, _y);
	cct_gotoxy(_x + 8, _y - 1);
	cout << "    ";
	cct_gotoxy(_x + 8, _y - 1);
}


void wait(int op)
{
	cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
	if (op == 1)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	int x, y;
	cct_getxy(x, y);
	cct_showstr(x, y, "本小题结束，请输入End继续...");
	while (1)
	{
		char pt[5] = { 0 };
		if (fgets(pt, 4, stdin) == NULL)
		{
			cin.clear();
			continue;
		}
		if (pt[0] == '\n')
		{
			end();
			continue;
		}
		for (int i = 0; i < 4; i++)
			pt[i] = toupper(pt[i]);
		if (pt[1] == '\n' || pt[2] == '\n')
		{
			cin.clear();
			end();
			continue;
		}
		else if (pt[0] == 'E' && pt[1] == 'N' && pt[2] == 'D' && pt[3] == '\0')
			break;
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			end();
			continue;
		}
	}
}
/* 提示：空文件，仅为了提醒你不要忘记首行 && 不要把文件名弄错 */
