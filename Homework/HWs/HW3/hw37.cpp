#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cmath>
#include <functional>
using namespace std;

struct TreeNode
{
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

int getPriority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPostfix(const string &infix)
{
    stack<char> st;
    string postfix;

    for (char c : infix)
    {
        if (isalpha(c))
            postfix += c;
        else if (c == '(')
            st.push(c);
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }
        else
        {
            while (!st.empty() && getPriority(st.top()) >= getPriority(c))
            {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty())
    {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

TreeNode *buildExpressionTree(const string &postfix)
{
    stack<TreeNode *> st;

    for (char c : postfix)
    {
        TreeNode *node = new TreeNode(c);

        if (isalpha(c))
            st.push(node);
        else
        {
            node->right = st.top();
            st.pop();
            node->left = st.top();
            st.pop();
            st.push(node);
        }
    }

    return st.top();
}

void postorderTraversal(TreeNode *root, string &result)
{
    if (!root)
        return;
    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result += root->val;
}

int evaluate(TreeNode *root, const map<char, int> &values)
{
    if (!root)
        return 0;

    if (isalpha(root->val))
        return values.at(root->val);
    int leftVal = evaluate(root->left, values);
    int rightVal = evaluate(root->right, values);

    switch (root->val)
    {
    case '+':
        return leftVal + rightVal;
    case '-':
        return leftVal - rightVal;
    case '*':
        return leftVal * rightVal;
    case '/':
        return leftVal / rightVal;
    default:
        return 0;
    }
}

int getHeight(TreeNode *root)
{
    if (!root)
        return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

void printTree(TreeNode *root)
{
    if (!root)
        return;

    int height = getHeight(root);
    int totalRows = 2 * height - 1;
    int totalCols = (1 << height) - 1;

    vector<vector<char>> grid(totalRows, vector<char>(totalCols, ' '));
    function<void(TreeNode *, int, int, int)> fillGrid = [&](TreeNode *node, int row, int col, int gap)
    {
        if (!node)
            return;
        grid[row][col] = node->val;

        if (node->left)
        {
            grid[row + 1][col - gap / 2] = '/';
            fillGrid(node->left, row + 2, col - gap, gap / 2);
        }

        if (node->right)
        {
            grid[row + 1][col + gap / 2] = '\\';
            fillGrid(node->right, row + 2, col + gap, gap / 2);
        }
    };
    int startCol = totalCols / 2;
    int initialGap = (1 << (height - 2));
    fillGrid(root, 0, startCol, initialGap);
    for (int i = 0; i < totalRows; i++)
    {
        string line;
        for (int j = 0; j < totalCols; j++)
            line += grid[i][j];
        while (!line.empty() && line.back() == ' ')
            line.pop_back();
        if (!line.empty())
            cout << line << endl;
    }
}

int main()
{
    string infix;
    int n;

    cin >> infix;
    cin >> n;

    map<char, int> values;
    for (int i = 0; i < n; i++)
    {
        char var;
        int value;
        cin >> var >> value;
        values[var] = value;
    }
    string postfix = infixToPostfix(infix);
    cout << postfix << endl;
    TreeNode *root = buildExpressionTree(postfix);
    printTree(root);
    int result = evaluate(root, values);
    cout << result << endl;

    return 0;
}