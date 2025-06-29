// 2451317 冯久恒 计算机
#include<iostream>
#include<time.h>
#include<iomanip>
#include"pullze.h"
#include"cmd_console_tools.h"
using namespace std;

void output_1(int s, char bl[16][16])
{
    cout << "+-+";
    for (int i = 0; i < s; i++)
    {
        cout << "--";
        if ((i + 1) % 5 == 0)
            cout << "-+";
    }
    cout << endl;
    cout << "| | ";
    for (int i = 0; i < s; i++)
    {
        cout << (char)(i + 'a') << " ";
        if ((i + 1) % 5 == 0)
            cout << "| ";
    }
    cout << endl;
    for (int i = 0; i <= s; i++)
    {
        if (i % 5 == 0)
        {
            cout << "+-+";
            for (int i = 0; i < s; i++)
            {
                cout << "--";
                if ((i + 1) % 5 == 0)
                    cout << "-+";
            }
            cout << endl;
        }
        if(i < s)
            cout << "|" << (char)(i + 'A') << "| ";
        for (int j = 0; j < s; j++)
        {
            if (bl[i + 1][j + 1] == '0')
                cout << "0 ";
            else
                cout << "  ";
            if ((j + 1) % 5 == 0 && i < s)
                cout << "| ";
        }
        cout << endl;
    }
}
void output_2(int s, char bl[16][16], char ip[16][16], int op)
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
    for (int i = 0; i < __1; i++)
        cout << "--";
    cout << "---+";
    for (int i = 0; i < s; i++)
    {
        cout << "--";
        if ((i + 1) % 5 == 0)
            cout << "-+";
    }
    cout << endl;
    for (int i = 0; i < __2; i++)
    {
        for (int i = 0; i < __1; i++)
            cout << "  ";
        cout << "   |";
        for (int j = 0; j < s; j++)
        {
            int t = i - (__2 - cur_2[j + 1]) + 1;
            if (_2[j + 1][t] != 0 && t > 0)
                cout << setw(2) << _2[j + 1][t];
            else
                cout << "  ";
            if ((j + 1) % 5 == 0 && j < s - 5)
                cout << " |";
        }
        cout << " |" << endl;
    }
    for (int i = 0; i < __1; i++)
        cout << "--";
    cout << "---+";
    for (int i = 0; i < s; i++)
    {
        cout << "--";
        if ((i + 1) % 5 == 0)
            cout << "-+";
    }
    cout << endl;
    for (int i = 0; i < __1; i++)
        cout << "  ";
    cout << "   | ";
    for (int i = 0; i < s; i++)
    {
        cout << (char)(i + 'a') << " ";
        if ((i + 1) % 5 == 0)
            cout << "| ";
    }
    cout << endl;
    for (int i = 0; i <= s; i++)
    {
        if (i % 5 == 0)
        {
            for (int i = 0; i < __1; i++)
                cout << "--";
            cout << "-+-+";
            for (int i = 0; i < s; i++)
            {
                cout << "--";
                if ((i + 1) % 5 == 0)
                    cout << "-+";
            }
            cout << endl;
        }
        if (i < s)
        {
            for (int j = 0; j < __1; j++)
            {
                int t = j + 1 - (__1 - cur_1[i + 1]);
                if (_1[i + 1][t] != 0)
                    cout << setw(2) << _1[i + 1][t];
                else
                    cout << "  ";
            }
            cout << " |" << (char)(i + 'A') << "| ";
        }
        for (int j = 0; j < s; j++)
        {
            if (bl[i + 1][j + 1] == '0' && op == 2)
                cout << "0 ";
            else if (ip[i + 1][j + 1] == '0' && op == 9)
            {
                int x, y;
                cct_getxy(x, y);
                cct_showch(x, y, '0', COLOR_HYELLOW, COLOR_BLUE, 1);
                cct_showch(x + 1, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
            }
            else if (op == 8)
            {
                int x, y;
                cct_getxy(x, y);
                if (ip[i + 1][j + 1] == '0')
                {
                    if (bl[i + 1][j + 1] == '0')
                    {
                        cct_showch(x, y, '0', COLOR_HYELLOW, COLOR_BLUE, 1);
                        cct_showch(x + 1, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
                    }
                    else
                    {
                        cct_showch(x, y, 'X', COLOR_HYELLOW, COLOR_BLUE, 1);
                        cct_showch(x + 1, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
                    }
                }
                else if (bl[i + 1][j + 1] == '0')
                    cct_showstr(x, y, "0 ");
                else 
                    cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 2);
            }
            else
            {
                int x, y;
                cct_getxy(x, y);
                cct_showch(x, y, ' ', COLOR_BLACK, COLOR_WHITE, 2);
            }
            if ((j + 1) % 5 == 0 && i < s)
                cout << "| ";
        }
        cout << endl;
    }
}
void output(int s, char bl[16][16], int op)
{
    if (op == 1)
        output_1(s, bl);
    else if (op == 2)
        output_2(s, bl, bl, 2);
    else if (op == 3)
        output_2(s, bl, bl, 3);
}

void puzzle_game(int s, char bl[16][16]);

void puzzle_base(int s, int op)
{
    int sum = (s * s) / 2 + 1;
    char bl[16][16] = { 0 };
    srand((unsigned int)(time(0))); // 生成伪随机数的种子，只需在程序开始时执行一次即可
    for (int i = 1, t = 1; t <= sum; i++)
    {
        int x = rand() % s + 1, y = rand() % s + 1;
        if (bl[x][y] != '0')
        {
            bl[x][y] = '0';
            t++;
        }
        else
            continue;
    }
    if (op == 1 || op == 2)
    {
        output(s, bl, op);
        wait(1);
    }
    else if (op == 3)
        puzzle_game(s, bl);
    else if (op == 4)
        draw_1(s, bl);
    else if (op >= 5 && op <= 7)
        draw_11(s, bl, op);
    else if (op == 8)
        draw_2(s, bl);
    else if (op >= 9 && op <= 11)
        draw_21(s, bl, op);
}
bool game_check(int s, char bl[16][16], char ip[16][16])
{
    int bl_1[16][16] = { 0 }, bl_2[16][16] = { 0 };
    for (int i = 1; i <= s; i++)
    {
        int cur_1 = 0, cur_2 = 0;
        bool f1 = false, f2 = false;
        for (int j = 1; j <= s; j++)
        {
            if (bl[i][j] == '0')
            {
                if (f1 == false)
                    cur_1++;
                f1 = true;
                bl_1[i][cur_1]++;
            }
            else
                f1 = false;
            if (bl[j][i] == '0')
            {
                if (f2 == false)
                    cur_2++;
                f2 = true;
                bl_2[i][cur_2]++;
            }
            else
                f2 = false;
        }
    }
    int ip_1[16][16] = { 0 }, ip_2[16][16] = { 0 };
    for (int i = 1; i <= s; i++)
    {
        int cur_1 = 0, cur_2 = 0;
        bool f1 = false, f2 = false;
        for (int j = 1; j <= s; j++)
        {
            if (ip[i][j] == '0')
            {
                if (f1 == false)
                    cur_1++;
                f1 = true;
                ip_1[i][cur_1]++;
            }
            else
                f1 = false;
            if (ip[j][i] == '0')
            {
                if (f2 == false)
                    cur_2++;
                f2 = true;
                ip_2[i][cur_2]++;
            }
            else
                f2 = false;
        }
    }
    for (int i = 1; i <= s; i++)
    {
        for (int j = 1; j <= s; j++)
        {
            if (bl_1[i][j] != ip_1[i][j] || bl_2[i][j] != ip_2[i][j])
                return false;
        }
    }
    return true;
}
void puzzle_game(int s,char bl[16][16])
{
    char ip[16][16] = { 0 };
    bool zb = false;
    int oop = 9;
    cout << "初始数组：" << endl;
    output(s, bl, 3);
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    while (1)
    {
        char pt[4] = { 0 };
        cout << endl;
        cout << "命令形式：Aa=等价于图形游戏中鼠标左键选择Aa位(区分大小写)" << endl;
        cout << "             不需要支持图形界面的右键打叉，再次输入Aa相当于清除" << endl;
        cout << "          X / x = 退出(新行仅有X / x，不分大小写)" << endl;
        cout << "          Y / y = 提交(新行仅有Y / y，不分大小写)" << endl;
        cout << "          Z / z = 作弊(新行仅有Z / z，不分大小写)" << endl;
        cout << "          Ctrl + c 强制退出" << endl;
        cout << "请输入 : ";
        if (fgets(pt, 3, stdin) == NULL)
        {
            cin.clear();
            continue;
        }
        if (pt[0] == '\n')
        {
            cout << "输入错误" << endl << endl;
            continue;
        }
        if ((pt[0] >= 'A' && pt[0] <= s + 'A' - 1) && (pt[1] >= 'a' && pt[1] <= s + 'a' - 1) && pt[2] == '\0')
        {
            cout << "输入" << pt << "后：" << endl;
            int x, y;
            x = pt[0] - 'A' + 1;
            y = pt[1] - 'a' + 1;
            if (ip[x][y] != '0')
                ip[x][y] = '0';
            else
                ip[x][y] = 0;
            output_2(s, bl, ip, oop);
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        else if ((pt[0] == 'X' || pt[0] == 'x') && pt[1] == '\n')
        {
            wait(0);
            return;
        }
        else if ((pt[0] == 'Y' || pt[0] == 'y') && pt[1] == '\n')
        {
            if (!game_check(s, bl, ip))
                cout << "提交错误, 请在作弊模式中查看" << endl;
            else
            {
                cout << "提交成功，游戏结束" << endl;
                wait(0);
                return;
            }
            continue;
        }
        else if ((pt[0] == 'Z' || pt[0] == 'z') && pt[1] == '\n')
        {
            cout << "输入Z/z后：" << endl;
            if (zb == false)
            {
                zb = true;
                oop = 8;
            }
            else
            {
                zb = false;
                oop = 9;
            }
            output_2(s, bl, ip, oop);
            continue;
        }
        else
        {   
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "输入错误" << endl << endl;
            continue;
        }
    }
}