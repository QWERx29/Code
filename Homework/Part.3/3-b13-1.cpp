#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int y, m, w;
    // input year and month
    while (1)
    {
        cout << "请输入年份(2000-2030)和月份(1-12) : ";
        cin >> y >> m;
        if (cin.good() != 1)
        {
            cout << "输入非法，请重新输入" << endl;
            cin.clear();
            cin.ignore(10086, '\n');
        }
        else if (m < 1 || m > 12 || y < 2000 || y > 2030)
        {
            cout << "输入非法，请重新输入" << endl;
            continue;
        }
        else
            break;
    }
    // input week no.
    while (1)
    {
        cout << "请输入" << y << "年" << m << "月1日的星期(0-6表示星期日-星期六) : ";
        cin >> w;
        if (cin.good() != 1)
        {
            cout << "输入非法，请重新输入\n";
            cin.clear();
            cin.ignore(96110, '\n');
        }
        else if (w < 0 || w > 6)
        {
            cout << "输入非法，请重新输入" << endl;
            continue;
        }
        else
            break;
    }
    cout << endl
         << y << "年" << m << "月的月历为:" << endl;
    cout << "星期日  星期一  星期二  星期三  星期四  星期五  星期六" << endl;
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

    // cout << dd << endl;
    // cout << y << " " << m << " " << w;
}