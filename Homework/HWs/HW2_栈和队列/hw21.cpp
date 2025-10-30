#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool check(const string &input, const string &output)
{
    stack<char> st;
    int i = 0, j = 0;
    int n = input.length();
    int m = output.length();

    if (n != m)
        return false;

    while (i < n || !st.empty())
    {
        if (!st.empty() && st.top() == output[j])
        {
            st.pop();
            j++;
        }
        else if (i < n)
        {
            st.push(input[i]);
            i++;
        }
        else
            return false;
    }

    return j == m;
}

int main()
{
    string input, output;
    cin >> input;
    while (cin >> output)
    {
        if (check(input, output))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}