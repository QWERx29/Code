#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double n;
    cout << "ÇëÊäÈë[0-100ÒÚ)Ö®¼äµÄÊý×Ö:" << endl;
    cin >> n;
    cout << "´óÐ´½á¹ûÊÇ:" << endl;
    n = fabs(n);
    long long a = n;
    long double b = n - a;
    long long _1, _2, _3, _4, _5, _6, _7, _8, _9, _0;
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
        switch (_0)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼Ê°";
            break;
        case 2:
            cout << "·¡Ê°";
            break;
        case 3:
            cout << "ÈþÊ°";
            break;
        case 4:
            cout << "ËÁÊ°";
            break;
        case 5:
            cout << "ÎéÊ°";
            break;
        case 6:
            cout << "Â½Ê°";
            break;
        case 7:
            cout << "ÆâÊ°";
            break;
        case 8:
            cout << "°ÆÊ°";
            break;
        case 9:
            cout << "¾ÁÊ°";
            break;
        }
        // 100 million
        switch (_9)
        {
        case 0:
            cout << "ÒÚ";
            break;
        case 1:
            cout << "Ò¼ÒÚ";
            break;
        case 2:
            cout << "·¡ÒÚ";
            break;
        case 3:
            cout << "ÈþÒÚ";
            break;
        case 4:
            cout << "ËÁÒÚ";
            break;
        case 5:
            cout << "ÎéÒÚ";
            break;
        case 6:
            cout << "Â½ÒÚ";
            break;
        case 7:
            cout << "ÆâÒÚ";
            break;
        case 8:
            cout << "°ÆÒÚ";
            break;
        case 9:
            cout << "¾ÁÒÚ";
            break;
        }
    }
    if (_8 + _7 + _6 + _5 != 0)
    {
        // 10 million
        if (_8 == 0 && _7 != 0)
        {
            if (_0 + _9 + _8 != 0)
                cout << "Áã";
        }
        switch (_8)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼Çª";
            break;
        case 2:
            cout << "·¡Çª";
            break;
        case 3:
            cout << "ÈþÇª";
            break;
        case 4:
            cout << "ËÁÇª";
            break;
        case 5:
            cout << "ÎéÇª";
            break;
        case 6:
            cout << "Â½Çª";
            break;
        case 7:
            cout << "ÆâÇª";
            break;
        case 8:
            cout << "°ÆÇª";
            break;
        case 9:
            cout << "¾ÁÇª";
            break;
        }
        if ((_7 == 0 && _6 != 0) || (_8 == 0 && _7 == 0 && _6 != 0))
        {
            if (_0 + _9 + _8 + _7 != 0)
                cout << "Áã";
        }
        switch (_7)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼°Û";
            break;
        case 2:
            cout << "·¡°Û";
            break;
        case 3:
            cout << "Èþ°Û";
            break;
        case 4:
            cout << "ËÁ°Û";
            break;
        case 5:
            cout << "Îé°Û";
            break;
        case 6:
            cout << "Â½°Û";
            break;
        case 7:
            cout << "Æâ°Û";
            break;
        case 8:
            cout << "°Æ°Û";
            break;
        case 9:
            cout << "¾Á°Û";
            break;
        }
        if ((_6 == 0 && _5 != 0) || (_8 == 0 && _7 == 0 && _6 == 0 && _5 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 != 0)
                cout << "Áã";
        }
        switch (_6)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼Ê°";
            break;
        case 2:
            cout << "·¡Ê°";
            break;
        case 3:
            cout << "ÈþÊ°";
            break;
        case 4:
            cout << "ËÁÊ°";
            break;
        case 5:
            cout << "ÎéÊ°";
            break;
        case 6:
            cout << "Â½Ê°";
            break;
        case 7:
            cout << "ÆâÊ°";
            break;
        case 8:
            cout << "°ÆÊ°";
            break;
        case 9:
            cout << "¾ÁÊ°";
            break;
        }
        switch (_5)
        {
        case 0:
            cout << "Íò";
            break;
        case 1:
            cout << "Ò¼Íò";
            break;
        case 2:
            cout << "·¡Íò";
            break;
        case 3:
            cout << "ÈþÍò";
            break;
        case 4:
            cout << "ËÁÍò";
            break;
        case 5:
            cout << "ÎéÍò";
            break;
        case 6:
            cout << "Â½Íò";
            break;
        case 7:
            cout << "ÆâÍò";
            break;
        case 8:
            cout << "°ÆÍò";
            break;
        case 9:
            cout << "¾ÁÍò";
            break;
        }
    }
    if (_4 + _3 + _2 + _1 != 0)
    {
        // 10 thousand
        if (_4 == 0 && _3 != 0)
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 != 0)
                cout << "Áã";
        }
        switch (_4)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼Çª";
            break;
        case 2:
            cout << "·¡Çª";
            break;
        case 3:
            cout << "ÈþÇª";
            break;
        case 4:
            cout << "ËÁÇª";
            break;
        case 5:
            cout << "ÎéÇª";
            break;
        case 6:
            cout << "Â½Çª";
            break;
        case 7:
            cout << "ÆâÇª";
            break;
        case 8:
            cout << "°ÆÇª";
            break;
        case 9:
            cout << "¾ÁÇª";
            break;
        }
        if ((_3 == 0 && _2 != 0) || (_4 == 0 && _3 == 0 && _2 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 != 0)
                cout << "Áã";
        }
        switch (_3)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼°Û";
            break;
        case 2:
            cout << "·¡°Û";
            break;
        case 3:
            cout << "Èþ°Û";
            break;
        case 4:
            cout << "ËÁ°Û";
            break;
        case 5:
            cout << "Îé°Û";
            break;
        case 6:
            cout << "Â½°Û";
            break;
        case 7:
            cout << "Æâ°Û";
            break;
        case 8:
            cout << "°Æ°Û";
            break;
        case 9:
            cout << "¾Á°Û";
            break;
        }
        if ((_2 == 0 && _1 != 0) || (_4 == 0 && _3 == 0 && _2 == 0 && _1 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 + _2 != 0)
                cout << "Áã";
        }
        switch (_2)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼Ê°";
            break;
        case 2:
            cout << "·¡Ê°";
            break;
        case 3:
            cout << "ÈþÊ°";
            break;
        case 4:
            cout << "ËÁÊ°";
            break;
        case 5:
            cout << "ÎéÊ°";
            break;
        case 6:
            cout << "Â½Ê°";
            break;
        case 7:
            cout << "ÆâÊ°";
            break;
        case 8:
            cout << "°ÆÊ°";
            break;
        case 9:
            cout << "¾ÁÊ°";
            break;
        }
        switch (_1)
        {
        case 0:
            cout << "Ô²";
            break;
        case 1:
            cout << "Ò¼Ô²";
            break;
        case 2:
            cout << "·¡Ô²";
            break;
        case 3:
            cout << "ÈþÔ²";
            break;
        case 4:
            cout << "ËÁÔ²";
            break;
        case 5:
            cout << "ÎéÔ²";
            break;
        case 6:
            cout << "Â½Ô²";
            break;
        case 7:
            cout << "ÆâÔ²";
            break;
        case 8:
            cout << "°ÆÔ²";
            break;
        case 9:
            cout << "¾ÁÔ²";
            break;
        }
    }
    else
    {
        if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
            cout << "Ô²";
    }

    b = round(b * 100);
    int x = (int)b, __1, __2;
    __1 = x / 10, __2 = x % 10;

    if (__1 + __2 != 0)
    {
        if (__1 == 0 && __2 != 0)
        {
            if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
                cout << "Áã";
        }

        switch (__1)
        {
        case 0:
            break;
        case 1:
            cout << "Ò¼½Ç";
            break;
        case 2:
            cout << "·¡½Ç";
            break;
        case 3:
            cout << "Èþ½Ç";
            break;
        case 4:
            cout << "ËÁ½Ç";
            break;
        case 5:
            cout << "Îé½Ç";
            break;
        case 6:
            cout << "Â½½Ç";
            break;
        case 7:
            cout << "Æâ½Ç";
            break;
        case 8:
            cout << "°Æ½Ç";
            break;
        case 9:
            cout << "¾Á½Ç";
            break;
        }

        switch (__2)
        {
        case 0:
            cout << "Õû";
            break;
        case 1:
            cout << "Ò¼·Ö";
            break;
        case 2:
            cout << "·¡·Ö";
            break;
        case 3:
            cout << "Èþ·Ö";
            break;
        case 4:
            cout << "ËÁ·Ö";
            break;
        case 5:
            cout << "Îé·Ö";
            break;
        case 6:
            cout << "Â½·Ö";
            break;
        case 7:
            cout << "Æâ·Ö";
            break;
        case 8:
            cout << "°Æ·Ö";
            break;
        case 9:
            cout << "¾Á·Ö";
            break;
        }
    }
    else if (n != 0)
        cout << "Õû";
    else
        cout << "ÁãÔ²Õû";
    cout << endl;
    return 0;
}