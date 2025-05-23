#include <iostream>
using namespace std;
int main()
{
    char ipt[33], *p;
    cout << "请输入一个0/1组成的字符串，长度不超过32" << endl;
    unsigned int n = 0, u = 1;
    cin >> ipt;
    for (p = ipt; *p != '\0'; p++)
    {
        if (*p == '1')
            n += u;
        u *= 2;
    }
    cout << n << endl;
    return 0;
}