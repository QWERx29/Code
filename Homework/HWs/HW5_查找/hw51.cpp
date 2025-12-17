#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<int> queries(m);
    for (int i = 0; i < m; i++)
        cin >> queries[i];
    vector<int> dp(n + 1, INT_MAX);

    dp[0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = n; j >= 1; j--)
            if (dp[j - 1] != INT_MAX)
                dp[j] = min(dp[j], dp[j - 1] + nums[i]);
    for (int i = 0; i < m; i++)
    {
        int query = queries[i];
        int left = 0, right = n, best = 0;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (dp[mid] <= query)
            {
                best = mid;
                left = mid + 1;
            }
            else
                right = mid - 1;
        }
        cout << best;
        if (i < m - 1)
            cout << " ";
    }
    cout << endl;

    return 0;
}