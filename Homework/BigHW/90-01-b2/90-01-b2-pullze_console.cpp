// 2451317 冯久恒 计算机
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include"90-01-b2-pullze.h"
#include"../include/cmd_console_tools.h"

using namespace std;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void init(int t, int w, int h, int op)
{
    cct_setfontsize("新宋体", t * 2, t);
    cct_setconsoleborder(w, h, w, h);
    cct_cls();
    if (op == 4 || op == 8)
        cout << endl << "    ";
    else if (op == 5 || op == 9)
        cout << endl;
    else if (op == 6 || op == 10)
        cout << "测试键盘/鼠标左键/右键，回车退出" << endl;
    else if (op == 7 || op == 11)
        cout << "左键选〇/右键选×，Y/y提交，Z/z作弊，Q/q结束" << endl;
}

void show_border_1(const char* left, const char* middle, const char* right, int stt_x, int stt_y, int len, int fc, int bc)
{
    cct_showstr(stt_x, stt_y, left, fc, bc, 1, -1);
    cct_showstr(stt_x + 2, stt_y, middle, fc, bc, len, -1);
    cct_showstr(stt_x + (len + 1) * 2, stt_y, right, fc, bc, 1, -1);
}

int read_enter(int x, int y, int op)
{
    int cols, lines, b_cols, b_lines;
    cct_getconsoleborder(cols, lines, b_cols, b_lines);
    cct_showstr(x, y, "[读到回车键]                      ");
    if (op == 6 || op == 10)
    {
        cct_showstr(0, y + 1, "窗口：");
        cout << cols << "行，" << lines << "列" << endl;
        return 1;
    }
    return 2;
}

void read_arrow(int kc1, int kc2, int x, int y)
{
    switch (kc2)
    {
    case KB_ARROW_UP:
        cct_showstr(x, y, "[读到上箭头]           ");
        break;
    case KB_ARROW_DOWN:
        cct_showstr(x, y, "[读到下箭头]           ");
        break;
    case KB_ARROW_LEFT:
        cct_showstr(x, y, "[读到左箭头]           ");
        break;
    case KB_ARROW_RIGHT:
        cct_showstr(x, y, "[读到右箭头]           ");
        break;
    default:
    {
        cct_showstr(x, y, "[读到键码]");
        cout << kc1 << "/" << kc2 << "                        ";
    }
    }
}

void draw_1(int s, char bl[16][16])
{
    int t = 120 / s;
    int w = (s + 2) * 5, h = (s + 1) * 2;
    init(t, w, h, 4);
    for (int i = 0; i <= s + 2; i++)
    {
        cct_setcursor(CCT_CURSOR_INVISIBLE);
        if (i == 0)
        {
            for (int j = 0; j < s; j++)
                cout << (char)(j + 'a') << " ";
            cout << endl;
        }
        if (i == 1)
        {
            int x, y;
            cct_getxy(x, y);
            cct_showstr(x, y, "  ");
            show_border_1("╔", "═", "╗", x + 2, y, s, COLOR_HWHITE, COLOR_BLACK);
            Sleep(50);
            cout << endl;
        }
        if (i >= 2 && i <= s + 1)
        {
            int x, y;
            cct_getxy(x, y);
            cct_showch(x, y, (char)(i + 'A' - 2));
            cct_showch(x + 1, y, ' ');
            show_border_1("║", "  ", "║", x + 2, y, s, COLOR_HWHITE, COLOR_BLACK);
            Sleep(50);
            cout << endl;
        }
        if (i == s + 2)
        {
            int x, y;
            cct_getxy(x, y);
            cct_showstr(x, y, "  ");
            show_border_1("╚", "═", "╝", x + 2, y, s, COLOR_HWHITE, COLOR_BLACK);
            Sleep(50);
            cout << endl;
        }
    }
    cct_gotoxy(5, 4);
    for (int i = 1; i <= s; i++)
    {
        for (int j = 1; j <= s; j++)
        {
            if (bl[i][j] == '0')
            {
                cct_showstr(4 + (j - 1) * 2, 3 + (i - 1), "〇", COLOR_HBLUE, COLOR_BLACK, 1);
                Sleep(50);
            }
        }
    }
    cct_gotoxy(0, s + 5);
    wait(1);
}

