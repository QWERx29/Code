#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 1005;

vector<int> tree[MAXN];
int parent[MAXN];
int depth[MAXN];

void buildTree(int n)
{
    // 初始化
    for (int i = 1; i <= n; i++)
        tree[i].clear();
    memset(parent, 0, sizeof(parent));
    memset(depth, 0, sizeof(depth));
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        parent[b] = a;
        tree[a].push_back(b);
    }
    int root = 0;
    for (int i = 1; i <= n; i++)
    {
        if (parent[i] == 0)
        {
            root = i;
            break;
        }
    }

    vector<int> stack;
    stack.push_back(root);
    depth[root] = 1;

    while (!stack.empty())
    {
        int node = stack.back();
        stack.pop_back();
        for (int child : tree[node])
        {
            depth[child] = depth[node] + 1;
            stack.push_back(child);
        }
    }
}

int findLCA(int x, int y)
{
    while (depth[x] > depth[y])
        x = parent[x];
    while (depth[y] > depth[x])
        y = parent[y];
    while (x != y)
    {
        x = parent[x];
        y = parent[y];
    }

    return x;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int Ni, Mi;
        cin >> Ni >> Mi;
        buildTree(Ni);
        for (int i = 0; i < Mi; i++)
        {
            int x, y;
            cin >> x >> y;
            cout << findLCA(x, y) << endl;
        }
    }

    return 0;
}