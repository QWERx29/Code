#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
    string s;
    cin >> s;

    int n = s.length();
    int max_len = 0;
    int start_pos = 0;

    stack<int> st;
    st.push(-1);
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(')
            st.push(i);
        else
        {
            st.pop();
            if (st.empty())
                st.push(i);
            else
            {
                int current_len = i - st.top();
                if (current_len > max_len)
                {
                    max_len = current_len;
                    start_pos = st.top() + 1;
                }
            }
        }
    }
    if (n == 0)
    {
        max_len = 0;
        start_pos = 0;
    }
    cout << max_len << " " << start_pos << endl;
    return 0;
}