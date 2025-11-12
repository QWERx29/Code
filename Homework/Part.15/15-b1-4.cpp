#include <iostream>
#include <fstream>

using namespace std;

struct student
{
    int no;
    char name[17];
    int score;
    int rank;
};

int init(student *&stu)
{
    ifstream fin("student.txt");
    if (!fin)
        return 0;

    int n;
    fin >> n;

    stu = new (nothrow) student[n];
    if (!stu)
    {
        fin.close();
        return 0;
    }

    for (int i = 0; i < n; i++)
        fin >> stu[i].no >> stu[i].name >> stu[i].score;

    fin.close();
    return n;
}

void sortByScore(student *stu, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (stu[j].score < stu[j + 1].score)
            {
                student temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp;
            }
        }
    }
}

void calculateRank(student *stu, int n)
{
    if (n <= 0)
        return;

    stu[0].rank = 1;
    for (int i = 1; i < n; i++)
    {
        if (stu[i].score == stu[i - 1].score)
            stu[i].rank = stu[i - 1].rank;
        else
            stu[i].rank = i + 1;
    }
}

void sortByRankAndNo(student *stu, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (stu[j].rank > stu[j + 1].rank ||
                (stu[j].rank == stu[j + 1].rank && stu[j].no > stu[j + 1].no))
            {
                student temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp;
            }
        }
    }
}

void output(student *stu, int n)
{
    for (int i = 0; i < n; i++)
        cout << stu[i].no << " " << stu[i].name << " " << stu[i].score << " " << stu[i].rank << endl;
}

int main()
{
    student *students = NULL;
    int n = init(students);

    if (n > 0)
    {
        sortByScore(students, n);
        calculateRank(students, n);
        sortByRankAndNo(students, n);
        output(students, n);

        delete[] students;
    }

    return 0;
}