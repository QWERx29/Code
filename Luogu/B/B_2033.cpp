#include <bits/stdc++.h>
using namespace std;
char a1[100086], b1[100086];
int a[100086], b[100086], c[100086], la, lb, lc, x;
int main()
{
    cin >> a1 >> b1;
    la = strlen(a1);
    lb = strlen(b1);
    for (int i = 0; i < la; i++)
        a[la - i] = a1[i] - '0';
    for (int i = 0; i < lb; i++)
        b[lb - i] = b1[i] - '0';
    for (int i = 1; i <= la; i++)
    {
        x = 0;
        for (int j = 1; j <= lb; j++)
        {
            c[i + j - 1] = a[i] * b[j] + x + c[i + j - 1];
            x = c[i + j - 1] / 10;
            c[i + j - 1] %= 10;
        }
        c[i + lb] = x;
    }
    lc = la + lb;
    while ((c[lc] == 0) && (lc > 1))
        lc--;
    for (int i = lc; i >= 1; i--)
        cout << c[i];
    return 0;
}