void draw_11(int s, char bl[16][16], int op)
{
    int _1[16][16] = { 0 }, _2[16][16] = { 0 };
    int cur_1[16] = { 0 }, cur_2[16] = { 0 };
    for (int i = 1; i <= s; i++)
    {
        cur_1[i] = 0, cur_2[i] = 0;
        bool f1 = false, f2 = false;
        for (int j = 1; j <= s; j++)
        {
            if (bl[i][j] == '0')
            {
                if (f1 == false)
                    cur_1[i]++;
                f1 = true;
                _1[i][cur_1[i]]++;
            }
            else
                f1 = false;
            if (bl[j][i] == '0')
            {
                if (f2 == false)
                    cur_2[i]++;
                f2 = true;
                _2[i][cur_2[i]]++;
            }
            else
                f2 = false;
        }
    }
    int __1 = -1, __2 = -1;
    for (int t = 1; t <= s; t++)
    {
        __1 = max(__1, cur_1[t]);
        __2 = max(__2, cur_2[t]);
    }
    int t = 210 / (s + 15);
    int w = s * t, h = s * t / 2;
    char ip[16][16] = { 0 }, df[16][16] = { 0 };
    init(t, w, h, op);
    int x, y;
    cct_getxy(x, y);
    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
    show_border_1("╔", "═", "╗", x + 6 + __1 * 2, y, s, COLOR_HWHITE, COLOR_BLACK);
    cout << endl;
    for (int i = 0; i < __2; i++)
    {
        cct_getxy(x, y);
        cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
        cct_showstr(x + 6 + __1 * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
        for (int j = 0; j < s; j++)
        {
            int t = i - (__2 - cur_2[j + 1]) + 1;
            if (_2[j + 1][t] != 0 && t > 0)
                cout << setw(2) << _2[j + 1][t];
            else
                cout << "  ";

        }
        cct_showstr(x + 8 + __1 * 2 + s * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
        cout << endl;
    }
    cct_getxy(x, y);
    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
    show_border_1("╠", "═", "╣", x + 6 + __1 * 2, y, s, COLOR_HWHITE, COLOR_BLACK);
    cout << endl;
    cct_getxy(x, y);
    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
    cct_showstr(x + 6 + __1 * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
    for (int i = 0; i < s; i++)
        cout << " " << (char)(i + 'a');
    cct_showstr(x + 8 + __1 * 2 + s * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
    cout << endl;
    for (int i = 0; i <= s + 1; i++)
    {
        if (i == 0)
        {
            cct_getxy(x, y);
            show_border_1("╔", "═", "╦", x, y, __1, COLOR_HWHITE, COLOR_BLACK);
            cct_showstr(x + 4 + __1 * 2, y, "═", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            show_border_1("╬", "═", "╣", x + 6 + __1 * 2, y, s, COLOR_HWHITE, COLOR_BLACK);
            cout << endl;
        }
        if (i < s)
        {
            cct_getxy(x, y);
            cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            for (int j = 0; j < __1; j++)
            {
                int t = j + 1 - (__1 - cur_1[i + 1]);
                if (_1[i + 1][t] != 0)
                    cout << left << setw(2) << _1[i + 1][t];
                else
                    cout << "  ";
            }
            cct_showstr(x + 2 + __1 * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            cout << " " << (char)(i + 'A');
            show_border_1("║", "  ", "║", x + 6 + __1 * 2, y, s, COLOR_HWHITE, COLOR_BLACK);
            cout << endl;
        }

        if (i == s + 1)
        {
            cct_getxy(x, y);
            show_border_1("╚", "═", "╩", x, y, __1, COLOR_HWHITE, COLOR_BLACK);
            cct_showstr(x + 4 + __1 * 2, y, "═", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            show_border_1("╩", "═", "╝", x + 6 + __1 * 2, y, s, COLOR_HWHITE, COLOR_BLACK);
            cout << endl;
        }
    }
    cct_gotoxy(5 + __1, 6 + __2);
    for (int i = 1; i <= s; i++)
    {
        for (int j = 1; j <= s; j++)
        {
            if (bl[i][j] == '0' && op != 7)
                cct_showstr(8 + __1 * 2 + (j - 1) * 2, 5 + (i - 1) + __2, "〇", COLOR_HBLUE, COLOR_BLACK, 1);
        }
    }
    if (op == 5)
    {
        cct_gotoxy(0, s + 7 + __2);
        wait(1);
    }
    else if (op == 6 || op == 7)
    {
        cct_setcursor(CCT_CURSOR_INVISIBLE);
        cct_enable_mouse();
        cct_gotoxy(8 + __1 * 2, 5 + __2);
        cct_gotoxy(0, s + 7 + __2);
        int mx = 0, my = 0, ma = 0, kc1 = 0, kc2 = 0;
        int ev = 0;
        bool zb = false;
        while (1)
        {
            cct_enable_mouse();
            ev = cct_read_keyboard_and_mouse(mx, my, ma, kc1, kc2);
            if (ev == CCT_KEYBOARD_EVENT)
            {
                if (kc1 == 13)
                {
                    if (read_enter(8 + __1 * 2, 6 + __2 + s, op) == 1)
                        break;
                    else
                        continue;
                }
                if (kc1 == 0xe0)
                    read_arrow(kc1, kc2, 8 + __1 * 2, 6 + __2 + s);
                else if (kc1 > 0)
                {
                    if (op == 7 && (kc1 == 'Q' || kc1 == 'q'))
                    {
                        cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到Q/q，游戏结束]                                 ");
                        cout << endl;
                        break;
                    }
                    else if (op == 7 && (kc1 == 'Z' || kc1 == 'z'))
                    {
                        if (zb == false)
                        {
                            zb = true;
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "[作弊模式开]                              ");
                            for (int i = 1; i <= s; i++)
                            {
                                for (int j = 1; j <= s; j++)
                                {
                                    if (bl[i][j] == '0')
                                    {
                                        if (ip[i][j] != '0')
                                            cct_showstr(6 + __1 * 2 + j * 2, 4 + i + __2, "〇", COLOR_HBLACK, COLOR_BLACK, 1);
                                        if (df[i][j] == '0')
                                            cct_showstr(6 + __1 * 2 + j * 2, 4 + i + __2, "×", COLOR_HBLUE, COLOR_BLACK, 1);
                                    }
                                    else
                                    {
                                        if (ip[i][j] == '0')
                                            cct_showstr(6 + __1 * 2 + j * 2, 4 + i + __2, "〇", COLOR_HRED, COLOR_BLACK, 1);
                                    }
                                }
                            }
                        }
                        else
                        {
                            zb = false;
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "[作弊模式关]                              ");
                            for (int i = 1; i <= s; i++)
                            {
                                for (int j = 1; j <= s; j++)
                                {
                                    cct_showstr(6 + __1 * 2 + j * 2, 4 + i + __2, "  ", COLOR_HWHITE, COLOR_BLACK, 1);
                                    if (ip[i][j] == '0')
                                        cct_showstr(6 + __1 * 2 + j * 2, 4 + i + __2, "〇", COLOR_HBLUE, COLOR_BLACK, 1);
                                    if (df[i][j] == '0')
                                        cct_showstr(6 + __1 * 2 + j * 2, 4 + i + __2, "×", COLOR_HRED, COLOR_BLACK, 1);
                                }
                            }
                        }
                        continue;
                    }
                    else if (op == 7 && (kc1 == 'Y' || kc1 == 'y'))
                    {
                        cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到提交键]                                  ");
                        Sleep(100);
                        if (!game_check(s, bl, ip))
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "提交失败，请在作弊模式中查看");
                        else
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "[提交成功]                                      ");
                            cout << endl;
                            wait(1);
                            return;
                        }
                        continue;
                    }
                    else
                    {
                        cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到键码]");
                        cout << kc1 << "/" << kc2 << "                     ";
                    }
                }
                else
                    cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到键码]0/0                     ");
            }
            else if (ev == CCT_MOUSE_EVENT)
            {
                int Valid_x1, Valid_x2, Valid_y1, Valid_y2;
                Valid_x1 = 8 + __1 * 2, Valid_y1 = 5 + __2;
                Valid_x2 = Valid_x1 + s * 2 - 1, Valid_y2 = Valid_y1 + s - 1;
                if ((mx >= Valid_x1 && mx <= Valid_x2) && (my >= Valid_y1 && my <= Valid_y2))
                {
                    cct_showstr(8 + __1 * 2, 6 + __2 + s, "[当前光标] ");
                    int Cur_x, Cur_y;
                    Cur_x = (mx - Valid_x1) / 2, Cur_y = (my - Valid_y1);
                    cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列                        ";
                    if (op == 6)
                    {
                        if (ma == MOUSE_LEFT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到左键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列               " << endl;
                            int cols, lines, b_cols, b_lines;
                            cct_getconsoleborder(cols, lines, b_cols, b_lines);
                            cct_showstr(0, 7 + __2 + s, "窗口：");
                            cout << cols << "行，" << lines << "列" << endl;
                            break;
                        }
                        else if (ma == MOUSE_RIGHT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到右键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列               " << endl;
                            int cols, lines, b_cols, b_lines;
                            cct_getconsoleborder(cols, lines, b_cols, b_lines);
                            cct_showstr(0, 7 + __2 + s, "窗口：");
                            cout << cols << "行，" << lines << "列" << endl;
                            break;
                        }
                    }
                    else if (op == 7)
                    {
                        if (ma == MOUSE_LEFT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到左键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列                         " << endl;
                            if (zb == false)
                            {
                                if (ip[Cur_y + 1][Cur_x + 1] != '0')
                                {
                                    ip[Cur_y + 1][Cur_x + 1] = '0';
                                    cct_showstr(10 + __1 * 2 + (Cur_x - 1) * 2, 6 + (Cur_y - 1) + __2, "〇", COLOR_HBLUE, COLOR_BLACK, 1);
                                }
                                else
                                {
                                    ip[Cur_y + 1][Cur_x + 1] = 0;
                                    cct_showstr(10 + __1 * 2 + (Cur_x - 1) * 2, 6 + (Cur_y - 1) + __2, "  ", COLOR_HWHITE, COLOR_BLACK, 1);
                                }
                            }
                            else
                            {
                                if (bl[Cur_y + 1][Cur_x + 1] == '0')
                                {
                                    if (ip[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = '0';
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "〇", COLOR_HBLUE, COLOR_BLACK, 1);
                                    }
                                    else
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "〇", COLOR_HBLACK, COLOR_BLACK, 1);
                                    }
                                }
                                else
                                {
                                    if (ip[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = '0';
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "〇", COLOR_HRED, COLOR_BLACK, 1);
                                    }
                                    else
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "  ", COLOR_HWHITE, COLOR_BLACK, 1);
                                    }
                                }
                            }
                        }
                        else if (ma == MOUSE_RIGHT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s, "[读到右键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列                        " << endl;
                            if (zb == false)
                            {
                                if (df[Cur_y + 1][Cur_x + 1] != '0')
                                {
                                    df[Cur_y + 1][Cur_x + 1] = '0';
                                    ip[Cur_y + 1][Cur_x + 1] = 0;
                                    cct_showstr(10 + __1 * 2 + (Cur_x - 1) * 2, 6 + (Cur_y - 1) + __2, "×", COLOR_HRED, COLOR_BLACK, 1);
                                }
                                else
                                {
                                    df[Cur_y + 1][Cur_x + 1] = 0;
                                    cct_showstr(10 + __1 * 2 + (Cur_x - 1) * 2, 6 + (Cur_y - 1) + __2, "  ", COLOR_HWHITE, COLOR_BLACK, 1);
                                }
                            }
                            else
                            {
                                if (bl[Cur_y + 1][Cur_x + 1] == '0')
                                {
                                    if (df[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = '0';
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "×", COLOR_HBLUE, COLOR_BLACK, 1);
                                    }
                                    else
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = 0;
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "〇", COLOR_HBLACK, COLOR_BLACK, 1);
                                    }
                                }
                                else
                                {
                                    if (df[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = '0';
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "×", COLOR_HRED, COLOR_BLACK, 1);
                                    }
                                    else
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = 0;
                                        cct_showstr(8 + __1 * 2 + Cur_x * 2, 5 + Cur_y + __2, "  ", COLOR_HWHITE, COLOR_BLACK, 1);
                                    }
                                }
                            }
                        }
                    }
                }
                else
                    cct_showstr(8 + __1 * 2, 6 + __2 + s, "[当前光标] 位置非法                        ");
            }
        }
        wait(1);
    }
}

