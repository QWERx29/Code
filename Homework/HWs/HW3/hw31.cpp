#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Node
{
    char val;
    Node *left, *right;
    Node(char v) : val(v), left(NULL), right(NULL) {}
};

void postorder(Node *root, string &res)
{
    if (root == NULL)
        return;
    postorder(root->left, res);
    postorder(root->right, res);
    res += root->val;
}

int main()
{
    int n;
    if (!(cin >> n))
        return 0;
    vector<string> ops(2 * n);
    for (int i = 0; i < 2 * n; ++i)
    {
        cin >> ws;
        getline(cin, ops[i]);
    }

    stack<Node *> st;
    Node *root = NULL;
    Node *lastPop = NULL;
    for (int i = 0; i < 2 * n; ++i)
    {
        string op = ops[i];
        if (op.size() >= 4 && op.substr(0, 4) == "push")
        {
            char c = op[op.size() - 1];
            Node *node = new Node(c);
            if (root == NULL)
                root = node;

            if (lastPop != NULL)
                lastPop->right = node;
            else if (!st.empty())
            {
                Node *top = st.top();
                if (top->left == NULL)
                    top->left = node;
                else
                    top->right = node;
            }
            st.push(node);
            lastPop = NULL;
        }
        else
        {
            if (!st.empty())
            {
                lastPop = st.top();
                st.pop();
            }
        }
    }

    string res;
    postorder(root, res);
    cout << res << endl;
    return 0;
}
