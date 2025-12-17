#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cstring>

using namespace std;

class Graph
{
private:
    int n;
    vector<vector<int>> adj;

public:
    Graph(int n) : n(n)
    {
        adj.resize(n + 1);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int bfsCount(int start)
    {
        vector<bool> visited(n + 1, false);
        queue<int> q;
        int count = 1; // 包括自己
        int level = 0; // 当前层数
        visited[start] = true;
        q.push(start);
        while (!q.empty() && level < 6)
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                int current = q.front();
                q.pop();
                // 遍历当前节点的所有邻居
                for (int neighbor : adj[current])
                {
                    if (!visited[neighbor])
                    {
                        visited[neighbor] = true;
                        q.push(neighbor);
                        count++;
                    }
                }
            }
            level++;
        }
        return count;
    }
    void calculateSixDegrees()
    {
        for (int i = 1; i <= n; i++)
        {
            int reachable = bfsCount(i);
            float percentage = (float)reachable / n * 100;
            cout << i << ": " << fixed << setprecision(2) << percentage << "%" << endl;
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    graph.calculateSixDegrees();
    return 0;
}