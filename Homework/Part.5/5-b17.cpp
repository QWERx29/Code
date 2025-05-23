// 2451317 冯久恒 计算机 
#include <iostream>
#include <time.h>
using namespace std;

char chr[4][30] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz", "0123456789"};
static const char oth[] = "!@#$%^&*-_=+,.?";
const int lll[] = {26, 26, 10, 15};

void exg(char ch[], int l)
{
    for (int i = 0; i < l; i++)
    {
        int t = rand() % (l - i);
        char u;
        u = ch[i], ch[i] = ch[t], ch[t] = u;
    }
}

int main()
{
    int len, op[4];
    srand((unsigned int)(time(0))); // 生成伪随机数的种子，只需在程序开始时执行一次即可
    cout << "请输入密码长度(12-16)， 大写字母个数(≥2)， 小写字母个数(≥2)， 数字个数(≥2)， 其它符号个数(≥2)" << endl;
    cin >> len >> op[0] >> op[1] >> op[2] >> op[3];
    if (cin.good() != 1)
    {
        cout << "输入非法" << endl;
        return 0;
    }
    else if (len < 12 || len > 16)
    {
        cout << "密码长度[" << len << "]不正确" << endl;
        return 0;
    }
    else if (op[0] < 2 || op[0] > len)
    {
        cout << "大写字母个数[" << op[0] << "]不正确" << endl;
        return 0;
    }
    else if (op[1] < 2 || op[1] > len)
    {
        cout << "小写字母个数[" << op[1] << "]不正确" << endl;
        return 0;
    }
    else if (op[2] < 2 || op[2] > len)
    {
        cout << "数字个数[" << op[2] << "]不正确" << endl;
        return 0;
    }
    else if (op[3] < 2 || op[3] > len)
    {
        cout << "其他符号个数[" << op[3] << "]不正确" << endl;
        return 0;
    }
    else if (op[0] + op[1] + op[2] + op[3] > len)
    {
        cout << "所有字符类型之和[" << op[0] << "+" << op[1] << "+" << op[2] << "+" << op[3] << "]大于总密码长度[" << len << "]" << endl;
        return 0;
    }
    for (int j = 0; j < lll[3]; j++)
        chr[3][j] = oth[j];
    cout << len << " " << op[0] << " " << op[1] << " " << op[2] << " " << op[3] << endl;
    for (int i = 0; i < 10; i++)
    {
        int cur = 0, cnt[4] = {0};
        char pwd[17] = {0};
        for (int p = 0; p < 4; p++)
        {
            for (int j = 0; j < op[p]; j++)
            {
                int x = rand() % lll[p];
                pwd[cur++] = chr[p][x];
                cnt[p]++;
            }
        }
        for (; cur < len; cur++)
        {
            int x = rand() % 4;
            if (cnt[x] >= op[x])
            {
                int y = rand() % lll[x];
                pwd[cur] = chr[x][y];
            }
        }
        exg(pwd, len);
        cout << pwd << endl;
    }
    return 0;
}
