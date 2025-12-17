#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

vector<int> topologicalSort(int k, vector<vector<int>> &conditions)
{
    vector<vector<int>> graph(k + 1);
    vector<int> indegree(k + 1, 0);

    // 构建图
    for (auto &cond : conditions)
    {
        int u = cond[0], v = cond[1];
        graph[u].push_back(v);
        indegree[v]++;
    }

    // 拓扑排序
    queue<int> q;
    for (int i = 1; i <= k; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> result;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (int v : graph[u])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    return result;
}

int main()
{
    int k, n, m;
    cin >> k >> n >> m;

    vector<vector<int>> rowConditions(n, vector<int>(2));
    vector<vector<int>> colConditions(m, vector<int>(2));

    for (int i = 0; i < n; i++)
    {
        cin >> rowConditions[i][0] >> rowConditions[i][1];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> colConditions[i][0] >> colConditions[i][1];
    }

    // 对行和列分别进行拓扑排序
    vector<int> rowOrder = topologicalSort(k, rowConditions);
    vector<int> colOrder = topologicalSort(k, colConditions);

    // 如果拓扑排序结果长度不等于k，说明有环，无法构造
    if (rowOrder.size() != k || colOrder.size() != k)
    {
        cout << -1 << endl;
        return 0;
    }

    // 创建映射：数字 -> 行位置，数字 -> 列位置
    vector<int> rowPos(k + 1), colPos(k + 1);
    for (int i = 0; i < k; i++)
    {
        rowPos[rowOrder[i]] = i;
        colPos[colOrder[i]] = i;
    }

    // 构造矩阵
    vector<vector<int>> matrix(k, vector<int>(k, 0));
    for (int num = 1; num <= k; num++)
    {
        int r = rowPos[num];
        int c = colPos[num];
        matrix[r][c] = num;
    }

    // 输出矩阵
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout << matrix[i][j];
            if (j < k - 1)
                cout << " ";
        }
        cout << endl;
    }

    return 0;
}