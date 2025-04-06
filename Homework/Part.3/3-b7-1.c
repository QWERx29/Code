#include <stdio.h>
int main()
{
    double n;
    printf("请输入找零值：\n");
    scanf("%lf", &n);
    int a = n;
    double x = (n - a) * 100;
    int b = x;
    int r50 = 0, r20 = 0, r10 = 0, r5 = 0, r1 = 0;
    if (a >= 50)
        r50++, a -= 50;
    if (a >= 20)
    {
        if (a >= 40)
            r20 += 2, a -= 40;
        else
            r20++, a -= 20;
    }
    if (a >= 10)
        r10++, a -= 10;
    if (a >= 5)
        r5++, a -= 5;
    r1 = a;

    int c50 = 0, c10 = 0, c5 = 0, c2 = 0, c1 = 0;
    if (b >= 50)
        c50++, b -= 50;
    if (b >= 10)
        c10 += b / 10, b %= 10;
    if (b >= 5)
        c5++, b -= 5;
    if (b >= 2)
    {
        if (b >= 4)
            c2 += 2, b -= 4;
        else
            c2++, b -= 2;
    }
    c1 = b;
    int sum = 0;
    if (r50 != 0)
        sum++;
    if (r20 != 0)
        sum++;
    if (r10 != 0)
        sum++;
    if (r5 != 0)
        sum++;
    if (r1 != 0)
        sum++;
    if (c50 != 0)
        sum++;
    if (c10 != 0)
        sum++;
    if (c5 != 0)
        sum++;
    if (c2 != 0)
        sum++;
    if (r1 != 0)
        sum++;
    printf("共%d张找零，具体如下：\n", sum);

    if (r50 != 0)
        printf("50元 : %d张\n", r50);
    if (r20 != 0)
        printf("20元 : %d张\n", r20);
    if (r10 != 0)
        printf("10元 : %d张\n", r10);
    if (r5 != 0)
        printf("5元  : %d张\n", r5);
    if (r1 != 0)
        printf("1元  : %d张\n", r1);
    if (c50 != 0)
        printf("5角  : %d张\n", c50);
    if (c10 != 0)
        printf("1角  : %d张\n", c10);
    if (c5 != 0)
        printf("5分  : %d张\n", c5);
    if (c2 != 0)
        printf("2分  : %d张\n", c2);
    if (r1 != 0)
        printf("1分  : %d张\n", c1);
    return 0;
}