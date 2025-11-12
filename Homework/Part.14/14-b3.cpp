#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>

using namespace std;

// 显示用法信息
int usage(const char *const procname)
{
    cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl
         << endl;
    cout << "e.g. : " << procname << " 2459999 2459998 all       80 screen" << endl;
    cout << "       " << procname << " 2459999 all     14-b1.cpp 75 result.txt" << endl;
    cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
    cout << "       " << procname << " all     all     all       85 screen" << endl;

    return 0;
}

// 检查是否为7位纯数字
bool checkNo(const string &str)
{
    if (str.length() != 7)
        return false;
    for (size_t i = 0; i < str.length(); i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

// 检查字符串长度是否超过32字节
bool checkLen(const string &str)
{
    return str.length() > 32;
}

// 主参数解析函数
int parseArguments(int argc, char *argv[], string &stu_1, string &stu_2, string &filename, int &similarity, string &output)
{
    if (argc != 6)
    {
        usage(argv[0]);
        return -1;
    }

    stu_1 = argv[1];
    stu_2 = argv[2];
    filename = argv[3];
    string similarityStr = argv[4];
    output = argv[5];

    if (stu_1 == "all")
    {
        if (stu_2 != "all")
        {
            cerr << "检查学号是all，匹配学号必须是all" << endl;
            return -1;
        }
    }
    else
    {
        if (!checkNo(stu_1))
        {
            if (stu_1.length() != 7)
                cerr << "要检查的学号不是7位" << endl;
            else
                cerr << "要检查的学号不是7位数字" << endl;
            return -1;
        }
        if (stu_2 != "all" && !checkNo(stu_2))
        {
            if (stu_2.length() != 7)
                cerr << "要匹配的学号不是7位" << endl;
            else
                cerr << "要匹配的学号不是7位数字" << endl;
            return -1;
        }
    }

    if (filename != "all" && checkLen(filename))
    {
        cerr << "源程序文件名超过了32字节" << endl;
        return -1;
    }

    similarity = 80;
    if (!similarityStr.empty())
    {
        char *endptr;
        long sim = strtol(similarityStr.c_str(), &endptr, 10);
        if (endptr == similarityStr.c_str() + similarityStr.length() && sim >= 60 && sim <= 100)
            similarity = (int)sim;
    }

    if (output != "screen" && checkLen(output))
    {
        cerr << "输出结果文件名超过了32字节" << endl;
        return -1;
    }

        return 0;
}

// 显示解析结果
void display(const string &stu_1, const string &stu_2, const string &filename, int similarity, const string &output)
{

    cout << "参数解析通过" << endl;

    cout << "检查学号：" << stu_1 << endl;
    cout << "匹配学号：" << stu_2 << endl;
    cout << "源文件名：" << filename << endl;
    cout << "匹配阈值：" << similarity << endl;
    cout << "输出目标：" << output << endl;
}

int main(int argc, char *argv[])
{
    string stu_1, stu_2, filename, output;
    int similarity;

    int result = parseArguments(argc, argv, stu_1, stu_2, filename, similarity, output);

    if (result == 0)
        display(stu_1, stu_2, filename, similarity, output);
    else
        return 1;

    return 0;
}