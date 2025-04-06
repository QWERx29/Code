#include <iostream>
using namespace std;
int main()
{
    double n;
    cout << "请输入找零值：" << endl;
    cin >> n;
    int a = n;
    double x = (n - a) * 100;
    int b = x;
    int r50 = 0, r20 = 0, r10 = 0, r5 = 0, r1 = 0;
    if (a >= 50)
        r50++, a -= 50;
    if (a >= 20)
    {
        if (a >= 40)
            r20 += 2, a -= 40;
        else
            r20++, a -= 20;
    }
    if (a >= 10)
        r10++, a -= 10;
    if (a >= 5)
        r5++, a -= 5;
    r1 = a;

    int c50 = 0, c10 = 0, c5 = 0, c2 = 0, c1 = 0;
    if (b >= 50)
        c50++, b -= 50;
    if (b >= 10)
        c10 += b / 10, b %= 10;
    if (b >= 5)
        c5++, b -= 5;
    if (b >= 2)
    {
        if (b >= 4)
            c2 += 2, b -= 4;
        else
            c2++, b -= 2;
    }
    c1 = b;
    int sum = 0;
    if (r50 != 0)
        sum++;
    if (r20 != 0)
        sum++;
    if (r10 != 0)
        sum++;
    if (r5 != 0)
        sum++;
    if (r1 != 0)
        sum++;
    if (c50 != 0)
        sum++;
    if (c10 != 0)
        sum++;
    if (c5 != 0)
        sum++;
    if (c2 != 0)
        sum++;
    if (r1 != 0)
        sum++;
    cout << "共" << sum << "张找零，具体如下：" << endl;

    if (r50 != 0)
        cout << "50元 : " << r50 << "张" << endl;
    if (r20 != 0)
        cout << "20元 : " << r20 << "张" << endl;
    if (r10 != 0)
        cout << "10元 : " << r10 << "张" << endl;
    if (r5 != 0)
        cout << "5元  : " << r5 << "张" << endl;
    if (r1 != 0)
        cout << "1元  : " << r1 << "张" << endl;
    if (c50 != 0)
        cout << "5角  : " << c50 << "张" << endl;
    if (c10 != 0)
        cout << "1角  : " << c10 << "张" << endl;
    if (c5 != 0)
        cout << "5分  : " << c5 << "张" << endl;
    if (c2 != 0)
        cout << "2分  : " << c2 << "张" << endl;
    if (r1 != 0)
        cout << "1分  : " << c1 << "张" << endl;
    return 0;
}