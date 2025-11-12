#include <iostream>
#include <string>
#include <iomanip>
#include <string.h>

using namespace std;

bool getInput(char &chr, char act[])
{
    if (strlen(act) < 2)
        return false;
    chr = toupper(chr);
    if (chr == 'Q')
        return true;
    if (chr < 'A' || chr > 'J')
        return false;
    for (size_t i = 0; i < strlen(act); i++)
        act[i] = toupper(act[i]);
    if (!strcmp(act, "ON") && !strcmp(act, "OFF"))
        return false;
    return true;
}

void print(short state)
{
    for (int i = 0; i < 10; i++)
        cout << setw(4) << setfill(' ') << left << (char)(i + 'A');
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        if (state & (1 << i))
            cout << "ON  ";
        else
            cout << "OFF ";
    }
    cout << endl;
}

int main()
{
    short Switch = 0x0000;

    cout << "初始状态: 0x" << hex << uppercase << setw(4) << setfill('0') << right << Switch << dec << endl;
    print(Switch);
    cout << endl;

    while (true)
    {
        cout << "请以(\" A On / J Off \"形式输入，输入\" Q on / off \"退出)" << endl;
        char chr = 'A', act[10];
        cin >> chr >> act;

        if (!getInput(chr, act))
            continue;

        if (chr == 'Q')
            break;
        for (size_t i = 0; i < strlen(act); i++)
            act[i] = toupper(act[i]);
        int pos = chr - 'A';
        if (!strcmp(act, "ON"))
            Switch = Switch | (1 << pos);
        else
            Switch = Switch & ~(1 << pos);

        cout << "当前状态: 0x" << hex << uppercase << setw(4) << setfill('0') << right << Switch << dec << endl;
        print(Switch);
        cout << endl;
    }

    return 0;
}