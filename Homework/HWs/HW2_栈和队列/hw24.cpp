#include <iostream>
using namespace std;

class Solution
{
public:
    Solution() {}

private:
    bool dfs(bool *map, const int row, const int col, int loc)
    {
        if (map[loc] != true)
            return false;
        map[loc] = false;
        bool bo = false;

        int x = loc / col, y = loc % col, dir = 0;
        if (x > 0)
        {
            bo |= dfs(map, row, col, loc - col);
            dir++;
        }
        if (x < row - 1)
        {
            bo |= dfs(map, row, col, loc + col);
            dir++;
        }
        if (y > 0)
        {
            bo |= dfs(map, row, col, loc - 1);
            dir++;
        }
        if (y < col - 1)
        {
            bo |= dfs(map, row, col, loc + 1);
            dir++;
        }
        bo |= dir == 4;
        return bo;
    }

public:
    int solution(bool *map, int row, int col)
    {
        int ans = 0;
        for (int i = 0; i < row * col; i++)
            if (map[i] == 1 && dfs(map, row, col, i) == true)
                ans++;
        return ans;
    }
};

int main()
{
    Solution s;
    int row, col;
    cin >> row >> col;
    bool *map = new bool[row * col];

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            int t;
            cin >> t;
            map[i * col + j] = (t == 1);
        }
    }
    int ans = s.solution(map, row, col);
    delete[] map;
    cout << ans << endl;
    return 0;
}