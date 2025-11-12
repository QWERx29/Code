#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct student
{
    int no;
    char name[17];
    int score;
    struct student *next;
};

int main()
{
    ifstream fin("list.txt");
    if (!fin.is_open())
        return -1;

    student *head = nullptr;
    student *tail = nullptr;
    student *new_node = nullptr;

    int no, score;
    char name[17];

    while (1)
    {
        fin >> no >> name >> score;
        if (fin.fail())
            break;

        if (no == 9999999)
            break;

        new_node = new (nothrow) student;
        if (new_node == nullptr)
        {
            fin.close();
            return -1;
        }

        new_node->no = no;
        strcpy(new_node->name, name);
        new_node->score = score;
        new_node->next = nullptr;

        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    fin.close();

    student *current = head;
    while (current != nullptr)
    {
        cout << current->no << " " << current->name << " " << current->score << endl;
        current = current->next;
    }
    current = head;
    while (current != nullptr)
    {
        student *temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}