#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> t(n + 1);             // 课程学时
    vector<vector<int>> graph(n + 1); // 课程依赖图
    vector<int> inDegree(n + 1, 0);   // 入度
    vector<int> outDegree(n + 1, 0);  // 出度

    // 读入数据
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i];
        int ci;
        cin >> ci;
        for (int j = 0; j < ci; j++)
        {
            int pre;
            cin >> pre;
            graph[pre].push_back(i); // pre -> i 的依赖关系
            inDegree[i]++;
            outDegree[pre]++;
        }
    }

    // 计算最早完成时间
    vector<int> earliest(n + 1, 0);
    vector<int> tempInDegree = inDegree;
    queue<int> q;

    // 初始化：没有前置课程的课程
    for (int i = 1; i <= n; i++)
    {
        if (tempInDegree[i] == 0)
        {
            earliest[i] = t[i];
            q.push(i);
        }
    }

    // 拓扑排序计算最早完成时间
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (int next : graph[curr])
        {
            earliest[next] = max(earliest[next], earliest[curr] + t[next]);
            tempInDegree[next]--;
            if (tempInDegree[next] == 0)
            {
                q.push(next);
            }
        }
    }

    // 计算整个毕业的最短时间（关键路径长度）
    int graduationTime = 0;
    for (int i = 1; i <= n; i++)
    {
        graduationTime = max(graduationTime, earliest[i]);
    }

    // 计算最晚完成时间，用于判断关键路径
    vector<int> latest(n + 1, graduationTime);
    vector<int> tempOutDegree = outDegree;
    queue<int> q2;

    // 初始化：没有后继课程的课程
    for (int i = 1; i <= n; i++)
    {
        if (tempOutDegree[i] == 0)
        {
            q2.push(i);
        }
    }

    // 反向拓扑排序计算最晚完成时间
    while (!q2.empty())
    {
        int curr = q2.front();
        q2.pop();

        // 找到所有前驱课程
        for (int i = 1; i <= n; i++)
        {
            for (int next : graph[i])
            {
                if (next == curr)
                {
                    latest[i] = min(latest[i], latest[curr] - t[curr]);
                    tempOutDegree[i]--;
                    if (tempOutDegree[i] == 0)
                    {
                        q2.push(i);
                    }
                }
            }
        }
    }

    // 输出结果
    for (int i = 1; i <= n; i++)
    {
        // 判断是否在关键路径上
        int isCritical = (earliest[i] == latest[i]) ? 1 : 0;
        cout << earliest[i] << " " << isCritical << endl;
    }

    return 0;
}