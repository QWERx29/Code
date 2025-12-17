#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli; // pair of (distance, node)

const ll INF = LLONG_MAX;

vector<ll> dijkstra(int start, const vector<vector<pair<int, int>>> &graph, int n)
{
    vector<ll> dist(n + 1, INF);
    dist[start] = 0;

    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        ll current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (current_dist > dist[u])
            continue;

        for (const auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    // 构建邻接表
    vector<vector<pair<int, int>>> graph(N + 1);

    for (int i = 0; i < M; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x].push_back({y, w});
        graph[y].push_back({x, w});
    }

    int H, R;
    cin >> H >> R;

    vector<int> grass_points(H);
    for (int i = 0; i < H; i++)
    {
        cin >> grass_points[i];
    }

    // 预处理所有有牧草的点到其他点的最短距离
    vector<vector<ll>> grass_dist(H);
    for (int i = 0; i < H; i++)
    {
        grass_dist[i] = dijkstra(grass_points[i], graph, N);
    }

    for (int j = 0; j < R; j++)
    {
        int start, end;
        cin >> start >> end;

        ll min_distance = INF;

        // 尝试所有可能的牧草点作为中间点
        for (int i = 0; i < H; i++)
        {
            if (grass_dist[i][start] != INF && grass_dist[i][end] != INF)
            {
                min_distance = min(min_distance, grass_dist[i][start] + grass_dist[i][end]);
            }
        }

        cout << min_distance << "\n";
    }

    return 0;
}