#include <bits/stdc++.h>
using namespace std;

int main()
{
    int caseNo = 1;
    while (1)
    {
        string s;
        getline(cin, s);
        if (s == "#")
            break;
        int depth1 = 0, max1 = 0;
        int depth2 = 0, max2 = 0;
        vector<pair<int, int>> stack;
        for (char c : s)
        {

            if (c == 'd')
            {
                depth1++;
                max1 = max(max1, depth1);

                depth2++;
                max2 = max(max2, depth2);
                stack.push_back({depth1, depth2});
            }
            else if (c == 'u')
            {
                depth1--;
                if (!stack.empty())
                {
                    depth2 = stack.back().second;
                    stack.pop_back();
                }
                else
                    depth2 = 0;
            }
        }
        cout << "Tree " << caseNo++ << ": " << max1 << " => " << max2 << endl;
    }
    return 0;
}