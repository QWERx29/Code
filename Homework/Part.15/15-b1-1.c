#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int no;
    char name[17];
    int score;
    int rank;
};

int init(struct student **stu)
{
    FILE *fp = fopen("student.txt", "r");
    if (!fp)
        return 0;
    int n;
    fscanf(fp, "%d", &n);

    *stu = (struct student *)malloc(n * sizeof(struct student));
    if (!*stu)
    {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < n; i++)
        fscanf(fp, "%d %s %d", &(*stu)[i].no, (*stu)[i].name, &(*stu)[i].score);

    fclose(fp);
    return n;
}

void sortByScore(struct student *stu, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
            if (stu[j].score > stu[maxIndex].score)
                maxIndex = j;
        if (maxIndex != i)
        {
            struct student temp = stu[i];
            stu[i] = stu[maxIndex];
            stu[maxIndex] = temp;
        }
    }
}

void calculateRank(struct student *stu, int n)
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

void sortByNo(struct student *stu, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (stu[j].no < stu[minIndex].no)
                minIndex = j;
        if (minIndex != i)
        {
            struct student temp = stu[i];
            stu[i] = stu[minIndex];
            stu[minIndex] = temp;
        }
    }
}

void output(struct student *stu, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d %s %d %d\n", stu[i].no, stu[i].name, stu[i].score, stu[i].rank);
}

int main()
{
    struct student *students = NULL;
    int n = init(&students);

    if (n > 0)
    {
        sortByScore(students, n);
        calculateRank(students, n);
        sortByNo(students, n);
        output(students, n);

        free(students);
    }

    return 0;
}