#include <stdio.h>
#include <limits.h>
int main()
{
    int t[1010], x, n = 0, f = 1;
    printf("请输入成绩（最多1000个），负数结束输入\n");
    while (1)
    {
        int ret;
        n++;
        ret = scanf("%d", &t[n]);
        if (t[n] < 0 || n > 1000)
        {
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
            break;
        }
    }
    printf("输入的数组为:\n");
    for (int i = 1; i < n; i++)
    {
        printf("%d ", t[i]);
        if (i % 10 == 0)
            printf("\n");
    }
    printf("\n分数与人数的对应关系为:\n");
    int cnt[105] = {0};
    for (int i = 1; i <= n; i++)
        cnt[t[i]]++;
    for (int i = 100; i >= 0; i--)
    {
        if (cnt[i] != 0)
            printf("%d %d\n", i, cnt[i]);
    }
    return 0;
}