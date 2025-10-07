#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Student
{
    string no;
    string name;
};
class SeqList
{
private:
    vector<Student> data;

public:
    SeqList(int n)
    {
        data.reserve(n + 1000);
        for (int i = 0; i < n; i++)
        {
            Student s;
            cin >> s.no >> s.name;
            data.push_back(s);
        }
    }

    int insert(int i, const string &no, const string &name)
    {
        if (i < 1 || i > data.size() + 1)
            return -1;
        Student newStudent;
        newStudent.no = no;
        newStudent.name = name;
        data.insert(data.begin() + (i - 1), newStudent);
        return 0;
    }
    int remove(int i)
    {
        if (i < 1 || i > data.size())
            return -1;
        data.erase(data.begin() + (i - 1));
        return 0;
    }
    int findByName(const string &name)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].name == name)
                return i;
        }
        return -1;
    }
    int findByNo(const string &no)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].no == no)
                return i;
        }
        return -1;
    }
    int getLength()
    {
        return data.size();
    }
    Student getStudent(int i)
    {
        return data[i];
    }
};

int main()
{
    int n;
    cin >> n;
    SeqList list(n);
    string operation;
    while (cin >> operation)
    {
        if (operation == "end")
            break;
        if (operation == "insert")
        {
            int i;
            string no, name;
            cin >> i >> no >> name;
            int result = list.insert(i, no, name);
            cout << result << endl;
        }
        else if (operation == "remove")
        {
            int i;
            cin >> i;
            int result = list.remove(i);
            cout << result << endl;
        }
        else if (operation == "check")
        {
            string type, value;
            cin >> type >> value;
            int pos = -1;
            if (type == "name")
                pos = list.findByName(value);
            else if (type == "no")
                pos = list.findByNo(value);
            if (pos == -1)
                cout << -1 << endl;
            else
            {
                Student s = list.getStudent(pos);
                cout << pos + 1 << " " << s.no << " " << s.name << endl;
            }
        }
    }
    cout << list.getLength() << endl;
    return 0;
}