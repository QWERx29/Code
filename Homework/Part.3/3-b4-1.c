#include <stdio.h>
#include <math.h>

const double pi = 3.14159;
int main()
{
    int a, b, x;
    scanf("%d%d%d", &a, &b, &x);
    float s = (0.5 * a * b * sin(pi * x / 180));
    printf("%.3f", s);
    return 0;
}