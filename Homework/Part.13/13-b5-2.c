#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    FORMAT_WINDOWS,
    FORMAT_LINUX,
    FORMAT_UNKNOWN,
    FORMAT_ERROR
} FileFormat;

FileFormat checkFileFormat(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
        return FORMAT_ERROR;

    int hasCRLF = 0;
    int hasLoneLF = 0;
    int prevChar = -1;
    int currentChar;

    while ((currentChar = fgetc(file)) != EOF)
    {
        if (currentChar == '\n')
        {
            if (prevChar == '\r')
                hasCRLF = 1;
            else
                hasLoneLF = 1;
        }
        prevChar = currentChar;
    }

    fclose(file);

    if (hasCRLF && hasLoneLF)
        return FORMAT_UNKNOWN;
    else if (hasCRLF)
        return FORMAT_WINDOWS;
    else if (hasLoneLF)
        return FORMAT_LINUX;
    else
        return FORMAT_UNKNOWN;
}

int wtol(const char *srcFile, const char *dstFile)
{
    FILE *src = fopen(srcFile, "rb");
    FILE *dst = fopen(dstFile, "wb");

    if (!src || !dst)
    {
        if (src)
            fclose(src);
        if (dst)
            fclose(dst);
        return -1;
    }

    int currentChar;
    int cnt = 0;

    while ((currentChar = fgetc(src)) != EOF)
    {
        if (currentChar == '\r')
        {
            int nextChar = fgetc(src);
            if (nextChar == '\n')
            {
                fputc('\n', dst);
                cnt++;
            }
            else
            {
                fputc('\r', dst);
                if (nextChar != EOF)
                    ungetc(nextChar, src);
            }
        }
        else
            fputc(currentChar, dst);
    }

    fclose(src);
    fclose(dst);
    return cnt;
}

int ltow(const char *srcFile, const char *dstFile)
{
    FILE *src = fopen(srcFile, "rb");
    FILE *dst = fopen(dstFile, "wb");

    if (!src || !dst)
    {
        if (src)
            fclose(src);
        if (dst)
            fclose(dst);
        return -1;
    }

    int currentChar;
    int cnt = 0;

    while ((currentChar = fgetc(src)) != EOF)
    {
        if (currentChar == '\n')
        {
            fputc('\r', dst);
            cnt++;
        }
        fputc(currentChar, dst);
    }

    fclose(src);
    fclose(dst);
    return cnt;
}

void printUsage(const char *fileName)
{

    printf("Usage : %s -- check 文件名 | --convert{wtol | ltow} 源文件名 目标文件名\n", fileName);
    printf("        %s --check a.txt\n", fileName);
    printf("        %s --convert wtol a.win.txt a.linux.txt\n", fileName);
    printf("        %s --convert ltow a.linux.txt a.win.txt\n", fileName);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printUsage(argv[0]);
        return 1;
    }

    char *command = argv[1];

    if (strcmp(command, "--check") == 0 && argc == 3)
    {
        char *filename = argv[2];
        FileFormat format = checkFileFormat(filename);

        switch (format)
        {
        case FORMAT_WINDOWS:
            printf("Windows格式\n");
            break;
        case FORMAT_LINUX:
            printf("Linux格式\n");
            break;
        case FORMAT_UNKNOWN:
            printf("文件格式无法识别\n");
            break;
        case FORMAT_ERROR:
            printf("文件打开失败\n");
            break;
        }
    }
    else if (strcmp(command, "--convert") == 0 && argc == 5)
    {
        char *convertType = argv[2];
        char *srcFile = argv[3];
        char *dstFile = argv[4];

        FileFormat srcFormat = checkFileFormat(srcFile);

        if (srcFormat == FORMAT_ERROR)
        {
            printf("文件打开失败\n");
            return 1;
        }
        if (strcmp(convertType, "wtol") == 0)
        {
            if (srcFormat != FORMAT_WINDOWS)
            {
                printf("文件格式无法识别\n");
                return 1;
            }
            int cnt = wtol(srcFile, dstFile);
            if (cnt > 0)
                printf("转换完成，去除%d个0x0D", cnt);
            else
            {
                printf("转换失败\n");
                return 1;
            }
        }
        else if (strcmp(convertType, "ltow") == 0)
        {
            if (srcFormat != FORMAT_LINUX)
            {
                printf("文件格式无法识别\n");
                return 1;
            }
            int cnt = ltow(srcFile, dstFile);
            if (cnt > 0)
                printf("转换完成，加入%d个0x0D", cnt);
            else
            {
                printf("转换失败\n");
                return 1;
            }
        }
        else
        {
            printUsage(argv[0]);
            return 1;
        }
    }
    else
    {
        printUsage(argv[0]);
        return 1;
    }

    return 0;
}