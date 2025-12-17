#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum FileFormat
{
    FORMAT_WINDOWS,
    FORMAT_LINUX,
    FORMAT_UNKNOWN,
    FORMAT_ERROR
};

FileFormat checkFileFormat(const string &filename)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open())
        return FORMAT_ERROR;

    bool hasCRLF = false;
    bool hasLoneLF = false;
    char prevChar = 0;
    char currentChar;

    while (file.get(currentChar))
    {
        if (currentChar == '\n')
        {
            if (prevChar == '\r')
                hasCRLF = true;
            else
                hasLoneLF = true;
        }
        prevChar = currentChar;
    }

    file.close();

    if (hasCRLF && hasLoneLF)
        return FORMAT_UNKNOWN;
    else if (hasCRLF)
        return FORMAT_WINDOWS;
    else if (hasLoneLF)
        return FORMAT_LINUX;
    else
        return FORMAT_UNKNOWN;
}

int wtol(const string &srcFile, const string &dstFile)
{
    ifstream src(srcFile, ios::binary);
    ofstream dst(dstFile, ios::binary);

    if (!src.is_open() || !dst.is_open())
        return -1;
    char currentChar;
    int cnt = 0;

    while (src.get(currentChar))
    {
        if (currentChar == '\r')
        {
            if (src.peek() != '\n')
                dst.put(currentChar);
            else
                cnt++;
        }
        else
            dst.put(currentChar);
    }

    src.close();
    dst.close();
    return cnt;
}

int ltow(const string &srcFile, const string &dstFile)
{
    ifstream src(srcFile, ios::binary);
    ofstream dst(dstFile, ios::binary);

    if (!src.is_open() || !dst.is_open())
        return -1;
    char currentChar;
    int cnt = 0;

    while (src.get(currentChar))
    {
        if (currentChar == '\n')
        {
            dst.put('\r');
            cnt++;
        }
        dst.put(currentChar);
    }

    src.close();
    dst.close();
    return cnt;
}

void printUsage(const string &fileName)
{
    cerr << "Usage : " << fileName << " -- check 文件名 | --convert{wtol | ltow} 源文件名 目标文件名 " << endl
         << "        " << fileName << " --check a.txt" << endl
         << "        " << fileName << " --convert wtol a.win.txt a.linux.txt" << endl
         << "        " << fileName << " --convert ltow a.linux.txt a.win.txt";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printUsage(argv[0]);
        return 1;
    }

    string command = argv[1];

    if (command == "--check" && argc == 3)
    {
        string filename = argv[2];
        FileFormat format = checkFileFormat(filename);

        switch (format)
        {
        case FORMAT_WINDOWS:
            cout << "Windows格式" << endl;
            break;
        case FORMAT_LINUX:
            cout << "Linux格式" << endl;
            break;
        case FORMAT_UNKNOWN:
            cout << "文件格式无法识别" << endl;
            break;
        case FORMAT_ERROR:
            cout << "文件打开失败" << endl;
            break;
        }
    }
    else if (command == "--convert" && argc == 5)
    {
        string convertType = argv[2];
        string srcFile = argv[3];
        string dstFile = argv[4];

        FileFormat srcFormat = checkFileFormat(srcFile);

        if (srcFormat == FORMAT_ERROR)
        {
            cout << "文件打开失败" << endl;
            return 1;
        }

        if (convertType == "wtol")
        {
            if (srcFormat != FORMAT_WINDOWS)
            {
                cout << "文件格式无法识别" << endl;
                return 1;
            }
            int cnt = wtol(srcFile, dstFile);
            if (cnt > 0)
                cout << "转换完成，去除" << cnt << "个0x0D" << endl;
            else
            {
                cout << "转换失败" << endl;
                return 1;
            }
        }
        else if (convertType == "ltow")
        {
            if (srcFormat != FORMAT_LINUX)
            {
                cout << "文件格式无法识别" << endl;
                return 1;
            }
            int cnt = ltow(srcFile, dstFile);
            if (cnt > 0)
                cout << "转换完成，加入" << cnt << "个0x0D" << endl;
            else
            {
                cout << "转换失败" << endl;
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