// 2451317 冯久恒 计算机 
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void hanoi(int n, char src, char tmp, char dst) // n-层数;src-起始柱;tmp-中间柱;dst-目标柱
{
    static int cnt = 0;
    if (n == 1)
    {
        cnt++;
        cout << setw(5) << cnt << ": ";
        cout << setw(2) << n;
        cout << "# " << src << "-->" << dst << endl;
        return;
    }
    hanoi(n - 1, src, dst, tmp);
    cnt++;
    cout << setw(5) << cnt << ": ";
    cout << setw(2) << n;
    cout << "# " << src << "-->" << dst << endl;
    hanoi(n - 1, tmp, src, dst);
}

int main()
{
    int n;
    char src, dst, tmp;
    // Input n
    while (1)
    {
        cout << "请输入汉诺塔的层数(1-16)" << endl;
        cin >> n;
        if (cin.good() != 1 || (n < 1 || n > 16))
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
    cout << "移动步骤为:" << endl;
    hanoi(n, src, tmp, dst);
    return 0;
}