#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int *no;
    char *name;
    int *score;
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

    int temp_no, temp_score;
    char temp_name[100];

    while (1)
    {
        if (fscanf(fp, "%d %s %d", &temp_no, temp_name, &temp_score) != 3)
            break;
        if (temp_no == 9999999)
            break;

        new_node = (struct student *)malloc(sizeof(struct student));
        if (new_node == NULL)
        {
            fclose(fp);
            return -1;
        }

        new_node->no = (int *)malloc(sizeof(int));
        if (new_node->no == NULL)
        {
            free(new_node);
            fclose(fp);
            return -1;
        }
        *(new_node->no) = temp_no;

        int name_len = strlen(temp_name);
        new_node->name = (char *)malloc((name_len + 1) * sizeof(char));
        if (new_node->name == NULL)
        {
            free(new_node->no);
            free(new_node);
            fclose(fp);
            return -1;
        }
        strcpy(new_node->name, temp_name);

        new_node->score = (int *)malloc(sizeof(int));
        if (new_node->score == NULL)
        {
            free(new_node->name);
            free(new_node->no);
            free(new_node);
            fclose(fp);
            return -1;
        }
        *(new_node->score) = temp_score;

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
        printf("%d %s %d\n", *(current->no), current->name, *(current->score));
        current = current->next;
    }

    current = head;
    while (current != NULL)
    {
        struct student *temp = current;
        current = current->next;

        free(temp->no);
        free(temp->name);
        free(temp->score);
        free(temp);
    }

    return 0;
}