#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 图的邻接矩阵表示
// 根据题目描述构建图：5个顶点，特定边不存在
const int N = 6; // 使用1-5的索引，0位置不使用
int graph[N][N] = {
    {0, 0, 0, 0, 0, 0}, // 索引0不使用
    {0, 0, 1, 1, 0, 1}, // 顶点1: 连接2,3,5
    {0, 1, 0, 1, 0, 1}, // 顶点2: 连接1,3,5
    {0, 1, 1, 0, 1, 1}, // 顶点3: 连接1,2,4,5
    {0, 0, 0, 1, 0, 1}, // 顶点4: 连接3,5
    {0, 1, 1, 1, 1, 0}  // 顶点5: 连接1,2,3,4
};

// 边的总数
const int EDGE_COUNT = 8;

// 存储找到的所有欧拉路径
vector<vector<int>> allPaths;

// 深度优先搜索寻找欧拉路径
void dfs(int current, vector<int> &path, bool visitedEdges[N][N], int edgeCount)
{
    // 如果已经访问了所有边，保存当前路径
    if (edgeCount == EDGE_COUNT)
    {
        allPaths.push_back(path);
        return;
    }

    // 按照节点递增顺序尝试所有可能的边
    for (int next = 1; next <= 5; next++)
    {
        // 检查是否有边，且边未被访问
        if (graph[current][next] == 1 && !visitedEdges[current][next])
        {
            // 标记边为已访问（无向图，双向标记）
            visitedEdges[current][next] = true;
            visitedEdges[next][current] = true;

            // 添加下一个顶点到路径
            path.push_back(next);

            // 递归搜索
            dfs(next, path, visitedEdges, edgeCount + 1);

            // 回溯：恢复状态
            path.pop_back();
            visitedEdges[current][next] = false;
            visitedEdges[next][current] = false;
        }
    }
}

// 输出所有找到的欧拉路径
void printAllPaths()
{
    cout << "所有可能的欧拉路径（一笔画）：" << endl;
    cout << "==============================" << endl;

    for (size_t i = 0; i < allPaths.size(); i++)
    {
        cout << "路径 " << i + 1 << ": ";
        for (int vertex : allPaths[i])
        {
            cout << vertex;
        }
        cout << endl;
    }

    cout << "总共找到 " << allPaths.size() << " 条路径" << endl;
}

int main()
{
    // 初始化访问标记数组
    bool visitedEdges[N][N] = {false};

    // 初始化路径：从顶点1开始
    vector<int> path;
    path.push_back(1);

    // 开始深度优先搜索
    dfs(1, path, visitedEdges, 0);

    // 输出所有找到的路径
    printAllPaths();

    return 0;
}
/*
算法复杂度分析
时间复杂度
最坏情况时间复杂度：O(n!)，其中n是顶点数

对于有n个顶点的完全图，欧拉路径的数量与顶点的排列有关

在实际图中，由于边的限制，搜索空间会小很多

本题目中，实际搜索的复杂度远低于理论最坏情况

实际复杂度分析：

顶点数：5个

边数：8条

每次递归分支数：当前顶点的未访问边数

递归深度：最多9（8条边对应9个顶点）

总搜索空间大小与图的特定结构相关

空间复杂度
递归栈空间：O(E)，其中E是边数

递归深度最多为边数+1

本题目中最大深度为9

存储空间：

路径存储：O(V)，其中V是顶点数

边访问标记：O(V?)

结果存储：O(K×L)，其中K是路径数，L是平均路径长度

程序说明
图表示：使用邻接矩阵存储图结构，其中1表示有边，0表示无边。

深度优先搜索(DFS)：

从顶点1开始搜索

按照顶点编号递增顺序尝试所有可能的边

使用回溯法确保每条边只访问一次

当访问完所有边时，保存当前路径

关键特性：

严格按照题目要求从顶点1开始

按照节点递增顺序尝试

确保每条边恰好只画一次

使用回溯法找到所有可能的欧拉路径

输出结果：
程序会输出所有找到的欧拉路径，包括题目中示例的"123153452"。

这个实现完全满足实验要求，使用深度优先搜索遍历所有可能的路径，通过回溯确保每条边只访问一次，并按照题目要求输出所有可能的欧拉路径。
*/