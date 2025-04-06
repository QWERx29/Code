#include <stdio.h>
#include <math.h>
int main()
{
    double n;
    printf("ÇëÊäÈë[0-100 ÒÚ)Ö®¼äµÄÊý×Ö:\n");
    scanf("%lf", &n);
    printf("´óÐ´½á¹ûÊÇ:\n");
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
            printf("Ò¼Ê°");
            break;
        case 2:
            printf("·¡Ê°");
            break;
        case 3:
            printf("ÈþÊ°");
            break;
        case 4:
            printf("ËÁÊ°");
            break;
        case 5:
            printf("ÎéÊ°");
            break;
        case 6:
            printf("Â½Ê°");
            break;
        case 7:
            printf("ÆâÊ°");
            break;
        case 8:
            printf("°ÆÊ°");
            break;
        case 9:
            printf("¾ÁÊ°");
            break;
        }
        // 100 million
        switch (_9)
        {
        case 0:
            printf("ÒÚ");
            break;
        case 1:
            printf("Ò¼ÒÚ");
            break;
        case 2:
            printf("·¡ÒÚ");
            break;
        case 3:
            printf("ÈþÒÚ");
            break;
        case 4:
            printf("ËÁÒÚ");
            break;
        case 5:
            printf("ÎéÒÚ");
            break;
        case 6:
            printf("Â½ÒÚ");
            break;
        case 7:
            printf("ÆâÒÚ");
            break;
        case 8:
            printf("°ÆÒÚ");
            break;
        case 9:
            printf("¾ÁÒÚ");
            break;
        }
    }
    if (_8 + _7 + _6 + _5 != 0)
    {
        // 10 million
        if (_8 == 0 && _7 != 0)
        {
            if (_0 + _9 + _8 != 0)
                printf("Áã");
        }
        switch (_8)
        {
        case 0:
            break;
        case 1:
            printf("Ò¼Çª");
            break;
        case 2:
            printf("·¡Çª");
            break;
        case 3:
            printf("ÈþÇª");
            break;
        case 4:
            printf("ËÁÇª");
            break;
        case 5:
            printf("ÎéÇª");
            break;
        case 6:
            printf("Â½Çª");
            break;
        case 7:
            printf("ÆâÇª");
            break;
        case 8:
            printf("°ÆÇª");
            break;
        case 9:
            printf("¾ÁÇª");
            break;
        }
        if ((_7 == 0 && _6 != 0) || (_8 == 0 && _7 == 0 && _6 != 0))
        {
            if (_0 + _9 + _8 + _7 != 0)
                printf("Áã");
        }
        switch (_7)
        {
        case 0:
            break;
        case 1:
            printf("Ò¼°Û");
            break;
        case 2:
            printf("·¡°Û");
            break;
        case 3:
            printf("Èþ°Û");
            break;
        case 4:
            printf("ËÁ°Û");
            break;
        case 5:
            printf("Îé°Û");
            break;
        case 6:
            printf("Â½°Û");
            break;
        case 7:
            printf("Æâ°Û");
            break;
        case 8:
            printf("°Æ°Û");
            break;
        case 9:
            printf("¾Á°Û");
            break;
        }
        if ((_6 == 0 && _5 != 0) || (_8 == 0 && _7 == 0 && _6 == 0 && _5 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 != 0)
                printf("Áã");
        }
        switch (_6)
        {
        case 0:
            break;
        case 1:
            printf("Ò¼Ê°");
            break;
        case 2:
            printf("·¡Ê°");
            break;
        case 3:
            printf("ÈþÊ°");
            break;
        case 4:
            printf("ËÁÊ°");
            break;
        case 5:
            printf("ÎéÊ°");
            break;
        case 6:
            printf("Â½Ê°");
            break;
        case 7:
            printf("ÆâÊ°");
            break;
        case 8:
            printf("°ÆÊ°");
            break;
        case 9:
            printf("¾ÁÊ°");
            break;
        }
        switch (_5)
        {
        case 0:
            printf("Íò");
            break;
        case 1:
            printf("Ò¼Íò");
            break;
        case 2:
            printf("·¡Íò");
            break;
        case 3:
            printf("ÈþÍò");
            break;
        case 4:
            printf("ËÁÍò");
            break;
        case 5:
            printf("ÎéÍò");
            break;
        case 6:
            printf("Â½Íò");
            break;
        case 7:
            printf("ÆâÍò");
            break;
        case 8:
            printf("°ÆÍò");
            break;
        case 9:
            printf("¾ÁÍò");
            break;
        }
    }
    if (_4 + _3 + _2 + _1 != 0)
    {
        // 10 thousand
        if (_4 == 0 && _3 != 0)
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 != 0)
                printf("Áã");
        }
        switch (_4)
        {
        case 0:
            break;
        case 1:
            printf("Ò¼Çª");
            break;
        case 2:
            printf("·¡Çª");
            break;
        case 3:
            printf("ÈþÇª");
            break;
        case 4:
            printf("ËÁÇª");
            break;
        case 5:
            printf("ÎéÇª");
            break;
        case 6:
            printf("Â½Çª");
            break;
        case 7:
            printf("ÆâÇª");
            break;
        case 8:
            printf("°ÆÇª");
            break;
        case 9:
            printf("¾ÁÇª");
            break;
        }
        if ((_3 == 0 && _2 != 0) || (_4 == 0 && _3 == 0 && _2 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 != 0)
                printf("Áã");
        }
        switch (_3)
        {
        case 0:
            break;
        case 1:
            printf("Ò¼°Û");
            break;
        case 2:
            printf("·¡°Û");
            break;
        case 3:
            printf("Èþ°Û");
            break;
        case 4:
            printf("ËÁ°Û");
            break;
        case 5:
            printf("Îé°Û");
            break;
        case 6:
            printf("Â½°Û");
            break;
        case 7:
            printf("Æâ°Û");
            break;
        case 8:
            printf("°Æ°Û");
            break;
        case 9:
            printf("¾Á°Û");
            break;
        }
        if ((_2 == 0 && _1 != 0) || (_4 == 0 && _3 == 0 && _2 == 0 && _1 != 0))
        {
            if (_0 + _9 + _8 + _7 + _6 + _5 + _4 + _3 + _2 != 0)
                printf("Áã");
        }
        switch (_2)
        {
        case 0:
            break;
        case 1:
            printf("Ò¼Ê°");
            break;
        case 2:
            printf("·¡Ê°");
            break;
        case 3:
            printf("ÈþÊ°");
            break;
        case 4:
            printf("ËÁÊ°");
            break;
        case 5:
            printf("ÎéÊ°");
            break;
        case 6:
            printf("Â½Ê°");
            break;
        case 7:
            printf("ÆâÊ°");
            break;
        case 8:
            printf("°ÆÊ°");
            break;
        case 9:
            printf("¾ÁÊ°");
            break;
        }
        switch (_1)
        {
        case 0:
            printf("Ô²");
            break;
        case 1:
            printf("Ò¼Ô²");
            break;
        case 2:
            printf("·¡Ô²");
            break;
        case 3:
            printf("ÈþÔ²");
            break;
        case 4:
            printf("ËÁÔ²");
            break;
        case 5:
            printf("ÎéÔ²");
            break;
        case 6:
            printf("Â½Ô²");
            break;
        case 7:
            printf("ÆâÔ²");
            break;
        case 8:
            printf("°ÆÔ²");
            break;
        case 9:
            printf("¾ÁÔ²");
            break;
        }
    }
    else
    {
        if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
            printf("Ô²");
    }

    b = round(b * 100);
    int x = (int)b, __1, __2;
    __1 = x / 10, __2 = x % 10;

    if (__1 + __2 != 0)
    {
        if (__1 == 0 && __2 != 0)
        {
            if (_0 + _1 + _2 + _3 + _4 + _5 + _6 + _7 + _8 + _9 != 0)
                printf("Áã");
        }

        switch (__1)
        {
        case 0:
            break;
        case 1:
            printf("Ò¼½Ç");
            break;
        case 2:
            printf("·¡½Ç");
            break;
        case 3:
            printf("Èþ½Ç");
            break;
        case 4:
            printf("ËÁ½Ç");
            break;
        case 5:
            printf("Îé½Ç");
            break;
        case 6:
            printf("Â½½Ç");
            break;
        case 7:
            printf("Æâ½Ç");
            break;
        case 8:
            printf("°Æ½Ç");
            break;
        case 9:
            printf("¾Á½Ç");
            break;
        }

        switch (__2)
        {
        case 0:
            printf("Õû");
            break;
        case 1:
            printf("Ò¼·Ö");
            break;
        case 2:
            printf("·¡·Ö");
            break;
        case 3:
            printf("Èþ·Ö");
            break;
        case 4:
            printf("ËÁ·Ö");
            break;
        case 5:
            printf("Îé·Ö");
            break;
        case 6:
            printf("Â½·Ö");
            break;
        case 7:
            printf("Æâ·Ö");
            break;
        case 8:
            printf("°Æ·Ö");
            break;
        case 9:
            printf("¾Á·Ö");
            break;
        }
    }
    else if (n != 0)
        printf("Õû");
    else
        printf("ÁãÔ²Õû");
    printf("\n");
    return 0;
}