void draw_rec(const char* in, const int fc, const int bc, int x, int y, int op)
{
    if (op == 1)
    {
        show_border_1("╔", "═", "╗", x, y, 1, fc, bc);
        show_border_1("║", in, "║", x, y + 1, 1, fc, bc);
        show_border_1("╚", "═", "╝", x, y + 2, 1, fc, bc);
    }
    else
        for (int t = y; t <= y + 2; t++)
            cct_showstr(x, t, "      ", fc, bc, 1, -1);

}
// 在某坐标处向右下绘制圈或叉
void draw_ball(const int x, const int y, const int op)
{
    if (op == 1)
        draw_rec("〇", COLOR_HBLUE, COLOR_BLACK, x, y, 1);
    else if (op == 2)
        draw_rec("×", COLOR_HRED, COLOR_BLACK, x, y, 1);
    else if (op == 3)
        draw_rec("  ", COLOR_HWHITE, COLOR_BLACK, x, y, 0);
    else if (op == 7)
        draw_rec("〇", COLOR_HRED, COLOR_BLACK, x, y, 1);
    else if (op == 8)
        draw_rec("×", COLOR_HBLUE, COLOR_BLACK, x, y, 1);
    else if (op == 9)
        draw_rec("〇", COLOR_HBLACK, COLOR_BLACK, x, y, 1);
}

