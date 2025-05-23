// 2451317 冯久恒 计算机 
#include <iostream>
using namespace std;
int main()
{
    char str[3][128];
    int cnt[5] = {0};
    for (int i = 0; i < 3; i++)
    {
        cout << "请输入第" << i + 1 << "行" << endl;
        fgets(str[i], 128, stdin);
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; str[i][j] != '\0'; j++)
        {
            if (str[i][j] >= 'A' && str[i][j] <= 'Z')
                cnt[0]++;
            else if (str[i][j] >= 'a' && str[i][j] <= 'z')
                cnt[1]++;
            else if (str[i][j] >= '0' && str[i][j] <= '9')
                cnt[2]++;
            else if (str[i][j] == ' ')
                cnt[3]++;
            else
                cnt[4]++;
        }
        cnt[4]--;
    }
    cout << "大写 : " << cnt[0] << endl;
    cout << "小写 : " << cnt[1] << endl;
    cout << "数字 : " << cnt[2] << endl;
    cout << "空格 : " << cnt[3] << endl;
    cout << "其他 : " << cnt[4] << endl;
    return 0;
}
