// 2451317 ·ë¾Ãºã ¼ÆËã»ú 
#include <iostream>
using namespace std;

static const char oth[] = "!@#$%^&*-_=+,.?";
int check(char ch)
{
    for (int i = 0; i < 15; i++)
    {
        if (ch == oth[i])
            return 1;
    }
    return -1;
}

int main()
{
    char tmp[999];
    fgets(tmp, 999, stdin);
    int len, op[4];
    cin >> len >> op[0] >> op[1] >> op[2] >> op[3];
    if (cin.good() != 1)
    {
        cout << "´íÎó" << endl;
        return 0;
    }
    else if (len < 12 || len > 16)
    {
        cout << "´íÎó" << endl;
        return 0;
    }
    else if (op[0] < 2 || op[0] > len)
    {
        cout << "´íÎó" << endl;
        return 0;
    }
    else if (op[1] < 2 || op[1] > len)
    {
        cout << "´íÎó" << endl;
        return 0;
    }
    else if (op[2] < 2 || op[2] > len)
    {
        cout << "´íÎó" << endl;
        return 0;
    }
    else if (op[3] < 2 || op[3] > len)
    {
        cout << "´íÎó" << endl;
        return 0;
    }
    else if (op[0] + op[1] + op[2] + op[3] > len)
    {
        cout << "´íÎó" << endl;
        return 0;
    }
    for (int i = 0; i < 10; i++)
    {
        bool f = true;
        char pwd[17];
        cin >> pwd;
        int cur = 0, cnt[4] = {0}, o = 0;
        for (; pwd[cur] != '\0'; cur++)
        {
            if (pwd[cur] >= 'A' && pwd[cur] <= 'Z')
                cnt[0]++;
            else if (pwd[cur] >= 'a' && pwd[cur] <= 'z')
                cnt[1]++;
            else if (pwd[cur] >= '0' && pwd[cur] <= '9')
                cnt[2]++;
            else
            {
                if (check(pwd[cur]) == 1)
                    cnt[3]++;
                else
                    f = false;
            }
        }
        if (cur < len - 1)
            f = false;
        for (int j = 0; j < 4; j++)
        {
            o += cnt[j];
            if (cnt[j] < op[j])
                f = false;
        }
        if (o != len)
            f = false;
        if (f == false)
        {
            cout << "´íÎó" << endl;
            return 0;
        }
    }
    cout << "ÕýÈ·" << endl;
    return 0;
}
