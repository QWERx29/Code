#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

struct Node
{
    char val;
    Node *left, *right;
    Node(char c) : val(c), left(NULL), right(NULL) {}
};

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPostfix(const string &expr)
{
    stack<char> st;
    string postfix;
    for (int i = 0; i < (int)expr.size(); i++)
    {
        char c = expr[i];
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
            while (!st.empty() && priority(st.top()) >= priority(c))
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

Node *buildTree(const string &postfix)
{
    stack<Node *> st;
    for (int i = 0; i < (int)postfix.size(); i++)
    {
        char c = postfix[i];
        if (isalpha(c))
            st.push(new Node(c));
        else
        {
            Node *r = st.top();
            st.pop();
            Node *l = st.top();
            st.pop();
            Node *p = new Node(c);
            p->left = l;
            p->right = r;
            st.push(p);
        }
    }
    return st.top();
}

int height(Node *root)
{
    if (!root)
        return 0;
    int hl = height(root->left);
    int hr = height(root->right);
    return (hl > hr ? hl : hr) + 1;
}

void draw(Node *t, vector<string> &canvas, int depth, int l, int r)
{
    if (!t)
        return;
    int mid = (l + r) / 2;
    canvas[depth * 2][mid] = t->val;
    if (t->left)
    {
        canvas[depth * 2 + 1][mid - 1] = '/';
        draw(t->left, canvas, depth + 1, l, mid - 1);
    }
    if (t->right)
    {
        canvas[depth * 2 + 1][mid + 1] = '\\';
        draw(t->right, canvas, depth + 1, mid + 1, r);
    }
}

void drawTree(Node *root)
{
    int h = height(root);
    int w = (1 << h) - 1;
    vector<string> canvas(2 * h - 1, string(w, ' '));
    draw(root, canvas, 0, 0, w - 1);
    for (int i = 0; i < (int)canvas.size(); i++)
    {
        int end = (int)canvas[i].find_last_not_of(' ');
        if (end != string::npos)
            cout << canvas[i].substr(0, end + 1) << endl;
    }
}

int eval(Node *root, map<char, int> &val)
{
    if (!root)
        return 0;
    if (isalpha(root->val))
        return val[root->val];
    int L = eval(root->left, val);
    int R = eval(root->right, val);
    switch (root->val)
    {
    case '+':
        return L + R;
    case '-':
        return L - R;
    case '*':
        return L * R;
    case '/':
        return L / R;
    }
    return 0;
}

int main()
{
    string expr;
    getline(cin, expr);
    int n;
    cin >> n;
    map<char, int> val;
    for (int i = 0; i < n; i++)
    {
        char c;
        int x;
        cin >> c >> x;
        val[c] = x;
    }

    string postfix = infixToPostfix(expr);
    cout << postfix << endl;

    Node *root = buildTree(postfix);
    drawTree(root);

    cout << eval(root, val) << endl;
    return 0;
}
