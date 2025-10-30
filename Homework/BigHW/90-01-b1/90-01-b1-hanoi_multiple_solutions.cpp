// 2451317 冯久恒 计算机
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_hdc_tools.h"
#include "90-01-b1-hanoi_const_value.h"

using namespace std;

/* ----------------------------------------------------------------------------------

     本文件功能：
    1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
    1、不允许定义外部全局变量（const及#define不在限制范围内）
    2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
    3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
    4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

int top[3] = { 0 }, plate[3][10] = { 0 }, cnt = 1;
int delay;

/***************************************************************************
  函数名称：input
  功    能：读入相关信息
  输入参数：n - 层数 ; src - 起始柱 ; dst - 目标柱
  返 回 值：
  说    明：
***************************************************************************/

void input(int* n, char* src, char* tmp, char* dst, int mode)
{
    // init
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
            plate[i][j] = 0;
        top[i] = -1;
    }
    cnt = 0;
    int m;
    char s, t, d;
    //src = 0, tmp = 0, dst = 0;
    // Inupt n
    while (1)
    {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> m;
        if (cin.good() != 1 || (m < 1 || m > 10))
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            break;
        }
    }
    // Input Source & Destination
    while (1)
    {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> s;
        s = toupper(s);
        if (cin.good() != 1 || (s < 'A' || s > 'C'))
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            break;
        }
    }
    while (1)
    {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> d;
        d = toupper(d);
        if (cin.good() != 1 || (d < 'A' || d > 'C'))
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else if (d == s)
        {
            cout << "目标柱(" << dst << ")不能与起始柱(" << src << ")相同" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            break;
        }
    }
    // Input delay
    if (mode == 4)
    {
        while (1)
        {
            cout << "请输入移动速度(0-200：0-按回车单步演示 1-200:延时1-200ms)";
            cin >> delay;
            if (cin.good() != 1 || (delay < 0 || delay > 200))
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
    else if (mode == 7 || mode == 8 || mode == 9)
    {
        while (1)
        {
            cout << "请输入移动速度(0-20：0-按回车单步演示 1-20:延时1-20ms)";
            cin >> delay;
            if (cin.good() != 1 || (delay < 0 || delay > 20))
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
        }
    }
    for (char i = 'A'; i <= 'C'; i++)
    {
        if (i == s || i == d)
            continue;
        t = i;
    }
    for (int i = 0; i < m; i++)
        plate[s - 'A'][i] = m - i;
    for (int i = 0; i < 3; i++)
        top[i] = -1;
    top[s - 'A'] = (m - 1);
    cnt = 1;
    *n = m;
    *src = s, * tmp = t, * dst = d;
}

/***************************************************************************
  函数名称：wait
  功    能：按回车键继续
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait(int op)
{
    if (op >= 4)
        cct_gotoxy(Status_Line_X, Status_Line_Y + 1);
    // cout << endl;
	cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
    cout << "按回车键继续";
    while (_getch() != 13)
        ;
}

void output_text(int n, char src, char dst, int mode)
{
    if (mode == 4)
    {
        cct_cls();
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << src << " 移动到 " << dst << "，共 " << top[src - 'A'] + 1 << " 层，延时设置为 " << delay << "ms";
    }
    else if (mode == 6 || mode == 7)
    {
        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 2);
        cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
    }
    else if (mode == 8)
    {
        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 2);
        cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << delay << "（前7步，后面自动变为0ms）";
    }
    else if (mode == 9)
    {
        cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 5);
        cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
    }
}

/***************************************************************************
  函数名称：output1
  功    能：基本输出
  输入参数：n - 层数 ; src - 起始柱 ; dst - 目标柱
  返 回 值：
  说    明：
***************************************************************************/
void output1(int n, char src, char dst)
{
    cout << setw(2) << n << "# " << src << "---->" << dst;
    top[dst - 'A']++;
    plate[src - 'A'][top[src - 'A']] = 0;
    plate[dst - 'A'][top[dst - 'A']] = n;
    top[src - 'A']--;
    cout << endl;
}

/***************************************************************************
  函数名称：output2
  功    能：横向输出移动步数
  输入参数：n - 层数 ; src - 起始柱 ; dst - 目标柱
  返 回 值：
  说    明：
***************************************************************************/
void output2(int n, char src, char dst, bool show)
{

    cout << "第" << setw(4) << cnt << " 步" << "(" << setw(2) << n << "#: ";
    cout << src << "-->" << dst << ")";
    top[dst - 'A']++;
    plate[src - 'A'][top[src - 'A']] = 0;
    plate[dst - 'A'][top[dst - 'A']] = n;
    top[src - 'A']--;
    if (show)
    {
        for (int i = 0; i < 3; i++)
        {
            cout << " " << char(i + 'A') << ":";
            for (int j = 0; j < 10; j++)
            {
                if (plate[i][j] != 0 && top[i] != -1)
                    cout << setw(2) << plate[i][j];
                else
                    cout << "  ";
            }
        }
    }
    cnt++;
    cout << endl;
}

/***************************************************************************
  函数名称：output3
  功    能：纵向输出移动步数
  输入参数：n - 层数 ; src - 起始柱 ; dst - 目标柱
  返 回 值：
  说    明：
***************************************************************************/
void output3_base(int n, char src, char dst, int op)
{
    cct_setcursor(CCT_CURSOR_INVISIBLE);
    int Menu_start_X = 0, Menu_start_Y = 0;
    if (op == 4)
        Menu_start_X = MenuItem4_Start_X, Menu_start_Y = MenuItem4_Start_Y;
    else if (op == 7 || op == 8)
        Menu_start_X = MenuItem8_Start_X, Menu_start_Y = MenuItem8_Start_Y;
    cct_gotoxy(Menu_start_X, Menu_start_Y);
    cout << "第" << setw(4) << cnt << "步(" << setw(2) << n << ") : " << src << "-->" << dst;
    top[dst - 'A']++;
    plate[src - 'A'][top[src - 'A']] = 0;
    plate[dst - 'A'][top[dst - 'A']] = n;
    top[src - 'A']--;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << char(i + 'A') << ":";
        for (int j = 0; j < 10; j++)
        {
            if (plate[i][j] != 0 && top[i] != -1)
                cout << setw(2) << plate[i][j];
            else
                cout << "  ";
        }
    }
    cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET - 2, Menu_start_Y + Underpan_A_Y_OFFSET - 1);
    for (int i = 1; i <= 2 * Underpan_Distance + 5; i++)
        cout << "=";
    cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET, Menu_start_Y + Underpan_A_Y_OFFSET);
    cout << 'A';
    for (char ch = 'B'; ch <= 'C'; ch++)
        cout << setw(Underpan_Distance) << ch;
    for (int i = 0; i < 3; i++)
    {
        cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET + i * (Underpan_Distance)-1, Menu_start_Y + Underpan_A_Y_OFFSET - 2);
        for (int j = 0; j < 10; j++)
        {
            cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET + i * (Underpan_Distance)-1, Menu_start_Y + Underpan_A_Y_OFFSET - 2 - j);
            if (plate[i][j] != 0 && top[i] != -1)
                cout << setw(2) << plate[i][j];
            else
                cout << "  ";
        }
    }
    cnt++;
}

