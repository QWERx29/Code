/* 学号 姓名 班级 */
#include <iostream>
using namespace std;

/* 1、不允许定义任何类型的全局变量，包括常变量及宏定义等
   2、不允许给出任何形式的全局函数
*/

/* --- 将类的定义补充完整 --- */
class Days
{
private:
    int year;
    int month;
    int day;

public:
    int calc_days();
    Days(int y, int m, int t);
};

int Days::calc_days()
{
    int d = 0;
    int dt[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool x = false;
    if (Days::month < 1 || Days::month > 12)
        return -1;
    if (Days::day > 31 || Days::day < 1)
        return -1;
    else if ((Days::month == 4 || Days::month == 6 || Days::month == 9 || Days::month == 11) && Days::day > 30)
        return -1;
    if ((Days::year % 4 == 0 && Days::year % 100 != 0) || Days::year % 400 == 0)
        x = true;
    if (x == true)
        dt[1] = 29;
    else
    {
        if (Days::month == 2 && Days::day > 28)
            return -1;
    }
    for (int i = 0; i < Days::month - 1; i++)
        d += dt[i];
    d += Days::day;
    return d;
}

Days::Days(int y, int m, int d)
{
    year = y;
    month = m;
    day = d;
}
/* --- 此处给出类成员函数的体外实现 --- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
 ***************************************************************************/
int main()
{
    if (1)
    {
        Days d1(2024, 3, 18);
        cout << "应该输出78， 实际是：" << d1.calc_days() << endl;
    }

    if (1)
    {
        Days d1(2023, 3, 18);
        cout << "应该输出77， 实际是：" << d1.calc_days() << endl;
    }

    if (1)
    {
        Days d1(2024, 12, 31);
        cout << "应该输出366，实际是：" << d1.calc_days() << endl;
    }

    if (1)
    {
        Days d1(2023, 12, 31);
        cout << "应该输出365，实际是：" << d1.calc_days() << endl;
    }

    if (1)
    {
        Days d1(2024, 2, 29);
        cout << "应该输出60， 实际是：" << d1.calc_days() << endl;
    }

    if (1)
    {
        Days d1(2023, 2, 29);
        cout << "应该输出-1， 实际是：" << d1.calc_days() << endl;
    }

    return 0;
}