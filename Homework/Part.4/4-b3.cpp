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
int zeller(int y, int m, int d)
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

void canlendar(int y,int m)
{
	int w = zeller(y, m, 1);
	cout << y << "年" << m << "月" << endl;
    cout << "======================================================" << endl;
    cout << "星期日  星期一  星期二  星期三  星期四  星期五  星期六" << endl;
    cout << "======================================================" << endl;
    // calculate month_date
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
    int t = 1;
    for (int i = 1; i <= 8 * w; i++)
        cout << " ";
    for (int i = w; i <= 6; i++, t++)
        cout << setw(4) << t << "    ";
    cout << endl;
    while (t <= dd)
    {
        for (int i = 0; i <= 6 && t <= dd; i++, t++)
            cout << setw(4) << t << "    ";
        cout << endl;
    }
    cout << "======================================================" << endl;
}
int main()
{
    int y, m;
    while (1)
    {
        cout << "请输入年[1900-2100]、月";
        cin >> y >> m;
        if (cin.good() != 1)
        {
            cout << "输入非法，请重新输入" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (m < 1 || m > 12 || y < 1900 || y > 2100)
        {
            cout << "输入非法，请重新输入" << endl;
            continue;
        }
        else
            break;
    }
    
    cout << endl;
    cout << endl;
    canlendar(y,m);
    return 0;
}
