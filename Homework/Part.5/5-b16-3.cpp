// 2451317 冯久恒 计算机 
#include <iostream>
using namespace std;

int cmp(const string s1, const string s2, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
        else
            continue;
    }
    return 0;
}

int main()
{
    string name[10], num[10];
    int pts[10];
    for (int i = 0; i < 10; i++)
    {
        cout << "请输入第" << i + 1 << "个人的学号、姓名、成绩" << endl;
        cin >> num[i] >> name[i] >> pts[i];
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (cmp(num[i], num[j], 8) == 1)
            {
                string t1, t2;
                int t3;
                t1 = name[i], name[i] = name[j], name[j] = t1;
                t2 = num[i], num[i] = num[j], num[j] = t2;
                t3 = pts[i], pts[i] = pts[j], pts[j] = t3;
            }
        }
    }
    cout << endl;
    cout << "全部学生(学号升序):" << endl;
    for (int i = 0; i < 10; i++)
        cout << name[i] << " " << num[i] << " " << pts[i] << endl;
    return 0;
}
