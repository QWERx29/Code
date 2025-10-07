/* 学号 姓名 班级 */
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM 4
#define SCORE_NUM 5

/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void average(int (*score)[STUDENT_NUM])
{
    double sum = 0;
    int *p;
    for (p = *score; p < *score + STUDENT_NUM; p++)
        sum += *p;
    cout << "第1门课平均分：" << sum / STUDENT_NUM << endl;
}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fail(int (*score)[STUDENT_NUM])
{
    int (*p)[STUDENT_NUM];
    int *q;
    int count[STUDENT_NUM] = {0};
    double sum[STUDENT_NUM] = {0};
    int student;
    for (p = score; p < score + SCORE_NUM; p++)
    {
        for (q = *p, student = 0; q < *p + STUDENT_NUM; q++, student++)
        {
            if (*q < 60)
                count[student]++;
            sum[student] += *q;
        }
    }
    cout << "2门以上不及格的学生：" << endl;
    for (student = 0; student < STUDENT_NUM; student++)
    {
        if (count[student] >= 2)
        {
            cout << "No：" << student + 1 << " ";
            for (p = score; p < score + SCORE_NUM; p++)
                cout << *(*p + student) << " ";
            cout << "平均：" << sum[student] / SCORE_NUM << endl;
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
void good(int (*score)[STUDENT_NUM])
{
    int (*p)[STUDENT_NUM];
    int *q;
    int all_above_85[STUDENT_NUM] = {1, 1, 1, 1};
    double sum[STUDENT_NUM] = {0};
    int student;
    for (p = score; p < score + SCORE_NUM; p++)
    {
        for (q = *p, student = 0; q < *p + STUDENT_NUM; q++, student++)
        {
            sum[student] += *q;
            if (*q < 85)
                all_above_85[student] = 0;
        }
    }
    cout << "平均90以上或全部85以上的学生：" << endl;
    for (student = 0; student < STUDENT_NUM; student++)
    {
        if (sum[student] / SCORE_NUM >= 90 || all_above_85[student])
        {
            cout << "No：" << student + 1 << " ";
            for (p = score; p < score + SCORE_NUM; p++)
                cout << *(*p + student) << " ";
            cout << "平均：" << sum[student] / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
    int a[SCORE_NUM][STUDENT_NUM] = {
        {91, 92, 93, 97},  // 第1-4个学生的第1门课成绩
        {81, 82, 83, 85},  // 第1-4个学生的第2门课成绩
        {71, 72, 99, 87},  // 第1-4个学生的第3门课成绩
        {61, 32, 80, 91},  // 第1-4个学生的第4门课成绩
        {51, 52, 95, 88}}; // 第1-4个学生的第5门课成绩
    int (*p)[STUDENT_NUM], *q;
    int i;

    cout << "初始信息：" << endl;
    for (p = a, i = 0; p < a + SCORE_NUM; p++, i++)
    {
        cout << "No.1-4学生的第" << i + 1 << "门课的成绩：";
        for (q = *p; q < *p + STUDENT_NUM; q++)
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