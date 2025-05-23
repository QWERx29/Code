// 2451317 冯久恒 计算机
#include <iostream>
using namespace std;

int div(int n)
{
    if (n < 10)
        return n;
    else
        return div(n % 10 + div(n / 10));
}

int main()
{
    int n, sum[10086], t;
    cout << "请输入数据的个数[1..10000]" << endl;
    cin >> n;
    cout << "请输入" << n << "个正整数" << endl;
    for (int i = 1; i <= n; i++)
        cin >> sum[i];
    cout << "请输入要统计的基数[1..9]" << endl;
    cin >> t;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (div(sum[i]) == t)
            ans++;
    cout << n << "个数中迭代累加后值为" << t << "的数字的个数 : " << ans << endl;
    return 0;
}
