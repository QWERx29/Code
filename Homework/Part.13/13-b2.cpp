#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>

using namespace std;

unsigned char Hex2Val(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0;
}

unsigned char Hex2Bit(const string &hex)
{
    if (hex.length() != 2)
        return 0;
    return (Hex2Val(hex[0]) << 4) | Hex2Val(hex[1]);
}

void convert_Hex(const string &i_filename, const string &o_filename)
{
    ifstream inputFile(i_filename);
    if (!inputFile.is_open())
        cerr << "输入文件" << i_filename << "打开失败!" << endl;
    ofstream outputFile(o_filename, ios::binary);
    if (!outputFile.is_open())
        cerr << "输出文件" << o_filename << "创建失败!" << endl;

    string line;
    int cnt = 0;
    int tot = 0;

    while (getline(inputFile, line))
    {
        cnt++;
        size_t hexStart = 11;
        string hexData;
        for (size_t i = hexStart; i < line.length(); i++)
        {
            char c = line[i];
            if (i + 1 < line.length() && c == ' ' && line[i + 1] == ' ')
                break;
            if (c != ' ' && c != '-')
                hexData += c;
        }

        for (size_t i = 0; i < hexData.length(); i += 2)
        {
            string byteStr = hexData.substr(i, 2);
            unsigned char byteValue = Hex2Bit(byteStr);
            outputFile.put(byteValue);
            tot++;
        }
    }

    inputFile.close();
    outputFile.close();
}

int main()
{
    cerr << "文件名以下形式均可以:" << endl
         << "a.hex : 不带路径形式" << endl
         << "..\\data\\b.txt : 相对路径形式" << endl
         << "C :\\Windows\\System32\\c.hex : 绝对相对路径形式 " << endl;

    cerr << "请输入要转换的hex格式文件名 :";
    string i_filename;
    getline(cin, i_filename);
    cerr << "请输入转换后的文件名        :";
    string o_filename;
    getline(cin, o_filename);

    convert_Hex(i_filename, o_filename);
    return 0;
}