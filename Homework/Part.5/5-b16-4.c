// 2451317 冯久恒 计算机 
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

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
            if (pts[i] < pts[j])
            {
                char t1[9], t2[8];
                int t3;
                for (int u = 0; u < 9; u++)
                    t1[u] = name[i][u], name[i][u] = name[j][u], name[j][u] = t1[u];
                for (int u = 0; u < 8; u++)
                    t2[u] = num[i][u], num[i][u] = num[j][u], num[j][u] = t2[u];
                t3 = pts[i], pts[i] = pts[j], pts[j] = t3;
            }
        }
    }
    printf("\n全部学生(成绩降序):\n");
    for (int i = 0; i < 10; i++)
        printf("%s %s %d\n", name[i], num[i], pts[i]);
    return 0;
}
