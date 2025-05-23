#include <iostream>
using namespace std;
int str_len(char *s)
{
    char *i = s;
    while (*i != '\0')
        i++;
    return i - s;
}
int main()
{
    char str[81];
    cout << "请输入一个长度小于80的字符串（回文串）" << endl;
    fgets(str, 80, stdin);
    char *p, *q;
    int l = str_len(str) - 1;
    bool flag = true;
    for (p = str, q = str + l - 1; p < str + l; p++, q--)
    {
        if (*p != *q)
            flag = false;
    }
    if (flag == false)
        cout << "no" << endl;
    else
        cout << "yes" << endl;
    return 0;
}