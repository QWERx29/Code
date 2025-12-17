#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

class UnionFind
{
private:
    vector<int> parent, rank;

public:
    UnionFind(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }
};

int main()
{
    int n;
    cin >> n;
    vector<Edge> edges;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int weight;
            cin >> weight;
            if (i < j)
                edges.push_back(Edge(i, j, weight));
        }
    }
    int m;
    cin >> m;
    UnionFind uf(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        uf.unite(a, b);
    }
    sort(edges.begin(), edges.end());

    int totalCost = 0;

    for (const Edge &edge : edges)
    {
        if (!uf.connected(edge.u, edge.v))
        {
            uf.unite(edge.u, edge.v);
            totalCost += edge.weight;
        }
    }

    cout << totalCost << endl;

    return 0;
}