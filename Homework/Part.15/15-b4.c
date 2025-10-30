#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned char Hex2Val(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 0;
}

unsigned char Hex2Bit(const char *hex)
{
    if (strlen(hex) < 2)
        return 0;
    return (Hex2Val(hex[0]) << 4) | Hex2Val(hex[1]);
}

void convert_Hex(const char *i_filename, const char *o_filename)
{
    FILE *input_file = fopen(i_filename, "r");
    if (!input_file)
        fprintf(stderr, "错误：无法打开输入文件%s", i_filename);
    FILE *output_file = fopen(o_filename, "wb");
    if (!output_file)
        fprintf(stderr, "错误：无法创建输出文件%s", o_filename);

    char line[1024];
    int line_count = 0;
    int total_bytes = 0;

    while (fgets(line, sizeof(line), input_file))
    {
        line_count++;
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0)
            continue;
        int hex_start = 11;

        char hex_data[512] = {0};
        int hex_index = 0;

        for (int i = hex_start; i < (int)strlen(line); i++)
        {
            char c = line[i];
            if (i + 1 < (int)strlen(line) && c == ' ' && line[i + 1] == ' ')
                break;
            if (c != ' ' && c != '-')
                hex_data[hex_index++] = c;
        }
        hex_data[hex_index] = '\0';

        for (size_t i = 0; i < strlen(hex_data); i += 2)
        {
            char byte_str[3] = {hex_data[i], hex_data[i + 1], '\0'};
            unsigned char byte_value = Hex2Bit(byte_str);
            fputc(byte_value, output_file);
            total_bytes++;
        }
    }

    fclose(input_file);
    fclose(output_file);
}

int main()
{
    fprintf(stderr, "文件名以下形式均可以:\na.txt : 不带路径形式\n..\\data\b.dat : 相对路径形式\nC :\\Windows\\System32\\c.dat : 绝对相对路径形式 \n");
    fprintf(stderr, "请输入要转换的hex格式文件名 :");
    char i_filename[1024];
    if (fgets(i_filename, sizeof(i_filename), stdin) == NULL)
        fprintf(stderr, "读取输入文件名失败\n");
    i_filename[strcspn(i_filename, "\n")] = 0;

    fprintf(stderr, "请输入转换后的文件名        :");
    char o_filename[1024];
    if (fgets(o_filename, sizeof(o_filename), stdin) == NULL)
        fprintf(stderr, "读取输出文件名失败\n");
    o_filename[strcspn(o_filename, "\n")] = 0;

    convert_Hex(i_filename, o_filename);
    return 0;
}