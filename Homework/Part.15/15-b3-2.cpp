#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct student
{
    int *no;
    char *name;
    int *score;
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

    int temp_no, temp_score;
    char temp_name[100];

    while (true)
    {
        fin >> temp_no >> temp_name >> temp_score;
        if (fin.fail())
            break;
        if (temp_no == 9999999)
            break;

        new_node = new (nothrow) student;
        if (new_node == nullptr)
        {
            fin.close();
            return -1;
        }

        new_node->no = new (nothrow) int;
        if (new_node->no == nullptr)
        {
            delete new_node;
            fin.close();
            return -1;
        }
        *(new_node->no) = temp_no;

        int name_len = strlen(temp_name);
        new_node->name = new (nothrow) char[name_len + 1];
        if (new_node->name == nullptr)
        {
            delete new_node->no;
            delete new_node;
            fin.close();
            return -1;
        }
        strcpy(new_node->name, temp_name);

        new_node->score = new (nothrow) int;
        if (new_node->score == nullptr)
        {
            delete[] new_node->name;
            delete new_node->no;
            delete new_node;
            fin.close();
            return -1;
        }
        *(new_node->score) = temp_score;

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
        cout << *(current->no) << " " << current->name << " " << *(current->score) << endl;
        current = current->next;
    }

    current = head;
    while (current != nullptr)
    {
        student *temp = current;
        current = current->next;

        delete temp->no;
        delete[] temp->name;
        delete temp->score;
        delete temp;
    }

    return 0;
}