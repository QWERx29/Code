#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    int caseNo = 1;
    while (cin >> s)
    {
        if (s[0] == '#')
            break;
        int depth1 = 0, max1 = 0;
        int depth2 = 0, max2 = 0;
        char prev = 0;

        for (char c : s)
        {
            if (c == 'd')
            {
                depth1++;
                max1 = max(max1, depth1);

                if (prev == 'u')
                    depth2 += 2;
                else
                    depth2 += 1;
                max2 = max(max2, depth2);
            }
            else if (c == 'u')
            {
                depth1--;
                depth2--;
            }
            prev = c;
        }

        cout << "Tree " << caseNo++ << ": " << max1 << " => " << max2 << "\n\n";
    }
    return 0;
}
