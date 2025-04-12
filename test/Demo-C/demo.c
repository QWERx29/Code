// 2451317 冯久恒 计算机 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int cnt = 0;

void hanoi(int n, char src, char tmp, char dst) // n-层数;src-起始柱;tmp-中间柱;dst-目标柱
{
    if (n == 1)
    {
        cnt++;
        printf("%5d: ", cnt);
        printf("%2d# %c-->%c\n", n, src, dst);
        return;
    }
    hanoi(n - 1, src, dst, tmp);
    cnt++;
    printf("%5d: ", cnt);
    printf("%2d# %c-->%c\n", n, src, dst);
    hanoi(n - 1, tmp, src, dst);
}

int main()
{
    int n;
    char src, dst, tmp;
    // Input n
    while (1)
    {
        int ret;
        printf("请输入汉诺塔的层数(1-16)\n");
        ret = scanf("%d", &n);
        if (ret != 1 || (n < 1 || n > 16))
        {
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
        }
        else
        {
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
            break;
        }
    }
    // Input Source & Destination
    while (1)
    {
        int ret;
        printf("请输入起始柱(A-C)\n");
        ret = scanf("%c", &src);
        if (src >= 'a' && src <= 'z')
            src -= ('a' - 'A');
        if (ret != 1 || (src < 'A' || src > 'C'))
        {
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
        }
        else
        {
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
            break;
        }
    }
    while (1)
    {
        int ret;
        printf("请输入目标柱(A-C)\n");
        ret = scanf("%c", &dst);
        if (dst >= 'a' && dst <= 'z')
            dst -= ('a' - 'A');
        if (ret != 1 || (dst < 'A' || dst > 'C'))
        {
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
        }
        else if (dst == src)
        {
            printf("目标柱(%c)不能与起始柱(%c)相同", src, dst);
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
        }
        else
        {
            int c;
            while ((c = getchar() != '\n') && c != EOF)
                ;
            break;
        }
    }
    for (int i = 'A'; i <= 'C'; i++)
    {
        if (i == src || i == dst)
            continue;
        tmp = i;
    }
    printf("移动步骤为:\n");
    hanoi(n, src, tmp, dst);
    return 0;
}