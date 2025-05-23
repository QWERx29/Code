// 2451317 冯久恒 计算机 
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

int cmp(const char c1[], const char c2[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (c1[i] > c2[i])
            return 1;
        else if (c1[i] < c2[i])
            return -1;
        else
            continue;
    }
}

int main()
{
    char name[10][9], num[10][8];
    int pts[10];
    for (int i = 0; i < 10; i++)
    {
        printf("请输入第%d个人的学号、姓名、成绩\n", i + 1);
        scanf("%s%s%d", num[i], name[i], &pts[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            int t = 0;
            if (cmp(num[i], num[j], 8) == -1)
            {
                t = 1;
                char t1[9], t2[8];
                int t3;
                for (int u = 0; u < 9; u++)
                {
                    t1[u] = name[i][u], name[i][u] = name[j][u], name[j][u] = t1[u];
                }
                for (int u = 0; u < 8; u++)
                    t2[u] = num[i][u], num[i][u] = num[j][u], num[j][u] = t2[u];
                t3 = pts[i], pts[i] = pts[j], pts[j] = t3;
            }
        }
    }
    printf("\n及格名单(学号降序):\n");
    for (int i = 0; i < 10; i++)
        if (pts[i] > 60)
            printf("%s %s %d\n", name[i], num[i], pts[i]);
    return 0;
}
