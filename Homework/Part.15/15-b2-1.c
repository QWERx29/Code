#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int no;
    char name[17];
    int score;
    struct student *next;
};

int main()
{
    FILE *fp = fopen("list.txt", "r");
    if (fp == NULL)
        return -1;

    struct student *head = NULL;
    struct student *tail = NULL;
    struct student *new_node = NULL;

    int no, score;
    char name[17];

    while (1)
    {
        if (fscanf(fp, "%d %s %d", &no, name, &score) != 3)
            break;
        if (no == 9999999)
            break;

        new_node = (struct student *)malloc(sizeof(struct student));
        if (new_node == NULL)
        {
            fclose(fp);
            return -1;
        }

        new_node->no = no;
        strcpy(new_node->name, name);
        new_node->score = score;
        new_node->next = NULL;

        if (head == NULL)
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

    fclose(fp);

    struct student *current = head;
    while (current != NULL)
    {
        printf("%d %s %d\n", current->no, current->name, current->score);
        current = current->next;
    }

    current = head;
    while (current != NULL)
    {
        struct student *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}