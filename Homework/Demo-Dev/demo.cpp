#include <iostream>
#include <conio.h>
#include <cctype>
#include <cstring>
using namespace std;

// 假设的CCT控制函数声明
/*
void cct_cls();
void cct_setfontsize(const char *font, int width, int height);
void cct_setcursor(int type);
void cct_setconsoleborder(int width, int height, int rows, int cols);
*/

int show_menu(const char *title, const char *menu_items[], int item_count, const char *separators[], int sep_count)
{
    /*
    cct_cls();
    cct_setfontsize("新宋体", 16, 8);
    cct_setcursor(1); // CCT_CURSOR_VISIBLE_NORMAL
    cct_setconsoleborder(120, 40, 120, 9001);*/

    cout << "---------------------------------------------------------" << endl;
    cout << title << endl;
    cout << "---------------------------------------------------------" << endl;

    int sep_index = 0;
    for (int i = 0; i < item_count; i++)
    {
        // 在适当位置插入分隔线
        if (sep_index < sep_count && separators[sep_index] != nullptr &&
            (i == 3 || i == 7 || i == 11))
        { // 分隔线的位置
            cout << separators[sep_index] << endl;
            sep_index++;
        }
        cout << menu_items[i] << endl;
    }

    if (sep_index < sep_count && separators[sep_index] != nullptr)
    {
        cout << separators[sep_index] << endl;
    }

    cout << "---------------------------------------------------------" << endl;
    cout << "[请选择:]";

    char op;
    while (1)
    {
        op = _getch();
        // 根据菜单类型检查输入范围
        if (strstr(title, "汉诺塔") != nullptr)
        {
            // 汉诺塔菜单：0-9
            if (op >= '0' && op <= '9')
            {
                cout << op << endl;
                return op - '0';
            }
        }
        else
        {
            // 主菜单：A-K, Q
            if ((op >= 'A' && op <= 'K') || op == 'Q' ||
                (op >= 'a' && op <= 'k') || op == 'q')
            {
                cout << op;
                op = toupper(op);
                if (op == 'Q')
                    return 0;
                return op - 'A' + 1;
            }
        }
    }
}

void display_menu(const char *menu_items[])
{
    for (int i = 0; menu_items[i] != nullptr; i++)
    {
        cout << menu_items[i] << endl;
    }
}

int menu()
{
    // 主菜单选项
    const char *main_menu_items[] = {
        "A.内部数组，原样输出",
        "B.内部数组，生成提示行列并输出",
        "C.内部数组，游戏版",
        "D.n * n的框架(无分隔线)，原样输出",
        "E.n * n的框架(无分隔线)，含提示行列",
        "F.n * n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标",
        "G.cmd图形界面完整版(无分隔线)",
        "H.n * n的框架(有分隔线)，原样输出",
        "I.n * n的框架(有分隔线)，含提示行列",
        "J.n * n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标",
        "K.cmd图形界面完整版(有分隔线)",
        "Q.退出"};

    // 主菜单分隔线
    const char *main_separators[] = {
        " --------------------------------------------------------",
        " --------------------------------------------------------",
        " --------------------------------------------------------",
        nullptr};

    return show_menu("主菜单", main_menu_items, 12, main_separators, 4);
}

int hanoi_menu()
{
    // 汉诺塔菜单选项
    const char *hanoi_items[] = {
        "1.基本解",
        "2.基本解(步数记录)",
        "3.内部数组显示(横向)",
        "4.内部数组显示(纵向+横向)",
        "5.图形解-预备-画三个圆柱",
        "6.图形解-预备-在起始柱上画n个盘子",
        "7.图形解-预备-第一次移动",
        "8.图形解-自动移动版本",
        "9.图形解-游戏版",
        "0.退出"};

    const char *hanoi_separators[] = {nullptr}; // 汉诺塔菜单无额外分隔线

    return show_menu("汉诺塔菜单", hanoi_items, 10, hanoi_separators, 0);
}

// 示例使用
int main()
{
    int choice;

    while (true)
    {
        // 显示主菜单
        choice = menu();

        if (choice == 0)
        {
            cout << "退出程序" << endl;
            break;
        }
        else if (choice == 12)
        { // 假设第12项是汉诺塔菜单入口
            // 显示汉诺塔菜单
            int hanoi_choice = hanoi_menu();
            if (hanoi_choice == 0)
            {
                cout << "退出汉诺塔菜单" << endl;
            }
            else
            {
                cout << "执行汉诺塔功能: " << hanoi_choice << endl;
            }
        }
        else
        {
            cout << "执行主菜单功能: " << choice << endl;
        }
    }

    return 0;
}