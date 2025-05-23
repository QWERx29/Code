#include <stdio.h>
#include <math.h>

const char chnstr[] = "零壹贰叁肆伍陆柒捌玖拾佰仟万亿圆角分整";
char result[256];

void addstr(int num, int cur)
{
    for (int i = num * 2; i <= num * 2 + 1; i++)
    {
        result[cur + i - num * 2] = chnstr[i];
    }
}

int daxie(int num, int flag_of_zero, int cur)
{
    switch (num)
    {
    case 0:
        if (flag_of_zero) // 此标记什么意思请自行思考
            addstr(0, cur);
        break;
    case 1:
        addstr(1, cur);
        break;
    case 2:
        addstr(2, cur);
        break;
    case 3:
        addstr(3, cur);
        break;
    case 4:
        addstr(4, cur);
        break;
    case 5:
        addstr(5, cur);
        break;
    case 6:
        addstr(6, cur);
        break;
    case 7:
        addstr(7, cur);
        break;
    case 8:
        addstr(8, cur);
        break;
    case 9:
        addstr(9, cur);
        break;
    default:
        printf("error");
        break;
    }
    return cur + 2;
}

int main()
{
    double n;
    printf("请输入[0-100亿)之间的数字:\n");
    scanf("%lf", &n);
    printf("大写结果是:\n");
    n = fabs(n);
    long long a = n;
    long double b = n - a;
    int _1, _2, _3, _4, _5, _6, _7, _8, _9, _0;
    int flag = 0, r = 0;
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
        r = daxie(_0, flag, r);
        if (_0 != 0)
            addstr(10, r), r += 2;
        // 100 million
        r = daxie(_9, flag, r);
        addstr(14, r), r += 2;
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
        r = daxie(_8, flag, r);
        flag = 0;
        if (_8 != 0)
            addstr(12, r), r += 2;
        if ((_7 == 0 && _6 != 0) || (_8 == 0 && _7 == 0 && _6 != 0))
        {
            if (_0 + _9 + _8 + _7 != 0)
                flag = 1;
        }
        r = daxie(_7, flag, r);
        flag = 0;
        if (_7 != 0)
            addstr(11, r), r += 2;
        if ((_6 == 0 && _5 != 0) || (_8 == 0 && _7 == 0 && _6 == 0 && _5 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 != 0)
                flag = 1;
        }
        r = daxie(_6, flag, r);
        flag = 0;
        if (_6 != 0)
            addstr(10, r), r += 2;
        r = daxie(_5, flag, r);
        addstr(13, r), r += 2;
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
        r = daxie(_4, flag, r);
        flag = 0;
        if (_4 != 0)
            addstr(12, r), r += 2;
        if ((_3 == 0 && _2 != 0) || (_4 == 0 && _3 == 0 && _2 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 != 0)
                flag = 1;
        }
        r = daxie(_3, flag, r);
        flag = 0;
        if (_3 != 0)
            addstr(11, r), r += 2;
        if ((_2 == 0 && _1 != 0) || (_4 == 0 && _3 == 0 && _2 == 0 && _1 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 + _2 != 0)
                flag = 1;
        }
        r = daxie(_2, flag, r);
        flag = 0;
        if (_2 != 0)
            addstr(10, r), r += 2;
        r = daxie(_1, flag, r);
        addstr(15, r), r += 2;
    }
    else
    {
        if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
            addstr(15, r), r += 2;
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
        r = daxie(__1, flag, r);
        flag = 0;
        if (__1 != 0)
            addstr(16, r), r += 2;
        if (__2 == 0)
            addstr(18, r), r += 2;
        else
        {
            r = daxie(__2, flag, r);
            addstr(17, r), r += 2;
        }
    }
    else if (n != 0)
        addstr(18, r), r += 2;
    else
    {
        r = daxie(0, 1, r);
        addstr(15, r), r += 2;
        addstr(18, r), r += 2;
    }
    printf("%s\n", result);
    return 0;
}