void output3_init(int n, char src, char dst, int op)
{
    int Menu_start_X = 0, Menu_start_Y = 0;
    if (op == 4)
        Menu_start_X = MenuItem4_Start_X, Menu_start_Y = MenuItem4_Start_Y;
    else if (op == 7 || op == 8)
        Menu_start_X = MenuItem8_Start_X, Menu_start_Y = MenuItem8_Start_Y;
    else if (op == 9)
        Menu_start_X = MenuItem9_Start_X, Menu_start_Y = MenuItem9_Start_Y;
    if (op > 4)
        output_text(n, src, dst, op);
    if (op > 6 || op == 4)
    {
        cct_gotoxy(Menu_start_X, Menu_start_Y);
        cout << "初始:               ";
        for (int i = 0; i < 3; i++)
        {
            cout << " " << char(i + 'A') << ":";
            for (int j = 0; j < 10; j++)
            {
                if (plate[i][j] != 0 && top[i] != -1)
                    cout << setw(2) << plate[i][j];
                else
                    cout << "  ";
            }
        }
        cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET - 2, Menu_start_Y + Underpan_A_Y_OFFSET - 1);
        for (int i = 1; i <= 2 * Underpan_Distance + 5; i++)
            cout << "=";
        cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET, Menu_start_Y + Underpan_A_Y_OFFSET);
        cout << 'A';
        for (char ch = 'B'; ch <= 'C'; ch++)
            cout << setw(Underpan_Distance) << ch;
        for (int i = 0; i < 3; i++)
        {
            cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET + i * (Underpan_Distance)-1, Menu_start_Y + Underpan_A_Y_OFFSET - 2);
            for (int j = 0; j < 10; j++)
            {
                cct_gotoxy(Menu_start_X + Underpan_A_X_OFFSET + i * (Underpan_Distance)-1, Menu_start_Y + Underpan_A_Y_OFFSET - 2 - j);
                if (plate[i][j] != 0 && top[i] != -1)
                    cout << setw(2) << plate[i][j];
                else
                    cout << "  ";
            }
        }
    }
}

