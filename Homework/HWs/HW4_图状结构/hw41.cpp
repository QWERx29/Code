#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1005;

class Graph
{
private:
    int n;
    vector<int> adj[MAXN];
    bool visited[MAXN];

public:
    Graph(int n) : n(n)
    {
        memset(visited, false, sizeof(visited));
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void sortAdjLists()
    {
        for (int i = 0; i < n; i++)
            sort(adj[i].begin(), adj[i].end());
    }

    void dfs(int u, vector<int> &component)
    {
        visited[u] = true;
        component.push_back(u);
        for (int v : adj[u])
            if (!visited[v])
                dfs(v, component);
    }

    vector<vector<int>> dfsTraversal()
    {
        memset(visited, false, sizeof(visited));
        vector<vector<int>> components;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                vector<int> component;
                dfs(i, component);
                components.push_back(component);
            }
        }
        return components;
    }

    vector<vector<int>> bfsTraversal()
    {
        memset(visited, false, sizeof(visited));
        vector<vector<int>> components;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                vector<int> component;
                queue<int> q;
                visited[i] = true;
                q.push(i);
                component.push_back(i);
                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    for (int v : adj[u])
                    {
                        if (!visited[v])
                        {
                            visited[v] = true;
                            q.push(v);
                            component.push_back(v);
                        }
                    }
                }
                components.push_back(component);
            }
        }
        return components;
    }
};

// 输出连通分量
void print(const vector<vector<int>> &components)
{
    for (const auto &component : components)
    {
        cout << "{";
        for (int i = 0; i < component.size(); i++)
        {
            if (i > 0)
                cout << " ";
            cout << component[i];
        }
        cout << "}";
    }
}

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
    graph.sortAdjLists();

    vector<vector<int>> dfsComponents = graph.dfsTraversal();
    vector<vector<int>> bfsComponents = graph.bfsTraversal();
    print(dfsComponents);
    cout << endl;
    print(bfsComponents);
    cout << endl;

    return 0;
}