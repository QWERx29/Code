#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a, b;
    char ch;
    cin >> a >> b >> ch;
    switch (ch)
    {
    case '+':
        cout << a + b;
        break;
    case '-':
        cout << a - b;
        break;
    case '*':
        cout << a * b;
        break;
    case '/':
        if (b == 0)
        {
            cout << "Divided by zero!";
            break;
        }
        else
        {
            cout << floor(a / b);
            break;
        }
    default:
        cout << "Invalid operator!";
        break;
    }
    return 0;
}