void output3(int n, char src, char dst)
{
    if (cnt == 1)
    {
        output3_init(n, src, dst, 4);
        if (delay != 0)
            Sleep(delay);
        else
            while (_getch() != '\r')
                ;
    }
    output3_base(n, src, dst, 4);
    if (delay != 0)
        Sleep(delay);
    else
        while (_getch() != '\r')
            ;
    cct_gotoxy(0, MenuItem4_Start_Y + 10);
}

/***************************************************************************
  函数名称：print_towerbase
  功    能：打印塔底与塔柱
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void print_towerbase(int n, char src, char dst, int op)
{
    const int   win_width = 1400, win_high = 900;	//设定屏幕宽度
    const int   win_bgcolor = 0, win_fgcolor = 14;
    const int   color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B
    hdc_init(win_bgcolor, win_fgcolor, win_width, win_high);		//用(背景色，前景色，宽度，高度）初始化窗口
    hdc_cls();
    cct_cls();
    cct_setcursor(CCT_CURSOR_INVISIBLE);
    if (op >= 6 && op <= 9)
        output3_init(n, src, dst, op);
    else
        cct_gotoxy(0, 30);
    Sleep(30);
    for (int i = 0; i < 3; i++)
    {
        int Unst_x = HDC_Start_X + i * HDC_Underpan_Distance + 23 * i * HDC_Base_Width;
        int Unst_y = HDC_Start_Y;
        int Unst_w = 23 * HDC_Base_Width, Unst_h = HDC_Base_High;
        hdc_rectangle(Unst_x, Unst_y, Unst_w, Unst_h, 0, true, 1, HDC_COLOR[11]);
        Sleep(HDC_Init_Delay);
    }
    for (int i = 0; i < 3; i++)
    {
        int Upst_x = HDC_Start_X + 11 * HDC_Base_Width + i * HDC_Underpan_Distance + 23 * i * HDC_Base_Width;
        int Upst_y = HDC_Start_Y - 12 * HDC_Base_High;
        int Upst_w = HDC_Base_Width, Upst_h = 12 * HDC_Base_High;
        hdc_rectangle(Upst_x, Upst_y, Upst_w, Upst_h, 0, true, 1, HDC_COLOR[11]);
        Sleep(HDC_Init_Delay);
    }
}
/***************************************************************************
  函数名称：print_plates
  功    能：打印初始盘子
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void print_plates(int n, char src, char dst, int op)
{
    print_towerbase(n, src, dst, op);
    for (int i = n; i >= 1; i--)
    {
        int pl_w = (2 * i + 1) * HDC_Base_Width, pl_h = HDC_Base_High;
        int pl_x = HDC_Start_X + (src - 'A') * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (11 - i) * HDC_Base_Width;
        int pl_y = HDC_Start_Y - (n + 1 - i) * HDC_Base_High;
        hdc_rectangle(pl_x, pl_y, pl_w, pl_h, 0, true, 1, HDC_COLOR[i]);
        Sleep(HDC_Init_Delay);
    }
}
void output6(int n, char src, char dst, int md)
{
    if (md == 0 && cnt == 2)
        return;
    output3_base(n, src, dst, 8);
    if (delay == 0)
    {
        if (md == 1)
            if (cnt <= 8)
                while (_getch() != '\r')
                    ;
        if (md == 0)
            while (_getch() != '\r')
                ;
    }
    else
    {
        if (cnt <= 8)
            Sleep(delay);
    }
    int Stx = HDC_Start_X + (src - 'A') * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (11 - n) * HDC_Base_Width;
    int Dsx = HDC_Start_X + (dst - 'A') * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (11 - n) * HDC_Base_Width;
    int Sty = HDC_Start_Y - (top[src - 'A'] + 2) * HDC_Base_High;
    int Dsy = HDC_Start_Y - (top[dst - 'A'] + 1) * HDC_Base_High;
    int Stw = (2 * n + 1) * HDC_Base_Width, Sth = HDC_Base_High;
    int Sttx = HDC_Start_X + 11 * HDC_Base_Width + (src - 'A') * HDC_Underpan_Distance + 23 * (src - 'A') * HDC_Base_Width;
    int Dstx = HDC_Start_X + 11 * HDC_Base_Width + (dst - 'A') * HDC_Underpan_Distance + 23 * (dst - 'A') * HDC_Base_Width;
    int Stty = Sty - HDC_Base_High;
    int Sttw = HDC_Base_Width, Stth = HDC_Base_High;
    // 上移
    for (int CurY = Sty - HDC_Step_Y; CurY >= HDC_Top_Y; CurY -= HDC_Step_Y)
    {
        hdc_rectangle(Stx, CurY + HDC_Base_High, Stw, HDC_Step_Y, 0, true, 1, HDC_COLOR[0]);
        if ((CurY + HDC_Base_High) >= (HDC_Start_Y - 12 * HDC_Base_High))
            hdc_rectangle(Sttx, CurY + HDC_Base_High, Sttw, HDC_Step_Y, 0, true, 1, HDC_COLOR[11]);
        else
            hdc_rectangle(Stx, CurY + HDC_Base_High, Stw, HDC_Step_Y, 0, true, 1, HDC_COLOR[0]);
        hdc_rectangle(Stx, CurY, Stw, Sth, 0, true, 1, HDC_COLOR[n]);
        if (delay == 0)
        {
            if (md == 1)
                if (cnt <= 8)
                    while (_getch() != '\r')
                        ;
            if (md == 0)
                while (_getch() != '\r')
                    ;
            if (md == 2)
                Sleep(5);
        }
        else
        {
            if (md == 1 || md == 2)
                if (cnt <= 8)
                    Sleep(delay);
            if (md == 0)
                Sleep(delay);
        }
    }
    // 平移
    if (dst > src)
    {
        for (int CurX = Stx - HDC_Step_X; CurX <= Stx + (dst - src) * (HDC_Underpan_Distance + 23 * HDC_Base_Width); CurX += HDC_Step_X)
        {
            hdc_rectangle(CurX - HDC_Step_X, HDC_Top_Y, HDC_Step_X, Sth, 0, true, 1, HDC_COLOR[0]);
            hdc_rectangle(CurX, HDC_Top_Y, Stw, Sth, 0, true, 1, HDC_COLOR[n]);
            if (delay == 0)
            {
                if (md == 1)
                    if (cnt <= 8)
                        while (_getch() != '\r')
                            ;
                if (md == 0)
                    while (_getch() != '\r')
                        ;
                if (md == 2)
                    Sleep(5);
            }
            else
            {
                if (md == 1 || md == 2)
                    if (cnt <= 8)
                        Sleep(delay);
                if (md == 0)
                    Sleep(delay);
            }
        }
    }
    else
    {
        for (int CurX = Stx - HDC_Step_X; CurX >= Stx - (src - dst) * (HDC_Underpan_Distance + 23 * HDC_Base_Width); CurX -= HDC_Step_X)
        {
            hdc_rectangle(CurX + Stw, HDC_Top_Y, HDC_Step_X, Sth, 0, true, 1, HDC_COLOR[0]);
            hdc_rectangle(CurX, HDC_Top_Y, Stw, Sth, 0, true, 1, HDC_COLOR[n]);
            if (delay == 0)
            {
                if (md == 1)
                    if (cnt <= 8)
                        while (_getch() != '\r')
                            ;
                if (md == 0)
                    while (_getch() != '\r')
                        ;
                if (md == 2)
                    Sleep(5);
            }
            else
            {
                if (md == 1 || md == 2)
                    if (cnt <= 8)
                        Sleep(delay);
                if (md == 0)
                    Sleep(delay);
            }
        }
    }
    // 下移
    for (int CurY = HDC_Top_Y; CurY <= Dsy; CurY += HDC_Step_Y)
    {
        hdc_rectangle(Dsx, CurY - HDC_Step_Y, Stw, HDC_Step_Y, 0, true, 1, HDC_COLOR[0]);
        if ((CurY + HDC_Base_High) >= (HDC_Start_Y - 11 * HDC_Base_High))
            hdc_rectangle(Dstx, CurY - HDC_Step_Y, Sttw, HDC_Step_Y, 0, true, 1, HDC_COLOR[11]);
        else
            hdc_rectangle(Dsx, CurY - HDC_Step_Y, Stw, HDC_Step_Y, 0, true, 1, HDC_COLOR[0]);
        hdc_rectangle(Dsx, CurY, Stw, Sth, 0, true, 1, HDC_COLOR[n]);
        if (delay == 0)
        {
            if (md == 1)
                if (cnt <= 8)
                    while (_getch() != '\r')
                        ;
            if (md == 0)
                while (_getch() != '\r')
                    ;
            if (md == 2)
                Sleep(5);
        }
        else
        {
            if (md == 1 || md == 2)
                if (cnt <= 8)
                    Sleep(delay);
            if (md == 0)
                Sleep(delay);
        }
    }
}

/***************************************************************************
  函数名称：output
  功    能：选择输出模式
  输入参数：n - 层数 ; src - 起始柱 ; dst - 目标柱 ; mode - 显示模式
  返 回 值：
  说    明：
***************************************************************************/
void output(int n, char src, char dst, int mode)
{
    if (mode == 1)
        output1(n, src, dst);
    else if (mode == 2)
        output2(n, src, dst, false);
    else if (mode == 3)
        output2(n, src, dst, true);
    else if (mode == 4)
        output3(n, src, dst);
    else if (mode == 7)
        output6(n, src, dst, 0);
    else if (mode == 8)
        output6(n, src, dst, 1);
}

