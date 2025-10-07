#include <stdio.h>
#include <math.h>

double definite_integration(double (*func)(double), double low, double high, int n)
{
    double dx = (high - low) / n;
    double sum = 0.0;
    int i;
    for (i = 1; i <= n; i++)
        sum += func(low + i * dx);
    return sum * dx;
}

int main()
{
    int n;
    double low, high, value;
    printf("请输入sinxdx的下限、上限及区间划分数量\n");
    scanf("%lf %lf %d", &low, &high, &n);
    value = definite_integration(sin, low, high, n);
    printf("sinxdx[%g~%g/n=%d] : %g\n", low, high, n, value);

    printf("请输入cosxdx的下限、上限及区间划分数量\n");
    scanf("%lf %lf %d", &low, &high, &n);
    value = definite_integration(cos, low, high, n);
    printf("cosxdx[%g~%g/n=%d] : %g\n", low, high, n, value);

    printf("请输入e^xdx的下限、上限及区间划分数量\n");
    scanf("%lf %lf %d", &low, &high, &n);
    value = definite_integration(exp, low, high, n);
    printf("e^xdx[%g~%g/n=%d] : %g\n", low, high, n, value);

    return 0;
}