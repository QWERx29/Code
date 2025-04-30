#include <iostream>
#include <limits>
using namespace std;
int main()
{
    int t[25], x, n = 0, f = 1;
    cout << "请输入任意个正整数（升序，最多20个），0或负数结束输入" << endl;
    while (1)
    {
        n++;
        cin >> t[n];

        if (t[n] <= 0 || n > 20)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (t[1] <= 0)
            {
                cout << "无有效输入" << endl;
                return 0;
            }
            break;
        }
    }
    cout << "原数组为：" << endl;
    for (int i = 1; i < n; i++)
        cout << t[i] << " ";
    cout << endl;
    cout << "请输入要插入的正整数" << endl;
    cin >> x;
    cout << "插入后的数组为：" << endl;
    for (int i = 1; i < n; i++)
    {
        if (x <= t[i] && f == 1)
            cout << x << " ", f = 0;
        cout << t[i] << " ";
    }
    cout << endl;
    return 0;
}