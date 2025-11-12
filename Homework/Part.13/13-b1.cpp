#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

bool print_check(unsigned char c)
{
    return (c >= 33 && c <= 126);
}

void display_Hex(const string &filename)
{

    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "输入文件" << filename << "打开失败!" << endl;
        return;
    }
    const int N = 16;
    unsigned char buffer[N];
    streamsize offset = 0;

    while (file)
    {
        file.read(reinterpret_cast<char *>(buffer), N);
        streamsize n = file.gcount(); // 文件字节数

        if (n == 0)
            break;

        cout << hex << uppercase << setw(8) << setfill('0') << offset << ":  ";

        for (int i = 0; i < N; i++)
        {
            if (i < n)
                cout << hex << setw(2) << setfill('0') << static_cast<int>(buffer[i]);
            else
                cout << "  ";

            if (i == 7)
                cout << " - ";
            else if (i < N - 1)
                cout << " ";
        }

        cout << "  ";

        for (int i = 0; i < n; i++)
        {
            if (print_check(buffer[i]))
                cout << buffer[i];
            else
                cout << ".";
        }
        cout << endl;
        offset += n;
    }

    file.close();
}

int main()
{
    cerr << "文件名以下形式均可以:" << endl
         << "a.txt : 不带路径形式" << endl
         << "..\\data\b.dat : 相对路径形式" << endl
         << "C :\\Windows\\System32\\c.dat : 绝对相对路径形式 " << endl;
    cerr << "请输入文件名: ";
    string filename;
    getline(cin, filename);
    display_Hex(filename);
    return 0;
}