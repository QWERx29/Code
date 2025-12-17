#include <iostream>
#include <climits>
using namespace std;

// 二叉排序树节点定义
struct BSTNode
{
    int key;        // 关键字
    int count;      // 该关键字出现的次数
    BSTNode *left;  // 左子树
    BSTNode *right; // 右子树

    BSTNode(int k) : key(k), count(1), left(nullptr), right(nullptr) {}
};

// 二叉排序树类
class BST
{
private:
    BSTNode *root;
    // 插入操作的辅助函数
    BSTNode *insert(BSTNode *node, int key)
    {
        if (node == nullptr)
            return new BSTNode(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            node->count++;
        return node;
    }
    // 删除操作的辅助函数
    BSTNode *remove(BSTNode *node, int key, bool &found)
    {
        if (node == nullptr)
            return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key, found);
        else if (key > node->key)
            node->right = remove(node->right, key, found);
        else
        {
            found = true;
            if (node->count > 1)
            {
                node->count--;
                return node;
            }
            if (node->left == nullptr)
            {
                BSTNode *rightChild = node->right;
                delete node;
                return rightChild;
            }
            else if (node->right == nullptr)
            {
                BSTNode *leftChild = node->left;
                delete node;
                return leftChild;
            }
            else
            {
                BSTNode *successor = findMinNode(node->right);
                node->key = successor->key;
                node->count = successor->count;
                successor->count = 1;
                node->right = remove(node->right, successor->key, found);
            }
        }
        return node;
    }
    // 查找最小节点
    BSTNode *findMinNode(BSTNode *node)
    {
        while (node != nullptr && node->left != nullptr)
            node = node->left;
        return node;
    }
    // 查找操作的辅助函数
    int searchCount(BSTNode *node, int key)
    {
        if (node == nullptr)
            return 0;
        if (key < node->key)
            return searchCount(node->left, key);
        else if (key > node->key)
            return searchCount(node->right, key);
        else
            return node->count;
    }
    // 查找最小值的辅助函数
    int findMinValue(BSTNode *node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node->key;
    }
    // 查找前驱的辅助函数
    int findPredecessor(BSTNode *node, int key)
    {
        int pred = INT_MIN;
        bool foundSmaller = false;
        while (node != nullptr)
        {
            if (node->key < key)
            {
                if (node->key > pred)
                {
                    pred = node->key;
                    foundSmaller = true;
                }
                node = node->right;
            }
            else
                node = node->left;
        }
        return foundSmaller ? pred : INT_MIN;
    }

public:
    BST() : root(nullptr) {}
    // 插入操作
    void insert(int key)
    {
        root = insert(root, key);
    }
    // 删除操作
    void remove(int key)
    {
        bool found = false;
        root = remove(root, key, found);
        if (!found)
            cout << "None" << endl;
    }
    // 查询某个整数的个数
    void queryCount(int key)
    {
        int count = searchCount(root, key);
        cout << count << endl;
    }
    // 查询最小值
    void queryMin()
    {
        if (root == nullptr)
        {
            cout << "None" << endl;
            return;
        }
        int minValue = findMinValue(root);
        cout << minValue << endl;
    }
    // 查询前驱
    void queryPredecessor(int key)
    {
        int pred = findPredecessor(root, key);
        if (pred == INT_MIN)
            cout << "None" << endl;
        else
            cout << pred << endl;
    }
};

int main()
{
    BST bst;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int x;
            cin >> x;
            bst.insert(x);
        }
        else if (op == 2)
        {
            int x;
            cin >> x;
            bst.remove(x);
        }
        else if (op == 3)
        {
            int x;
            cin >> x;
            bst.queryCount(x);
        }
        else if (op == 4)
        {
            bst.queryMin();
        }
        else if (op == 5)
        {
            int x;
            cin >> x;
            bst.queryPredecessor(x);
        }
    }

    return 0;
}