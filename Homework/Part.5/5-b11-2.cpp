
#include <iostream>
#include <cmath>
using namespace std;

const char chnstr[] = "零壹贰叁肆伍陆柒捌玖拾佰仟万亿圆角分整";
string result;

void addstr(int num)
{
    result += chnstr[num * 2];
    result += chnstr[num * 2 + 1];
}

void daxie(int num, int flag_of_zero)
{
    switch (num)
    {
    case 0:
        if (flag_of_zero) // 此标记什么意思请自行思考
            addstr(0);
        break;
    case 1:
        addstr(1);
        break;
    case 2:
        addstr(2);
        break;
    case 3:
        addstr(3);
        break;
    case 4:
        addstr(4);
        break;
    case 5:
        addstr(5);
        break;
    case 6:
        addstr(6);
        break;
    case 7:
        addstr(7);
        break;
    case 8:
        addstr(8);
        break;
    case 9:
        addstr(9);
        break;
    default:
        cout << "error";
        break;
    }
}

int main()
{
    double n;
    cout << "请输入[0-100亿)之间的数字:" << endl;
    cin >> n;
    cout << "大写结果是:" << endl;
    n = fabs(n);
    long long a = n;
    long double b = n - a;
    int _1, _2, _3, _4, _5, _6, _7, _8, _9, _0;
    int flag = 0;
    _1 = a % 10, a /= 10;
    _2 = a % 10, a /= 10;
    _3 = a % 10, a /= 10;
    _4 = a % 10, a /= 10;
    _5 = a % 10, a /= 10;
    _6 = a % 10, a /= 10;
    _7 = a % 10, a /= 10;
    _8 = a % 10, a /= 10;
    _9 = a % 10, a /= 10;
    _0 = a % 10, a /= 10;

    if (_0 + _9 != 0)
    {
        // billion
        daxie(_0, flag);
        if (_0 != 0)
            addstr(10);
        // 100 million
        daxie(_9, flag);
        addstr(14);
    }

    if (_8 + _7 + _6 + _5 != 0)
    {
        flag = 0;
        // 10 million
        if (_8 == 0 && _7 != 0)
        {
            if (_0 + _9 + _8 != 0)
                flag = 1;
        }
        daxie(_8, flag);
        flag = 0;
        if (_8 != 0)
            addstr(12);
        if ((_7 == 0 && _6 != 0) || (_8 == 0 && _7 == 0 && _6 != 0))
        {
            if (_0 + _9 + _8 + _7 != 0)
                flag = 1;
        }
        daxie(_7, flag);
        flag = 0;
        if (_7 != 0)
            addstr(11);
        if ((_6 == 0 && _5 != 0) || (_8 == 0 && _7 == 0 && _6 == 0 && _5 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 != 0)
                flag = 1;
        }
        daxie(_6, flag);
        flag = 0;
        if (_6 != 0)
            addstr(10);
        daxie(_5, flag);
        addstr(13);
    }

    if (_4 + _3 + _2 + _1 != 0)
    {
        flag = 0;
        // 10 thousand
        if (_4 == 0 && _3 != 0)
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 != 0)
                flag = 1;
        }
        daxie(_4, flag);
        flag = 0;
        if (_4 != 0)
            addstr(12);
        if ((_3 == 0 && _2 != 0) || (_4 == 0 && _3 == 0 && _2 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 != 0)
                flag = 1;
        }
        daxie(_3, flag);
        flag = 0;
        if (_3 != 0)
            addstr(11);
        if ((_2 == 0 && _1 != 0) || (_4 == 0 && _3 == 0 && _2 == 0 && _1 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 + _2 != 0)
                flag = 1;
        }
        daxie(_2, flag);
        flag = 0;
        if (_2 != 0)
            addstr(10);
        daxie(_1, flag);
        addstr(15);
    }
    else
    {
        if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
            addstr(15);
    }

    b = round(b * 100);
    int x = (int)b, __1, __2;
    __1 = x / 10, __2 = x % 10;

    if (__1 + __2 != 0)
    {
        flag = 0;
        if (__1 == 0 && __2 != 0)
        {
            if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
                flag = 1;
        }
        daxie(__1, flag);
        flag = 0;
        if (__1 != 0)
            addstr(16);
        if (__2 == 0)
            addstr(18);
        else
        {
            daxie(__2, flag);
            addstr(17);
        }
    }
    else if (n != 0)
        addstr(18);
    else
    {
        daxie(0, 1);
        addstr(15);
        addstr(18);
    }
    cout << result << endl;
    return 0;
}
