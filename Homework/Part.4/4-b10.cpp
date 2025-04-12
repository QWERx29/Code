/* 学号 班级 姓名 */
#include <iostream>
using namespace std;

int is_power(int num, int base)
{
    if (num % base != 0)
        return 0;
    else if (num / base != 1)
        return is_power(num / base, base);
    else
        return 1;
}

int main()
{
    int num, base;
    cout << "请输入整数num及基数base" << endl;
    cin >> num >> base;
    if (num == 1)
    {
        cout << num << "是" << base << "的幂" << endl;
    }
    else
    {
        if (is_power(num, base))
            cout << num << "是" << base << "的幂" << endl;
        else
            cout << num << "不是" << base << "的幂" << endl;
    }

    return 0;
}