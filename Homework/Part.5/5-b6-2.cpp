/* 学号 姓名 班级 */
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int top[3], plate[3][10], cnt = 1;

void output(int n, char src, char dst)
{

    cout << "第" << setw(4) << cnt << " 步" << "(" << setw(2) << n << "): ";
    cout << src << "-->" << dst;
    top[dst - 'A']++;
    plate[src - 'A'][top[src - 'A']] = 0;
    plate[dst - 'A'][top[dst - 'A']] = n;

    top[src - 'A']--;
    for (int i = 0; i < 3; i++)
    {
        cout << " " << char(i + 'A') << ":";
        // cout << top[i];
        for (int j = 0; j < 10; j++)
        {
            if (plate[i][j] != 0 && top[i] != -1)
                cout << setw(2) << plate[i][j]; // cout << top[i] << " ";
            else
                cout << "  ";
        }
    }
    cnt++;
    cout << endl;
}
void hanoi(int n, char src, char tmp, char dst) // n-层数;src-起始柱;tmp-中间柱;dst-目标柱
{

    if (n == 1)
    {
        output(n, src, dst);
        return;
    }
    hanoi(n - 1, src, dst, tmp);
    output(n, src, dst);
    hanoi(n - 1, tmp, src, dst);
}

int main()
{
    int n;
    char src, dst, tmp;
    // Input n
    while (1)
    {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> n;
        if (cin.good() != 1 || (n < 1 || n > 10))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    // Input Source & Destination
    while (1)
    {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> src;
        src = toupper(src);
        if (cin.good() != 1 || (src < 'A' || src > 'C'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    while (1)
    {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> dst;
        dst = toupper(dst);
        if (cin.good() != 1 || (dst < 'A' || dst > 'C'))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (dst == src)
        {
            cout << "目标柱(" << dst << ")不能与起始柱(" << src << ")相同" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    for (int i = 'A'; i <= 'C'; i++)
    {
        if (i == src || i == dst)
            continue;
        tmp = i;
    }

    for (int i = 0; i < n; i++)
        plate[src - 'A'][i] = n - i;
    cout << "初始:               ";
    for (int i = 0; i < 3; i++)
    {
        cout << " " << char(i + 'A') << ":";
        top[i] = -1;
        for (int j = 0; j < 10; j++)
        {
            if (plate[i][j] != 0 || j < top[i])
                cout << setw(2) << plate[i][j];
            else
                cout << "  ";
        }
    }
    top[src - 'A'] = n - 1;
    cout << endl;
    // cout << "移动步骤为:" << endl;
    hanoi(n, src, tmp, dst);
    return 0;
}
