#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    int amountOfTime(TreeNode *root, int start)
    {
        unordered_map<TreeNode *, TreeNode *> parent;
        TreeNode *startNode = nullptr;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            if (node->val == start)
                startNode = node;

            if (node->left)
            {
                parent[node->left] = node;
                q.push(node->left);
            }
            if (node->right)
            {
                parent[node->right] = node;
                q.push(node->right);
            }
        }
        unordered_map<TreeNode *, bool> visited;
        q.push(startNode);
        visited[startNode] = true;
        int minutes = -1;

        while (!q.empty())
        {
            int size = q.size();
            minutes++;

            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.front();
                q.pop();

                if (node->left && !visited[node->left])
                {
                    visited[node->left] = true;
                    q.push(node->left);
                }

                if (node->right && !visited[node->right])
                {
                    visited[node->right] = true;
                    q.push(node->right);
                }

                if (parent.find(node) != parent.end() && !visited[parent[node]])
                {
                    visited[parent[node]] = true;
                    q.push(parent[node]);
                }
            }
        }

        return minutes;
    }
};

TreeNode *buildTree(int n, vector<pair<int, int>> &children)
{
    vector<TreeNode *> nodes(n);
    for (int i = 0; i < n; i++)
        nodes[i] = new TreeNode(i);

    for (int i = 0; i < n; i++)
    {
        int left = children[i].first;
        int right = children[i].second;

        if (left != -1)
            nodes[i]->left = nodes[left];
        if (right != -1)
            nodes[i]->right = nodes[right];
    }

    return nodes[0];
}

int main()
{
    int n, start;
    cin >> n >> start;

    vector<pair<int, int>> children(n);
    for (int i = 0; i < n; i++)
    {
        int left, right;
        cin >> left >> right;
        children[i] = {left, right};
    }

    TreeNode *root = buildTree(n, children);
    Solution solution;
    int result = solution.amountOfTime(root, start);

    cout << result << endl;

    return 0;
}