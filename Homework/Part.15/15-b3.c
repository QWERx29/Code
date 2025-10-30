#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int print_check(unsigned char c)
{
    return (c >= 33 && c <= 126);
}

void display_hex_viewer(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        fprintf(stderr, "输入文件%s打开失败!\n", filename);
        return;
    }

    const int BYTES_PER_LINE = 16;
    unsigned char buffer[BYTES_PER_LINE];
    long offset = 0;
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BYTES_PER_LINE, file)) > 0)
    {
        printf("%08lX:  ", offset);

        for (int i = 0; i < BYTES_PER_LINE; i++)
        {
            if (i < bytes_read)
                printf("%02X", buffer[i]);
            else
                printf("  ");
            if (i == 7)
                printf(" - ");
            else if (i < BYTES_PER_LINE - 1)
                printf(" ");
        }

        printf("  ");

        for (int i = 0; i < bytes_read; i++)
        {
            if (print_check(buffer[i]))
                printf("%c", buffer[i]);
            else
                printf(".");
        }

        printf("\n");
        offset += bytes_read;
    }

    fclose(file);
}

int main()
{
    fprintf(stderr, "文件名以下形式均可以:\na.txt : 不带路径形式\n..\\data\b.dat : 相对路径形式\nC :\\Windows\\System32\\c.dat : 绝对相对路径形式 \n");
    fprintf(stderr, "请输入文件名: ");

    char filename[1024];
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        fprintf(stderr, "读取文件名失败\n");
        return 1;
    }
    filename[strcspn(filename, "\n")] = 0;
    display_hex_viewer(filename);
    return 0;
}