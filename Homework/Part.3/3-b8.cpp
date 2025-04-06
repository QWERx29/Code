#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    double ans = 1.0, x, t = 1.0;
    cout << "请输入 x 的值[-10 ~ +65]" << endl;
    cin >> x;
    while (x < -10 || x > 65)
    {
        cout << "输入非法，请重新输入" << endl;
        cin >> x;
    }
    long long n = 1;
    while (fabs(t) > 10e-6)
    {
        t = 1.0;
        for (int j = 1; j <= n; j++)
            t *= x / j;
        ans += t;
        n++;
    }
    cout << "e^" << x << "=" << setprecision(10) << ans << endl;
    return 0;
}