void show_border_2(const char* left, const char* middle_1, const char* middle_2, const char* right, int stt_x, int stt_y, int len, int fc, int bc)
{
    cct_showstr(stt_x, stt_y, left, fc, bc, 1, -1);
    for (int j = 1; j < len; j++)
    {
        if (j % 8 == 0 && j > 7)
            cct_showstr(stt_x + j, stt_y, middle_1, fc, bc, 1, -1);
        else
            cct_showstr(stt_x + j, stt_y, middle_2, fc, bc, 1, -1);
    }
    cct_showstr(stt_x + len, stt_y, right, fc, bc, 1, -1);
}

void show_border_3(const char* left, const char* md11, const char* md12, const char* md21, const char* md22, const char* right, int stt_x, int stt_y, int len, int fc, int bc, int k)
{
    cct_showstr(stt_x, stt_y, left, fc, bc, 1, -1);
    for (int j = 1; j < len; j++)
    {
        if (k % 4 == 0)
        {
            if (j % 8 == 0 && j > 7)
                cct_showstr(stt_x + j, stt_y, md11, fc, bc, 1, -1);
            else
                cct_showstr(stt_x + j, stt_y, md12, fc, bc, 1, -1);
        }
        else
        {
            if (j % 8 == 0 && j > 7)
                cct_showstr(stt_x + j, stt_y, md21, fc, bc, 1, -1);
            else
                cct_showstr(stt_x + j, stt_y, md22, fc, bc, 1, -1);
        }
    }
    cct_showstr(stt_x + len, stt_y, right, fc, bc, 1, -1);
}

