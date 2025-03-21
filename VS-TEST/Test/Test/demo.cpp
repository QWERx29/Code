#include <iostream>
using namespace std;

int main()
{
    int i;
    cout << "请输入成绩[0-100]" << endl;
    cin >> i;
    if (i >= 90 && i <= 100)
        cout << "优" << endl;
    else if (i >= 80 && i <= 90)
        cout << "良" << endl;
    else if (i >= 70 && i < 80)
        cout << "中" << endl;
    else if (i >= 60 && i < 70)
        cout << "及格" << endl;
    else if (i >= 0 && i < 60)
        cout << "不及格" << endl;
    else
        cout << "输入错误" << endl;
    cout << "程序结束" << endl;
    return 0;
}
