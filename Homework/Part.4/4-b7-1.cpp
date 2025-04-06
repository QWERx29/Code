/* 学号 姓名 班级 */
#include <iostream>
using namespace std;

void convert(int n)
{
    if (n == 0)
    {
        cout << '0';
        return;
    }
    if (n / 10 == 0)
    {
        if (n < 0)
            cout << "- " << char(abs(n % 10) + '0');
        else
            cout << char(n + '0');
    }
    else
    {
        convert(n / 10);
        cout << ' ' << char(abs(n % 10) + '0');
    }
}

int main()
{
    int n;
    cout << "请输入一个整数" << endl;
    cin >> n; // 不考虑输入错误
    convert(n);
    cout << endl;
    return 0;
}