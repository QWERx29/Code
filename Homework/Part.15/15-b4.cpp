#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

struct Student
{
    char *id;
    char *name;
    char *school;
};

bool init(const char *filename, int &N, int &M, Student *&students);
bool output(const char *filename, int N, Student *selectedStudents);
void select(int N, int M, Student *students, Student *&selectedStudents);
void release(int M, Student *students, int N, Student *selectedStudents);
char *copyString(const char *source);

int main()
{
    int N, M;
    Student *students = nullptr;
    Student *selectedStudents = nullptr;

    cout << "读取待抽签名单...";

    if (!init("stulist.txt", N, M, students))
    {
        cout << "读取数据失败！" << endl;
        return -1;
    }
    cout << "完成" << endl;
    cout << "正在抽签...";
    select(N, M, students, selectedStudents);
    if (output("result.txt", N, selectedStudents))
        cout << "完成" << endl;
    else
    {
        cout << "写入结果失败！" << endl;
        release(M, students, N, selectedStudents);
        return -1;
    }
    release(M, students, N, selectedStudents);
    return 0;
}

char *copyString(const char *source)
{
    if (source == nullptr)
        return nullptr;

    int len = strlen(source);
    char *dest = new (nothrow) char[len + 1];
    if (dest == nullptr)
        return nullptr;

    strcpy(dest, source);
    return dest;
}

bool init(const char *filename, int &N, int &M, Student *&students)
{
    ifstream fin(filename);
    if (!fin.is_open())
        return -1;

    fin >> N >> M;
    fin.ignore();
    students = new (nothrow) Student[M];
    if (students == nullptr)
    {
        fin.close();
        return -1;
    }
    for (int i = 0; i < M; i++)
    {
        students[i].id = nullptr;
        students[i].name = nullptr;
        students[i].school = nullptr;
    }
    const int BUFFER_SIZE = 1024;
    char line_buffer[BUFFER_SIZE];

    for (int i = 0; i < M; i++)
    {
        if (!fin.getline(line_buffer, BUFFER_SIZE))
        {
            fin.close();
            return -1;
        }

        char *id_start = line_buffer;
        char *name_start = strchr(line_buffer, '\t');
        if (name_start == nullptr)
            name_start = strchr(line_buffer, ' ');

        if (name_start == nullptr)
        {
            fin.close();
            return -1;
        }

        *name_start = '\0';
        name_start++;

        char *school_start = strchr(name_start, '\t');
        if (school_start == nullptr)
            school_start = strchr(name_start, ' ');
        if (school_start == nullptr)
        {
            fin.close();
            return -1;
        }

        *school_start = '\0';
        school_start++;

        students[i].id = copyString(id_start);
        students[i].name = copyString(name_start);
        students[i].school = copyString(school_start);

        if (students[i].id == nullptr || students[i].name == nullptr || students[i].school == nullptr)
        {
            fin.close();
            return -1;
        }
    }

    fin.close();
    return 1;
}

void select(int N, int M, Student *students, Student *&selectedStudents)
{
    selectedStudents = new (nothrow) Student[N];
    if (selectedStudents == nullptr)
        return;

    for (int i = 0; i < N; i++)
    {
        selectedStudents[i].id = nullptr;
        selectedStudents[i].name = nullptr;
        selectedStudents[i].school = nullptr;
    }
    srand(time(nullptr));
    bool *selected = new (nothrow) bool[M];
    if (selected == nullptr)
        return;
    for (int i = 0; i < M; i++)
        selected[i] = false;

    int count = 0;
    while (count < N)
    {
        int index = rand() % M;
        if (!selected[index])
        {
            selectedStudents[count].id = copyString(students[index].id);
            selectedStudents[count].name = copyString(students[index].name);
            selectedStudents[count].school = copyString(students[index].school);

            if (selectedStudents[count].id == nullptr ||
                selectedStudents[count].name == nullptr ||
                selectedStudents[count].school == nullptr)
            {
                delete[] selected;
                return;
            }

            selected[index] = true;
            count++;
        }
    }

    delete[] selected;
}

bool output(const char *filename, int N, Student *selectedStudents)
{
    ofstream fout(filename);
    if (!fout.is_open())
        return -1;

    for (int i = 0; i < N; i++)
        fout << selectedStudents[i].id << " " << selectedStudents[i].name << " " << selectedStudents[i].school << endl;
    fout.close();
    return 1;
}

void release(int M, Student *students, int N, Student *selectedStudents)
{
    if (students != nullptr)
    {
        for (int i = 0; i < M; i++)
        {
            if (students[i].id != nullptr)
                delete[] students[i].id;
            if (students[i].name != nullptr)
                delete[] students[i].name;
            if (students[i].school != nullptr)
                delete[] students[i].school;
        }
        delete[] students;
    }
    if (selectedStudents != nullptr)
    {
        for (int i = 0; i < N; i++)
        {
            if (selectedStudents[i].id != nullptr)
                delete[] selectedStudents[i].id;
            if (selectedStudents[i].name != nullptr)
                delete[] selectedStudents[i].name;
            if (selectedStudents[i].school != nullptr)
                delete[] selectedStudents[i].school;
        }
        delete[] selectedStudents;
    }
}