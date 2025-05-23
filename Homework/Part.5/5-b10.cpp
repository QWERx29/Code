#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

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

void canlendar(int y, int show)
{
    int w[13], cur_ym[13], y_date[13];
    int can[550] = {0};
    for (int i = 1; i <= 12; i++)
    {
        w[i] = zeller(y, i, 1);
        y_date[i] = calc_date(y, i);
    }
    // calculate month_date - line 1
    for (int i = 1; i <= 12; i++)
    {
        cur_ym[i] = 1;
        for (int j = (i - 1) * 7 + w[i] + 1; j <= 7 * i; j++)
            can[j] = cur_ym[i]++;
    }
    // line 2-4
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 7; j++)
            can[7 * (i + 11) + j] = cur_ym[i]++;
    }
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 7; j++)
            can[7 * (i + 23) + j] = cur_ym[i]++;
    }
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 7; j++)
            can[7 * (i + 35) + j] = cur_ym[i]++;
    }
    int line_max[13];
    for (int i = 1; i <= 12; i++)
        line_max[i] = 4;
    // line 5-6
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            if (cur_ym[i] > y_date[i])
                break;
            can[7 * (i + 47) + j] = cur_ym[i]++;
            line_max[i] = 5;
        }
    }
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            if (cur_ym[i] > y_date[i])
                break;
            can[7 * (i + 59) + j] = cur_ym[i]++;
            line_max[i] = 6;
        }
    }
    // print
    cout << y << "年的日历:" << endl;
    cout << endl;
    for (int u = 1; u <= 12 / show; u++)
    {
        for (int m = (u - 1) * show + 1; m <= u * show; m++)
        {
            cout << right << setw(13) << m;
            cout << "月";
            cout << setw(17) << " ";
        }
        cout << endl;
        for (int m = (u - 1) * show + 1; m <= u * show; m++)
            cout << "Sun Mon Tue Wed Thu Fri Sat     ";
        cout << endl;
        int curr = 1;
        for (int i = 1; i <= 6; i++)
        {
            for (int j = 1; j <= show * 7; j++)
            {
                curr = ((u - 1) * show) * 7 + (i - 1) * 84 + j;
                if (can[curr] != 0)
                    cout << left << setw(4) << can[curr];
                else
                    cout << setw(4) << " ";
                if (j % 7 == 0)
                    cout << "    ";
            }
            cout << endl;
        }
        for (int m = (u - 1) * show + 1; m <= u * show; m++)
        {
            if (line_max[m] == 6)
            {
                cout << endl;
                break;
            }
        }
    }
}
int main()
{
    int y, s;
    while (1)
    {
        cout << "请输入年份[1900-2100]" << endl;
        cin >> y;
        if (cin.good() != 1 || y < 1900 || y > 2100)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        else
            break;
    }
    while (1)
    {
        cout << "请输入每行打印的月份数[1/2/3/4/6/12]" << endl;
        cin >> s;
        if (cin.good() != 1 || (s != 1 && s != 2 && s != 3 && s != 4 && s != 6 && s != 12))
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        else
            break;
    }
    // for (int m = 1; m <= 12; m++)
    canlendar(y, s);
    cout << endl;
    return 0;
}