/***************************************************************************
  函数名称：hanoi
  功    能：递归求解汉诺塔问题
  输入参数：n - 层数 ; src - 起始柱 ; dst - 目标柱 ;  mode - 显示模式
  返 回 值：
  说    明：
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, int mode)
{
    if (n == 1)
    {
        output(n, src, dst, mode);
        return;
    }
    hanoi(n - 1, src, dst, tmp, mode);
    output(n, src, dst, mode);
    hanoi(n - 1, tmp, src, dst, mode);
}

void game_input_clear(int md)
{
    cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 1);
    if (md == 0)
        cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：          ";
    else
        cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";

}

void hanoi_game(int n, char s, char t, char d)
{
	cct_setcursor(CCT_CURSOR_VISIBLE_NORMAL);
    char ipt[10];
    for (int i = 0; i < 10; i++)
        ipt[i] = '\0';
    char src, tmp, dst;
    while (1)
    {
        if (cnt == 1 && delay == 0)
            while (_getch() != '\r')
                ;
        game_input_clear(1);
        cin >> ipt;
        if (ipt[2] != '\0')
        {
            game_input_clear(0);
            continue;
        }
        if (ipt[1] == '\0' && (ipt[0] == 'Q' || ipt[0] == 'q'))
        {
            cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 2);
            cout << "游戏终止!!!!!";
            return;
        }
        src = ipt[0], dst = ipt[1];
        if (src >= 'a' && src <= 'z')
            src = toupper(src);
        if (dst >= 'a' && dst <= 'z')
            dst = toupper(dst);
        for (int i = 'A'; i <= 'C'; i++)
        {
            if (i == src || i == dst)
            {
                game_input_clear(0);
                continue;
            }
            tmp = i;
        }
        if ((src < 'A' || src> 'C') || (dst < 'A' || dst > 'C') || src == dst)
        {
            game_input_clear(0);
            continue;
        }
        else
        {
            if (top[src - 'A'] < 0)
            {
                cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 2);
                cout << "源柱为空!";
                Sleep(500);
                cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 2);
                cout << "                             ";
                continue;
            }
            else if (top[dst - 'A'] != -1 && plate[src - 'A'][top[src - 'A']] > plate[dst - 'A'][top[dst - 'A']])
            {
                cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 2);
                cout << "大盘压小盘，非法移动!";
                Sleep(500);
                cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 2);
                cout << "                             ";
                continue;
            }
            else
                output6(plate[src - 'A'][top[src - 'A']], src, dst, 2);
            if (top[s - 'A'] == -1 && top[t - 'A'] == -1 && top[d - 'A'] == n - 1)
            {
                cct_gotoxy(MenuItem9_Start_X, MenuItem9_Start_Y + 2);
                cout << "游戏结束!!!!!";
                return;
            }
        }
        game_input_clear(0);
    }
}