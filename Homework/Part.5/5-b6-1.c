/* 学号 姓名 班级 */
#include <stdio.h>
int topA = -1, topB = -1, topC = -1, plateA[10], plateB[10], plateC[10], cnt = 1;
void output(int n, char src, char dst)
{

    printf("第%4d 步(%2d): ", cnt, n);
    printf("%c-->%c", src, dst);
    if (dst == 'A')
        topA++, plateA[topA] = n;
    else if (dst == 'B')
        topB++, plateB[topB] = n;
    else
        topC++, plateC[topC] = n;
    if (src == 'A')
        plateA[topA] = 0, topA--;
    else if (src == 'B')
        plateB[topB] = 0, topB--;
    else
        plateC[topC] = 0, topC--;
    printf(" A:");
    for (int j = 0; j < 10; j++)
    {
        if (plateA[j] != 0 && topA != -1)
            printf("%2d", plateA[j]);
        else
            printf("  ");
    }
    printf(" B:");
    for (int j = 0; j < 10; j++)
    {
        if (plateB[j] != 0 && topB != -1)
            printf("%2d", plateB[j]);
        else
            printf("  ");
    }
    printf(" C:");
    for (int j = 0; j < 10; j++)
    {
        if (plateC[j] != 0 && topC != -1)
            printf("%2d", plateC[j]);
        else
            printf("  ");
    }
    cnt++;
    printf("\n");
}
void hanoi(int n, char src, char tmp, char dst) // n-层数;src-起始柱;tmp-中间柱;dst-目标柱
{

    if (n == 1)
    {
        output(n, src, dst);
        return;
    }
    hanoi(n - 1, src, dst, tmp);
    output(n, src, dst);
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
        printf("请输入汉诺塔的层数(1-10)\n");
        ret = scanf("%d", &n);
        if (ret != 1 || (n < 1 || n > 10))
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
    if (src == 'A')
        for (int i = 0; i < n; i++)
            plateA[i] = n - i;
    else if (src == 'B')
        for (int i = 0; i < n; i++)
            plateB[i] = n - i;
    else
        for (int i = 0; i < n; i++)
            plateC[i] = n - i;
    printf("初始:               ");
    printf(" A:");
    for (int j = 0; j < 10; j++)
    {
        if (plateA[j] != 0 || j < topA)
            printf("%2d", plateA[j]);
        else
            printf("  ");
    }
    printf(" B:");
    for (int j = 0; j < 10; j++)
    {
        if (plateB[j] != 0 || j < topB)
            printf("%2d", plateB[j]);
        else
            printf("  ");
    }
    printf(" C:");
    for (int j = 0; j < 10; j++)
    {
        if (plateC[j] != 0 || j < topC)
            printf("%2d", plateC[j]);
        else
            printf("  ");
    }
    if (src == 'A')
        topA = n - 1;
    else if (src == 'B')
        topB = n - 1;
    else
        topC = n - 1;
    printf("\n");
    hanoi(n, src, tmp, dst);
    return 0;
}
