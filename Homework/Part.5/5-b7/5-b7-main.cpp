// 2451317 冯久恒 计算机
#include<iostream>
#include<limits>
#include<iomanip>
#include<Windows.h>
#include"5-b7.h"

using namespace std;

int topA = -1, topB = -1, topC = -1, plateA[10], plateB[10], plateC[10], cnt = 1;
int delay, show_plate;

void output(int n, char src, char dst)
{
    cct_cls();
    cct_gotoxy(15, 25);
    cout << "第" << setw(4) << cnt << "步(" << setw(2) << n << ") : " << src << "-->" << dst;
    if (dst == 'A')
        topA++, plateA[topA] = n;
    else if (dst == 'B')
        topB++, plateB[topB] = n;
    else
        topC++, plateC[topC] = n;
    if (src == 'A')
        plateA[topA] = 0, topA--;
    else if (src == 'B')
        plateB[topB] = 0, topB--;
    else
        plateC[topC] = 0, topC--;
    if (show_plate == 1)
    {
        printf(" A:");
        for (int j = 0; j < 10; j++)
        {
            if (plateA[j] != 0 && topA != -1)
                cout << setw(2) << plateA[j];
            else
                cout << "  ";
        }
        printf(" B:");
        for (int j = 0; j < 10; j++)
        {
            if (plateB[j] != 0 && topB != -1)
                cout << setw(2) << plateB[j];
            else
                cout << "  ";
        }
        printf(" C:");
        for (int j = 0; j < 10; j++)
        {
            if (plateC[j] != 0 && topC != -1)
                cout << setw(2) << plateC[j];
            else
                cout << "  ";
        }
    }
    cct_gotoxy(0, 20);
    cout << "     ==============================" << endl;
    for (char ch = 'A'; ch <= 'C'; ch++)
        cout << setw(10) << ch;
    cct_gotoxy(8, 19);
    for (int i = 0; i < 10; i++)
    {
        cct_gotoxy(8, 19 - i);
        if (plateA[i] != 0 && topA != -1)
            cout << setw(2) << plateA[i];
        else
            cout << "  ";
    }
    cct_gotoxy(18, 19);
    for (int i = 0; i < 10; i++)
    {   cct_gotoxy(18, 19 - i);
        if (plateB[i] != 0 && topB != -1)
            cout << setw(2) << plateB[i];
        else
            cout << "  ";
    }
    cct_gotoxy(28, 19);
    for (int i = 0; i < 10; i++)
    {
        cct_gotoxy(28, 19 - i);
        if (plateC[i] != 0 && topC != -1)
            cout << setw(2) << plateC[i];
        else
            cout << "  ";
    }
    cnt++;
    printf("\n");
    if (delay == 0)
        getchar();
    else
        Sleep(300 * (5-delay));

}
void hanoi(int n, char src, char tmp, char dst) // n-层数;src-起始柱;tmp-中间柱;dst-目标柱
{

    if (n == 1)
    {
        output(n, src, dst);
        return;
    }
    hanoi(n - 1, src, dst, tmp);
    output(n, src, dst);
    hanoi(n - 1, tmp, src, dst);
}

int main()
{
    int n;
    char src, dst, tmp;
    // Input n
    while (1)
    {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> n;
        if (cin.good() != 1 || (n < 1 || n > 10))
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
        cin >> src;
        src = toupper(src);
        if (cin.good() != 1 || (src < 'A' || src > 'C'))
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
        cin >> dst;
        dst = toupper(dst);
        if (cin.good() != 1 || (dst < 'A' || dst > 'C'))
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else if (dst == src)
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
    while (1)
    {
       cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> delay;
        if (cin.good() != 1 || (delay < 0 || delay > 5))
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
        cout << "请输入是否显示内部数组值(0-不显示 1-显示)" << endl;
        cin >> show_plate;
        if (cin.good() != 1 || (show_plate < 0 || show_plate > 1))
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
    for (int i = 'A'; i <= 'C'; i++)
    {
        if (i == src || i == dst)
            continue;
        tmp = i;
    }
    if (src == 'A')
        for (int i = 0; i < n; i++)
            plateA[i] = n - i;
    else if (src == 'B')
        for (int i = 0; i < n; i++)
            plateB[i] = n - i;
    else
        for (int i = 0; i < n; i++)
            plateC[i] = n - i;
    cct_cls();
    cct_gotoxy(15, 25);
    if (show_plate == 1)
    {
        printf("初始:               ");
        printf(" A:");
        for (int j = 0; j < 10; j++)
        {
            if (plateA[j] != 0 || j < topA)
                printf("%2d", plateA[j]);
            else
                printf("  ");
        }
        printf(" B:");
        for (int j = 0; j < 10; j++)
        {
            if (plateB[j] != 0 || j < topB)
                printf("%2d", plateB[j]);
            else
                printf("  ");
        }
        printf(" C:");
        for (int j = 0; j < 10; j++)
        {
            if (plateC[j] != 0 || j < topC)
                printf("%2d", plateC[j]);
            else
                printf("  ");
        }
    }
    if (delay == 0)
        getchar();
    else
        Sleep(300 * (5 - delay));
    if (src == 'A')
        topA = n - 1;
    else if (src == 'B')
        topB = n - 1;
    else
        topC = n - 1;
    printf("\n");
    hanoi(n, src, tmp, dst);
    cct_gotoxy(0, 27);
    system("pause");
    return 0;
}