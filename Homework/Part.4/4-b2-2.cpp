// 2451317 冯久恒 计算机
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
int calc_date(int y, int m)
{
    int dd;
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        dd = 31;
    else if (m != 2)
        dd = 30;
    else
    {
        if (y % 4 == 0 && y % 100 != 0)
        {
            dd = 29;
        }
        else
        {
            if (y % 400 == 0)
                dd = 29;
            else
                dd = 28;
        }
    }
    return dd;
}
int calc_week(int y, int m, int d)
{
    int c, yy, ww;
    if (m <= 2)
        m += 12, y--;
    c = y / 100, yy = y % 100;
    ww = yy + (yy / 4) + (c / 4) - (2 * c) + ((m + 1) * 13 / 5) + (d - 1);
    if (ww < 0)
        ww += 7;
    ww %= 7;
    return ww;
}
void output(int w)
{
    cout << "星期";
    switch (w)
    {
    case 0:
        cout << "日" << endl;
        break;
    case 1:
        cout << "一" << endl;
        break;
    case 2:
        cout << "二" << endl;
        break;
    case 3:
        cout << "三" << endl;
        break;
    case 4:
        cout << "四" << endl;
        break;
    case 5:
        cout << "五" << endl;
        break;
    case 6:
        cout << "六" << endl;
        break;
    }
}
int main()
{
    int y, m, d;
    while (1)
    {
        cout << "请输入年[1900-2100]、月、日：";
        cin >> y >> m >> d;
        if (cin.good() != 1)
        {
            cout << "输入非法，请重新输入" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (m < 1 || m > 12)
        {
            cout << "月份不正确，请重新输入" << endl;
            continue;
        }
        else if (y < 1900 || y > 2100)
        {
            cout << "年份不正确，请重新输入" << endl;
            continue;
        }
        else if (d > calc_date(y, m) || d < 0)
        {
            cout << "日不正确，请重新收入" << endl;
            continue;
        }
        else
            break;
    }
    int w = calc_week(y, m, d);
    cout << endl;
    output(w);

    return 0;
}