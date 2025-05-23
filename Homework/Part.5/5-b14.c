#include <stdio.h>

int main()
{
    char ms[11][27], in[11][53];
    int cm = 0, x = 1;
    for (int i = 1; i <= 10; i++)
    {
        scanf("%52[^\n]", in[i]);
        int c;
        while ((c = getchar() != '\n') && c != EOF)
            ;
    }
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1, t = 0; j <= 26; t++)
        {
            if (in[i][t] != ' ')
            {
                ms[i][j] = in[i][t];
                j++;
            }
        }
    }
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 26; j++)
            if (ms[i][j] == '*')
                cm++;
    if (cm != 50)
    {
        printf("´íÎó1\n");
        return 0;
    }
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 26; j++)
        {
            if (ms[i][j] != '*')
            {
                int t = 0;
                for (int q = i - 1; q <= i + 1; q++)
                {
                    for (int w = j - 1; w <= j + 1; w++)
                    {
                        if (ms[q][w] == '*')
                            t++;
                    }
                }
                if (t != (ms[i][j] - '0'))
                {
                    printf("´íÎó2\n");
                    return 0;
                }
            }
        }
    }
    printf("ÕýÈ·\n");
    return 0;
}