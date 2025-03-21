#include <stdio.h>
int n, a, b, c, d, e;
int main()
{
    scanf("%d", &n);
    a = n / 10000;
    b = n / 1000 % 10;
    c = n / 100 % 10;
    d = n / 10 % 10;
    e = n % 10000 % 10;
    printf("万位 : %d\n", a);
    printf("千位 : %d\n", b);
    printf("百位 : %d\n", c);
    printf("十位 : %d\n", d);
    printf("个位 : %d\n", e);
    return 0;
}