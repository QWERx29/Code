#include <iostream>
#include <limits>
using namespace std;
int max(int a, int b)
{
    return a > b ? a : b;
}
int max(int a, int b, int c)
{
    int t = a > b ? a : b;
    return t > c ? t : c;
}
int max(int a, int b, int c, int d)
{
    int t = a > b ? a : b;
    int u = t > c ? t : c;
    return u > d ? u : d;
}
int main()
{
    int n, a, b, c, d;
    {
        while (1)
        {
            cout << "请输入个数num及num个正整数：" << endl;
            cin >> n;
            if (n < 2 || n > 4)
            {
                cout << "个数输入错误" << endl;
                return 0;
            }
            else if (cin.good() != 1)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                while (1)
                {
                    if (n == 2)
                        cin >> a >> b;
                    else if (n == 3)
                        cin >> a >> b >> c;
                    else
                        cin >> a >> b >> c >> d;
                    if (cin.good() != 1)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "请输入个数num及num个正整数：" << endl;
                        cin >> n;
                        if (n < 2 || n > 4)
                        {
                            cout << "个数输入错误" << endl;
                            return 0;
                        }
                        else if (cin.good() != 1)
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    else
                        break;
                }
                break;
            }
        }
    }
    if (n == 2)
        cout << "max=" << max(a, b) << endl;
    else if (n == 3)
        cout << "max=" << max(a, b, c) << endl;
    else
        cout << "max=" << max(a, b, c, d) << endl;
    return 0;
}