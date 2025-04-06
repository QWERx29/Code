/* 学号 姓名 班级 */
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;
// 以下内容不许编辑
const int MAX_X = 69; // 定义*组成的边框的宽度
const int MAX_Y = 17; // 定义*组成的边框的高度

void cls(const HANDLE hout) // 清除整个屏幕缓冲区,不仅仅是可见窗口区域(使用当前颜色)
{
    COORD coord = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO binfo; // to get buffer info
    DWORD num;

    GetConsoleScreenBufferInfo(hout, &binfo);                                                          // 取当前缓冲区信息
    FillConsoleOutputCharacter(hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);        // 填充字符
    FillConsoleOutputAttribute(hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num); // 填充属性
    SetConsoleCursorPosition(hout, coord);                                                             // 光标回到(0,0)
    return;
}

void gotoxy(const HANDLE hout, const int X, const int Y) // 将光标移动到指定位置
{
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    SetConsoleCursorPosition(hout, coord);
}

void showch(const HANDLE hout, const int X, const int Y, const char ch) // 在指定位置处打印一个指定的字符
{
    gotoxy(hout, X, Y);
    putchar(ch);
}

void init_border(const HANDLE hout) // 显示初始的边框及随机字符
{
    gotoxy(hout, 0, 0); // 光标移回左上角(0,0)
    cout << "***********************************************************************" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "*                                                                     *" << endl;
    cout << "***********************************************************************" << endl;

    /* 随机显示20个大写字母，字母的值、XY坐标都随机显示
       rand()函数的功能：随机生成一个在 0-32767 之间的整数
       思考：在什么情况下，下面这个循环执行生成后，你看到的实际字母个数不足20个？ */
    int i;
    for (i = 0; i < 20; i++)
        showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

    return;
}

// 以上内容不许修改
// 显示菜单
void menu(const HANDLE hout)
{
    cls(hout); // 调用系统的cls命令清屏
    gotoxy(hout, 0, 0);
    cout << "1.用I、J、K、L键控制上下左右(大小写均可，按左箭头光标不允许下移，边界停止)" << endl
         << "2.用I、J、K、L键控制上下左右(大小写均可，按左箭头光标不允许下移，边界回绕)" << endl
         << "3.用箭头键控制上下左右(按大写HPKM不允许移动光标,边界停止)" << endl
         << "4.用箭头键控制上下左右(按大写HPKM不允许移动光标,边界回绕)" << endl;
    cout << "0.退出" << endl
         << "[请选择0 - 4]";
}
// 输出结束提示
void end(const HANDLE hout)
{
    gotoxy(hout, 0, 23);
    cout << "游戏结束，按回车键退出.";
    while (_getch() != '\r')
        ;
}
// 抹掉字符
void erase(const HANDLE hout, int curX, int curY)
{
    showch(hout, curX, curY, ' ');
    gotoxy(hout, curX, curY);
}

void Move_by_IJKL(const HANDLE hout, bool if_cross)
{
    int op;
    int curX = MAX_X / 2, curY = (MAX_Y + 1) / 2;
    gotoxy(hout, curX, curY);
    while (true)
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

void Move_by_ARROW(const HANDLE hout, bool if_cross)
{
    int op;
    int curX = MAX_X / 2, curY = (MAX_Y + 1) / 2;
    gotoxy(hout, curX, curY);
    while (true)
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
    while (true)
    {
        menu(hout); // 显示菜单
        char op = _getch();
        if (op == '0')
            return 0;
        else if (op > '4' || op < '0')
            continue;
        bool if_cross = true;
        cls(hout);
        init_border(hout); // 显示初始的边框及其中的随机字符
        if (op == '1' || op == '3')
            if_cross = false;
        if (op == '1' || op == '2')
            Move_by_IJKL(hout, if_cross);
        else
            Move_by_ARROW(hout, if_cross);
    }

    return 0;
}