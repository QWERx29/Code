#include <stdio.h>
const double pi = 3.14159;
int main()
{
    double r, h;
    printf("请输入半径和高度\n");
    scanf("%lf%lf", &r, &h);
    double c, s1, s2, v1, v2;
    c = 2 * pi * r, s1 = pi * r * r, s2 = 4 * pi * r * r, v1 = 4.0 / 3 * pi * r * r * r, v2 = s1 * h;
    printf("圆周长     : %.2lf\n", c);
    printf("圆面积     : %.2lf\n", s1);
    printf("圆球表面积 : %.2lf\n", s2);
    printf("圆球体积   : %.2lf\n", v1);
    printf("圆柱体积   : %.2lf\n", v2);
    return 0;
}