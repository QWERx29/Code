#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    while (getline(cin, s))
    {
        if (s == "#")
            break;
        int sum = 0;
        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];
            int value;
            if (c == ' ')
                value = 0;
            else
                value = c - 'A' + 1;
            sum += (i + 1) * value;
        }
        cout << sum << endl;
    }
    return 0;
}
