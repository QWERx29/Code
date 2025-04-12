/* 学号 班级 姓名 */
#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

/* -----------------------------------------------------------------------------------
        允许   ：1、按需增加一个或多个函数（包括递归函数），但是所有增加的函数中不允许任何形式的循环
                 2、定义符号常量
                 3、定义const型变量

        不允许 ：1、定义全局变量
                 2、除print_tower之外的其他函数中不允许定义静态局部变量
   ----------------------------------------------------------------------------------- */

void print_space(int n)
{
    if (n <= 0)
        return;
    cout << " ";
    print_space(n - 1);
}
void print_row(char ch, char End_ch)
{
    cout << ch;
    if (ch > End_ch)
    {
        print_row(ch - 1, End_ch);
        cout << ch;
    }
}
void print_tower(char Start_ch, char End_ch, int len, bool order)
{
    if ((order && Start_ch < End_ch) || (!order && Start_ch > End_ch))
        return;
    int sp = len - (Start_ch - 'A' + 1);
    print_space(sp);
    print_row(Start_ch, 'A');
    cout << endl;
    if (order)
        print_tower(Start_ch - 1, End_ch, len, order);
    else
        print_tower(Start_ch + 1, End_ch, len, order);
}

int main()
{
    char end_ch;
    // 键盘输入结束字符(仅大写有效，为避免循环出现，不处理输入错误)
    cout << "请输入结束字符(A~Z)" << endl;
    end_ch = getchar(); // 读缓冲区第一个字符
    if (end_ch < 'A' || end_ch > 'Z')
    {
        cout << "结束字符不是大写字母" << endl;
        return -1;
    }

    /* 正三角字母塔(中间为A) */
    cout << setfill('=') << setw((end_ch - 'A') * 2 + 1) << '=' << endl;
    cout << "正三角字母塔(" << end_ch << "->A)" << endl;
    cout << setfill('=') << setw((end_ch - 'A') * 2 + 1) << '=' << endl;
    print_tower('A', end_ch, (end_ch - 'A' + 1), 0); // 正序打印 A~结束字符
    cout << endl;

    /* 倒三角字母塔(中间为A) */
    cout << setfill('=') << setw((end_ch - 'A') * 2 + 1) << '=' << endl;
    cout << "倒三角字母塔(" << end_ch << "->A)" << endl;
    cout << setfill('=') << setw((end_ch - 'A') * 2 + 1) << '=' << endl;
    print_tower(end_ch, 'A', (end_ch - 'A' + 1), 1); // 逆序打印 A~结束字符
    cout << endl;

    /* 合起来就是漂亮的菱形（中间为A） */
    cout << setfill('=') << setw((end_ch - 'A') * 2 + 1) << '=' << endl; /* 按字母塔最大宽度输出= */
    cout << "菱形(" << end_ch << "->A)" << endl;
    cout << setfill('=') << setw((end_ch - 'A') * 2 + 1) << '=' << endl; /* 按字母塔最大宽度输出= */
    print_tower('A', end_ch, (end_ch - 'A' + 1), 0);                     // 打印 A~结束字符的正三角
    print_tower(end_ch - 1, 'A', (end_ch - 'A' + 1), 1);                 // 打印 A~结束字符-1的倒三角
    cout << endl;

    return 0;
}