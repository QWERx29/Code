/* 学号 姓名 班级 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM 4
#define SCORE_NUM 5

/* --- 不允许定义任何形式的全局变量 --- */

/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：相关输出都放在函数中即可
***************************************************************************/
void average(int (*score)[SCORE_NUM])
{
    double sum = 0;
    int (*p)[SCORE_NUM];
    for (p = score; p < score + STUDENT_NUM; p++)
        sum += *(*p);
    cout << "第1门课平均分：" << sum / STUDENT_NUM << endl;
}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：相关输出都放在函数中即可
***************************************************************************/
void fail(int (*score)[SCORE_NUM])
{
    int (*p)[SCORE_NUM];
    int *q;
    int count, student_count;
    double sum;
    cout << "2门以上不及格的学生：" << endl;
    for (p = score, student_count = 0; p < score + STUDENT_NUM; p++, student_count++)
    {
        count = 0;
        sum = 0;
        for (q = *p; q < *p + SCORE_NUM; q++)
        {
            if (*q < 60)
                count++;
            sum += *q;
        }
        if (count >= 2)
        {
            cout << "No：" << student_count + 1 << " ";
            for (q = *p; q < *p + SCORE_NUM; q++)
                cout << *q << " ";
            cout << "平均：" << sum / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  函数名称：
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void good(int (*score)[SCORE_NUM])
{
    int (*p)[SCORE_NUM];
    int *q;
    int all_above_85, student_count;
    double sum;
    cout << "平均90以上或全部85以上的学生：" << endl;
    for (p = score, student_count = 0; p < score + STUDENT_NUM; p++, student_count++)
    {
        sum = 0;
        all_above_85 = 1;
        for (q = *p; q < *p + SCORE_NUM; q++)
        {
            sum += *q;
            if (*q < 85)
                all_above_85 = 0;
        }
        if (sum / SCORE_NUM >= 90 || all_above_85)
        {
            cout << "No：" << student_count + 1 << " ";
            for (q = *p; q < *p + SCORE_NUM; q++)
                cout << *q << " ";
            cout << "平均：" << sum / SCORE_NUM << endl;
        }
    }
}

int main()
{
    int a[STUDENT_NUM][SCORE_NUM] = {
        {91, 81, 71, 61, 51},  // 第1个学生的1-5门课的成绩
        {92, 82, 72, 32, 52},  // 第2个学生的1-5门课的成绩
        {93, 83, 99, 80, 95},  // 第3个学生的1-5门课的成绩
        {97, 85, 87, 91, 88}}; // 第4个学生的1-5门课的成绩

    int (*p)[SCORE_NUM], *q;
    int i;
    cout << "初始信息：" << endl;
    for (p = a, i = 0; p < a + STUDENT_NUM; p++, i++)
    {
        cout << "No." << i + 1 << "的1-5门课成绩：";
        for (q = *p; q < *p + SCORE_NUM; q++)
            cout << *q << " ";
        cout << endl;
    }
    cout << endl;
    average(a);
    cout << endl;
    fail(a);
    cout << endl;
    good(a);

    return 0;
}