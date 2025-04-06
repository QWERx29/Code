// 2451317 冯久恒 计算机 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

const int MAX_X = 69; // 定义*组成的边框的宽度
const int MAX_Y = 17; // 定义*组成的边框的高度

void cls(const HANDLE hout)
{
    COORD coord = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO binfo; // to get buffer info
    DWORD num;
    GetConsoleScreenBufferInfo(hout, &binfo);                                                          // 取当前缓冲区信息
    FillConsoleOutputCharacter(hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);        // 填充字符
    FillConsoleOutputAttribute(hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num); // 填充属性
    SetConsoleCursorPosition(hout, coord);                                                             // 光标回到(0,0)
    return;
}

void gotoxy(const HANDLE hout, const int X, const int Y)
{
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    SetConsoleCursorPosition(hout, coord);
}

void showch(const HANDLE hout, const int X, const int Y, const char ch)
{
    gotoxy(hout, X, Y);
    putchar(ch);
}

void init_border(const HANDLE hout)
{
    gotoxy(hout, 0, 0); // 光标移回左上角(0,0)
    printf("***********************************************************************\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("*                                                                     *\n");
    printf("***********************************************************************\n");

    /* 随机显示20个大写字母，字母的值、XY坐标都随机显示
       rand()函数的功能：随机生成一个在 0-32767 之间的整数
       思考：在什么情况下，下面这个循环执行生成后，你看到的实际字母个数不足20个？ */
    int i;
    for (i = 0; i < 20; i++)
        showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

    return;
}

void menu(const HANDLE hout)
{
    cls(hout); // 调用系统的cls命令清屏
    gotoxy(hout, 0, 0);
    printf("1.用I、J、K、L键控制上下左右(大小写均可，按左箭头光标不允许下移，边界停止)\n");
    printf("2.用I、J、K、L键控制上下左右(大小写均可，按左箭头光标不允许下移，边界回绕)\n");
    printf("3.用箭头键控制上下左右(按大写HPKM不允许移动光标,边界停止)\n");
    printf("4.用箭头键控制上下左右(按大写HPKM不允许移动光标,边界回绕)\n");
    printf("0.退出\n");
    printf("[请选择0 - 4]");
}
// 输出结束提示
void end(const HANDLE hout)
{
    gotoxy(hout, 0, 23);
    printf("游戏结束，按回车键退出.");
    while (_getch() != '\r')
        ;
}
// 抹掉字符
void erase(const HANDLE hout, int curX, int curY)
{
    showch(hout, curX, curY, ' ');
    gotoxy(hout, curX, curY);
}

void Move_by_IJKL(const HANDLE hout, int if_cross)
{
    int op;
    int curX = MAX_X / 2, curY = (MAX_Y + 1) / 2;
    gotoxy(hout, curX, curY);
    while (1)
    {
        op = _getch();
        if (op == 0xE0 || op == 0)
        {
            _getch();
            continue;
        } // 避免按向左箭头光标下移
        op = toupper(op);
        if (op == 'Q')
        {
            end(hout);
            break;
        }
        else if (op == ' ')
            erase(hout, curX, curY);
        else
        {
            if (op == 'I')
                curY--;
            if (op == 'K')
                curY++;
            if (op == 'J')
                curX--;
            if (op == 'L')
                curX++;
        }
        if (if_cross)
        {
            if (curX > MAX_X)
                curX = 1;
            if (curX < 1)
                curX = MAX_X;
            if (curY > MAX_Y)
                curY = 1;
            if (curY < 1)
                curY = MAX_Y;
        }
        else
        {
            if (curX > MAX_X)
                curX = MAX_X;
            if (curX < 1)
                curX = 1;
            if (curY > MAX_Y)
                curY = MAX_Y;
            if (curY < 1)
                curY = 1;
        }
        gotoxy(hout, curX, curY);
    }
}

void Move_by_ARROW(const HANDLE hout, int if_cross)
{
    int op;
    int curX = MAX_X / 2, curY = (MAX_Y + 1) / 2;
    gotoxy(hout, curX, curY);
    while (1)
    {
        op = _getch();
        if (op == 0xE0 || op == 0)
        {
            int dr = _getch();
            if (dr == 72)
                curY--;
            if (dr == 80)
                curY++;
            if (dr == 75)
                curX--;
            if (dr == 77)
                curX++;
            if (if_cross)
            {
                if (curX > MAX_X)
                    curX = 1;
                if (curX < 1)
                    curX = MAX_X;
                if (curY > MAX_Y)
                    curY = 1;
                if (curY < 1)
                    curY = MAX_Y;
            }
            else
            {
                if (curX > MAX_X)
                    curX = MAX_X;
                if (curX < 1)
                    curX = 1;
                if (curY > MAX_Y)
                    curY = MAX_Y;
                if (curY < 1)
                    curY = 1;
            }
            gotoxy(hout, curX, curY);
        }
        else if (toupper(op) == 'Q')
        {
            end(hout);
            break;
        }
        else if (op == ' ')
            erase(hout, curX, curY);
    }
}

int main()
{
    const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); // 取标准输出设备对应的句柄
    srand((unsigned int)(time(0)));                      // 生成伪随机数的种子，只需在程序开始时执行一次即可
    cls(hout);                                           // 此句的作用是调用系统的cls命令清屏
    while (1)
    {
        menu(hout); // 显示菜单
        char op = _getch();
        if (op == '0')
            return 0;
        else if (op > '4' || op < '0')
            continue;
        int if_cross = 1;
        cls(hout);
        init_border(hout); // 显示初始的边框及其中的随机字符
        if (op == '1' || op == '3')
            if_cross = 0;
        if (op == '1' || op == '2')
            Move_by_IJKL(hout, if_cross);
        else
            Move_by_ARROW(hout, if_cross);
    }

    return 0;
}