void draw_2(int s, char bl[16][16])
{
    int t = 12 / (s / 5);
    int w = s * 10, h = s * 6;
    init(t, w, h, 8);
    for (int i = 0; i <= s * 4 + 1; i++)
    {
        cct_setcursor(CCT_CURSOR_INVISIBLE);
        if (i == 0)
        {
            for (int j = 0; j < s; j++)
                cout << "   " << (char)(j + 'a') << "    ";
            cout << endl;
        }
        if (i == 1)
        {
            int x, y;
            cct_getxy(x, y);
            cct_showstr(x, y, " ");
            show_border_2("╔", "╦", "═", "╗", x + 2, y, s * 8, COLOR_HWHITE, COLOR_BLACK);
            Sleep(50);
            cout << endl;
        }
        if (i >= 2 && i <= s * 4)
        {
            int x, y;
            cct_getxy(x, y);
            if ((i - 3) % 4 == 0)
            {
                cct_showch(x, y, (char)((i - 3) / 4 + 'A'));
                cct_showstr(x + 1, y, " ");
            }
            else
                cct_showstr(x, y, "  ");
            show_border_3("║", "╬", "═", "║", "  ", "║", x + 2, y, s * 8, COLOR_HWHITE, COLOR_BLACK, i - 1);
            Sleep(50);
            cout << endl;
        }
        if (i == s * 4 + 1)
        {
            int x, y;
            cct_getxy(x, y);
            cct_showstr(x, y, "  ");
            show_border_2("╚", "╩", "═", "╝", x + 2, y, s * 8, COLOR_HWHITE, COLOR_BLACK);
            Sleep(50);
            cout << endl;
        }
    }
    cct_gotoxy(5, 4);
    for (int i = 1; i <= s; i++)
    {
        for (int j = 1; j <= s; j++)
        {
            if (bl[i][j] == '0')
            {
                draw_ball(4 + (j - 1) * 8, 3 + (i - 1) * 4, 1);
                Sleep(50);
            }
        }
    }
    cct_gotoxy(0, s * 4 + 5);
    wait(1);
}


