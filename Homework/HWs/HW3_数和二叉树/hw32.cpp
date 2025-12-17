#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node
{
    char data;
    int left, right;
};

// 找根结点
int findRoot(vector<Node> &tree, int n)
{
    if (n == 0)
        return -1;
    vector<int> isChild(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (tree[i].left != -1)
            isChild[tree[i].left] = 1;
        if (tree[i].right != -1)
            isChild[tree[i].right] = 1;
    }
    for (int i = 0; i < n; i++)
        if (!isChild[i])
            return i;
    return -1;
}

// 计算深度
int depth(vector<Node> &tree, int root)
{
    if (root == -1)
        return 0;
    return 1 + max(depth(tree, tree[root].left), depth(tree, tree[root].right));
}

// 判断同构
bool isomorphic(vector<Node> &T1, int r1, vector<Node> &T2, int r2)
{
    if (r1 == -1 && r2 == -1)
        return true;
    if ((r1 == -1) ^ (r2 == -1))
        return false;
    if (T1[r1].data != T2[r2].data)
        return false;

    bool noSwap = isomorphic(T1, T1[r1].left, T2, T2[r2].left) && isomorphic(T1, T1[r1].right, T2, T2[r2].right);
    bool swapped = isomorphic(T1, T1[r1].left, T2, T2[r2].right) && isomorphic(T1, T1[r1].right, T2, T2[r2].left);
    return noSwap || swapped;
}

int main()
{
    int N1, N2;
    cin >> N1;
    vector<Node> T1(N1);
    for (int i = 0; i < N1; i++)
    {
        string l, r;
        cin >> T1[i].data >> l >> r;
        T1[i].left = (l == "-") ? -1 : stoi(l);
        T1[i].right = (r == "-") ? -1 : stoi(r);
    }

    cin >> N2;
    vector<Node> T2(N2);
    for (int i = 0; i < N2; i++)
    {
        string l, r;
        cin >> T2[i].data >> l >> r;
        T2[i].left = (l == "-") ? -1 : stoi(l);
        T2[i].right = (r == "-") ? -1 : stoi(r);
    }

    int root1 = findRoot(T1, N1);
    int root2 = findRoot(T2, N2);

    bool iso = isomorphic(T1, root1, T2, root2);
    int d1 = depth(T1, root1);
    int d2 = depth(T2, root2);

    cout << (iso ? "Yes" : "No") << endl;
    cout << d1 << endl;
    cout << d2 << endl;
    return 0;
}
