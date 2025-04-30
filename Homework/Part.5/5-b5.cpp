#include <iostream>
#include <limits>
using namespace std;
int main()
{
    int t[1010], x, n = 0, f = 1;
    cout << "请输入成绩（最多1000个），负数结束输入" << endl;
    while (1)
    {
        n++;
        cin >> t[n];

        if (t[n] < 0 || n > 1000)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            break;
        }
    }
    cout << "输入的数组为:" << endl;
    for (int i = 1; i < n; i++)
    {
        cout << t[i] << " ";
        if (i % 10 == 0)
            cout << endl;
    }
    cout << endl;
    cout << "分数与名次的对应关系为:" << endl;
    int cnt[105] = {0};
    for (int i = 1; i <= n; i++)
        cnt[t[i]]++;
    for (int i = 100, s = 1; i >= 0; i--)
    {
        if (cnt[i] != 0)
        {
            for (int j = 1, u = s; j <= cnt[i]; j++, s++)
                cout << i << " " << u << endl;
        }
    }
    return 0;
}