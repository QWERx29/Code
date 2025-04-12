
#include <iostream>
#include <cmath>
using namespace std;

void daxie(int num, int flag_of_zero)
{
    switch (num)
    {
    case 0:
        if (flag_of_zero) // 此标记什么意思请自行思考
            cout << "零";
        break;
    case 1:
        cout << "壹";
        break;
    case 2:
        cout << "贰";
        break;
    case 3:
        cout << "叁";
        break;
    case 4:
        cout << "肆";
        break;
    case 5:
        cout << "伍";
        break;
    case 6:
        cout << "陆";
        break;
    case 7:
        cout << "柒";
        break;
    case 8:
        cout << "捌";
        break;
    case 9:
        cout << "玖";
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
    int flag;
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
            cout << "拾";
        // 100 million
        daxie(_9, flag);
        cout << "亿";
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
            cout << "仟";
        if ((_7 == 0 && _6 != 0) || (_8 == 0 && _7 == 0 && _6 != 0))
        {
            if (_0 + _9 + _8 + _7 != 0)
                flag = 1;
        }
        daxie(_7, flag);
        flag = 0;
        if (_7 != 0)
            cout << "佰";
        if ((_6 == 0 && _5 != 0) || (_8 == 0 && _7 == 0 && _6 == 0 && _5 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 != 0)
                flag = 1;
        }
        daxie(_6, flag);
        flag = 0;
        if (_6 != 0)
            cout << "拾";
        daxie(_5, flag);
        cout << "万";
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
            cout << "仟";
        if ((_3 == 0 && _2 != 0) || (_4 == 0 && _3 == 0 && _2 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 != 0)
                flag = 1;
        }
        daxie(_3, flag);
        flag = 0;
        if (_3 != 0)
            cout << "佰";
        if ((_2 == 0 && _1 != 0) || (_4 == 0 && _3 == 0 && _2 == 0 && _1 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 + _2 != 0)
                flag = 1;
        }
        daxie(_2, flag);
        flag = 0;
        if (_2 != 0)
            cout << "拾";
        daxie(_1, flag);
        cout << "圆";
    }
    else
    {
        if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
            cout << "圆";
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
            cout << "角";

        if (__2 == 0)
            cout << "整";
        else
        {
            daxie(__2, flag);
            cout << "分";
        }
    }
    else if (n != 0)
        cout << "整";
    else
    {
        daxie(0, 1);
        cout << "圆整";
    }
    cout << endl;

    return 0;
}