void draw_21(int s, char bl[16][16], int op)
{
    cct_setcursor(CCT_CURSOR_INVISIBLE);
    int _1[16][16] = { 0 }, _2[16][16] = { 0 };
    int cur_1[16] = { 0 }, cur_2[16] = { 0 };
    bool zb = false;
    for (int i = 1; i <= s; i++)
    {
        cur_1[i] = 0, cur_2[i] = 0;
        bool f1 = false, f2 = false;
        for (int j = 1; j <= s; j++)
        {
            if (bl[i][j] == '0')
            {
                if (f1 == false)
                    cur_1[i]++;
                f1 = true;
                _1[i][cur_1[i]]++;
            }
            else
                f1 = false;
            if (bl[j][i] == '0')
            {
                if (f2 == false)
                    cur_2[i]++;
                f2 = true;
                _2[i][cur_2[i]]++;
            }
            else
                f2 = false;
        }
    }
    int __1 = -1, __2 = -1;
    for (int t = 1; t <= s; t++)
    {
        __1 = max(__1, cur_1[t]);
        __2 = max(__2, cur_2[t]);
    }
    int t = 150 / (s + 15);
    int w = s * t * 2, h = (s)*t;
    char ip[16][16] = { 0 }, df[16][16] = { 0 };
    init(t, w, h, op);
    int x, y;
    cct_getxy(x, y);
    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
    show_border_1("╔", "═", "╗", x + 6 + __1 * 2, y, s * 4 - 1, COLOR_HWHITE, COLOR_BLACK);
    cout << endl;
    for (int i = 0; i < __2; i++)
    {
        cct_getxy(x, y);
        cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
        cct_showstr(x + 6 + __1 * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
        for (int j = 0; j < s; j++)
        {
            int t = i - (__2 - cur_2[j + 1]) + 1;
            if (_2[j + 1][t] != 0 && t > 0)
                cout << "  " << setw(2) << _2[j + 1][t] << "    ";
            else
                cout << "        ";
        }
        cct_showstr(x + 6 + __1 * 2 + s * 8, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
        cout << endl;
    }
    cct_getxy(x, y);
    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
    show_border_1("╠", "═", "╣", x + 6 + __1 * 2, y, s * 4 - 1, COLOR_HWHITE, COLOR_BLACK);
    cout << endl;
    cct_getxy(x, y);
    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 4 + __1 * 2);
    cct_showstr(x + 6 + __1 * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
    for (int i = 0; i < s; i++)
        cout << "   " << (char)(i + 'a') << "    ";
    cct_showstr(x + 6 + __1 * 2 + s * 8, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
    cout << endl;
    for (int i = 0; i <= s * 4 - 1; i++)
    {
        if (i == 0)
        {
            cct_getxy(x, y);
            show_border_1("╔", "═", "╦", x, y, __1, COLOR_HWHITE, COLOR_BLACK);
            cct_showstr(x + 4 + __1 * 2, y, "═", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            show_border_2("╬", "╦", "═", "╣", x + 6 + __1 * 2, y, s * 8, COLOR_HWHITE, COLOR_BLACK);
            cout << endl;
        }
        if (i < s * 4 - 1)
        {
            cct_getxy(x, y);
            cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            if ((i - 1) % 4 == 0)
            {
                for (int j = 0; j < __1; j++)
                {
                    int t = j + 1 - (__1 - cur_1[(i - 1) / 4 + 1]);
                    if (_1[(i - 1) / 4 + 1][t] != 0)
                    {
                        cct_showint(x + j * 2 + 2, y, _1[(i - 1) / 4 + 1][t], COLOR_HWHITE, COLOR_BLACK);
                        cct_showstr(x + j * 2 + 3, y, " ", COLOR_HWHITE, COLOR_BLACK);
                    }
                    else
                        cct_showstr(x + j * 2 + 2, y, "  ", COLOR_HWHITE, COLOR_BLACK);
                }
                cct_showstr(x + 2 + __1 * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
                cct_showstr(x + __1 * 2 + 4, y, " ", COLOR_HWHITE, COLOR_BLACK);
                cct_showch(x + __1 * 2 + 5, y, (char)((i - 1) / 4 + 'A'), COLOR_HWHITE, COLOR_BLACK);
            }
            else
            {
                for (int j = 0; j < __1; j++)
                    cct_showstr(x + j * 2 + 2, y, "  ", COLOR_HWHITE, COLOR_BLACK);
                cct_showstr(x + 2 + __1 * 2, y, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
                cct_showstr(x + __1 * 2 + 4, y, "  ", COLOR_HWHITE, COLOR_BLACK);
            }
            show_border_3("║", "╬", "═", "║", "  ", "║", x + 6 + __1 * 2, y, s * 8, COLOR_HWHITE, COLOR_BLACK, i + 1);
            cout << endl;
        }
        if (i == s * 4 - 1)
        {
            cct_getxy(x, y);
            show_border_1("╚", "═", "╩", x, y, __1, COLOR_HWHITE, COLOR_BLACK);
            cct_showstr(x + 4 + __1 * 2, y, "═", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            show_border_2("╩", "╩", "═", "╝", x + 6 + __1 * 2, y, s * 8, COLOR_HWHITE, COLOR_BLACK);
            cout << endl;
        }
    }
    if (op != 11)
    {
        for (int i = 1; i <= s; i++)
        {
            for (int j = 1; j <= s; j++)
            {
                if (bl[i][j] == '0')
                {
                    draw_ball(8 + (j - 1) * 8 + __1 * 2, 5 + (i - 1) * 4 + __2, 1);
                    Sleep(10);
                }
            }
        }
    }
    if (op == 9)
    {
        cct_gotoxy(0, s * 4 + 7 + __2);
        wait(1);
    }
    else if (op == 10 || op == 11)
    {
        cct_setcursor(CCT_CURSOR_INVISIBLE);
        cct_enable_mouse();
        cct_gotoxy(8 + __1 * 2, 5 + __2);
        cct_gotoxy(0, s + 7 + __2);
        int mx = 0, my = 0, ma = 0, kc1 = 0, kc2 = 0;
        int ev = 0;
        while (1)
        {
            cct_enable_mouse();
            ev = cct_read_keyboard_and_mouse(mx, my, ma, kc1, kc2);
            if (ev == CCT_KEYBOARD_EVENT)
            {
                if (kc1 == 13)
                {
                    if (read_enter(8 + __1 * 2, 6 + __2 + s * 4, op) == 1)
                        break;
                    else
                        continue;
                }
                if (kc1 == 0xe0)
                    read_arrow(kc1, kc2, 8 + __1 * 2, 6 + __2 + s * 4);
                else if (kc1 > 0)
                {
                    if (op == 11 && (kc1 == 'Q' || kc1 == 'q'))
                    {
                        cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到Q/q，游戏结束]");
                        cout << endl;
                        break;
                    }
                    else if (op == 11 && (kc1 == 'Z' || kc1 == 'z'))
                    {
                        if (zb == false)
                        {
                            zb = true;
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[作弊模式开]                              ");
                            for (int i = 1; i <= s; i++)
                            {
                                for (int j = 1; j <= s; j++)
                                {
                                    if (bl[i][j] == '0')
                                    {
                                        if (ip[i][j] != '0')
                                            draw_ball(8 + (j - 1) * 8 + __1 * 2, 5 + (i - 1) * 4 + __2, 9);
                                        if (df[i][j] == '0')
                                            draw_ball(8 + (j - 1) * 8 + __1 * 2, 5 + (i - 1) * 4 + __2, 8);
                                    }
                                    else
                                    {
                                        if (ip[i][j] == '0')
                                            draw_ball(8 + (j - 1) * 8 + __1 * 2, 5 + (i - 1) * 4 + __2, 7);
                                    }
                                }
                            }
                        }
                        else
                        {
                            zb = false;
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[作弊模式关]                              ");
                            for (int i = 1; i <= s; i++)
                            {
                                for (int j = 1; j <= s; j++)
                                {
                                    draw_ball(8 + (j - 1) * 8 + __1 * 2, 5 + (i - 1) * 4 + __2, 3);
                                    if (ip[i][j] == '0')
                                        draw_ball(8 + (j - 1) * 8 + __1 * 2, 5 + (i - 1) * 4 + __2, 1);
                                    if (df[i][j] == '0')
                                        draw_ball(8 + (j - 1) * 8 + __1 * 2, 5 + (i - 1) * 4 + __2, 2);

                                }
                            }
                        }
                        continue;
                    }
                    else if (op == 11 && (kc1 == 'Y' || kc1 == 'y'))
                    {
                        cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到提交键]                              ");
                        Sleep(100);
                        if (!game_check(s, bl, ip))
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "提交失败，请在作弊模式中查看");
                        else
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[提交成功]                       ");
                            cout << endl;
                            wait(1);
                            return;
                        }
                        continue;
                    }
                    cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到键码]");
                    cout << kc1 << "/" << kc2 << "                               ";
                }
                else
                    cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到键码]0/0             ");
            }
            else if (ev == CCT_MOUSE_EVENT)
            {
                int Valid_x1, Valid_x2, Valid_y1, Valid_y2;
                Valid_x1 = 8 + __1 * 2, Valid_y1 = 5 + __2;
                Valid_x2 = Valid_x1 + s * 8 - 1, Valid_y2 = Valid_y1 + s * 4 - 1;
                if ((mx >= Valid_x1 && mx <= Valid_x2) && (my >= Valid_y1 && my <= Valid_y2))
                {
                    cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[当前光标] ");
                    int Cur_x, Cur_y;
                    if ((mx - Valid_x1) % 8 == 7 || (my - Valid_y1) % 4 == 3)
                    {
                        cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[当前光标] 位置非法                    ");
                        continue;
                    }
                    Cur_x = (mx - Valid_x1) / 8, Cur_y = (my - Valid_y1) / 4;
                    cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列                ";
                    if (op == 10)
                    {
                        if (ma == MOUSE_LEFT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到左键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列       " << endl;
                            int cols, lines, b_cols, b_lines;
                            cct_getconsoleborder(cols, lines, b_cols, b_lines);
                            cct_showstr(0, 7 + __2 + s * 4, "窗口：");
                            cout << cols << "行，" << lines << "列" << endl;
                            break;
                        }
                        else if (ma == MOUSE_RIGHT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到右键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列       " << endl;
                            int cols, lines, b_cols, b_lines;
                            cct_getconsoleborder(cols, lines, b_cols, b_lines);
                            cct_showstr(0, 7 + __2 + s * 4, "窗口：");
                            cout << cols << "行，" << lines << "列" << endl;
                            break;
                        }
                    }
                    else if (op == 11)
                    {
                        if (ma == MOUSE_LEFT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到左键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列                 " << endl;
                            if (zb == false)
                            {
                                if (ip[Cur_y + 1][Cur_x + 1] != '0')
                                {
                                    ip[Cur_y + 1][Cur_x + 1] = '0';
                                    draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 1);
                                }
                                else
                                {
                                    ip[Cur_y + 1][Cur_x + 1] = 0;
                                    draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 3);
                                }
                            }
                            else
                            {
                                if (bl[Cur_y + 1][Cur_x + 1] == '0')
                                {
                                    if (ip[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = '0';
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 1);
                                    }
                                    else
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 9);
                                    }
                                }
                                else
                                {
                                    if (ip[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = '0';
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 7);
                                    }
                                    else
                                    {
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 3);
                                    }
                                }
                            }
                        }
                        else if (ma == MOUSE_RIGHT_BUTTON_CLICK)
                        {
                            cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[读到右键] ");
                            cout << (char)(Cur_y + 'A') << "行" << (char)(Cur_x + 'a') << "列                 " << endl;
                            if (zb == false)
                            {
                                if (df[Cur_y + 1][Cur_x + 1] != '0')
                                {
                                    df[Cur_y + 1][Cur_x + 1] = '0';
                                    ip[Cur_y + 1][Cur_x + 1] = 0;
                                    draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 2);
                                }
                                else
                                {
                                    df[Cur_y + 1][Cur_x + 1] = 0;
                                    draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 3);
                                }
                            }
                            else
                            {
                                if (bl[Cur_y + 1][Cur_x + 1] == '0')
                                {
                                    if (df[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = '0';
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 8);
                                    }
                                    else
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = 0;
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 9);
                                    }
                                }
                                else
                                {
                                    if (df[Cur_y + 1][Cur_x + 1] != '0')
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = '0';
                                        ip[Cur_y + 1][Cur_x + 1] = 0;
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 2);
                                    }
                                    else
                                    {
                                        df[Cur_y + 1][Cur_x + 1] = 0;
                                        draw_ball(8 + Cur_x * 8 + __1 * 2, 5 + Cur_y * 4 + __2, 3);
                                    }
                                }
                            }
                        }
                    }
                }
                else
                    cct_showstr(8 + __1 * 2, 6 + __2 + s * 4, "[当前光标] 位置非法");
            }
        }
        wait(1);
    }
}