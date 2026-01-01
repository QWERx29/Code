#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 定义一个树节点结构
struct Person
{
    string name;
    Person *parent;
    vector<Person *> children;
    int depth; // 深度，用于表示缩进级别
};

// 解析家谱，建立树结构
void buildFamilyTree(vector<string> &treeLines, unordered_map<string, Person *> &people)
{
    // 第一行是最早的祖先
    Person *ancestor = new Person();
    ancestor->name = treeLines[0];
    ancestor->parent = NULL;
    ancestor->depth = 0;
    people[ancestor->name] = ancestor;
    // 栈用于保存当前路径
    vector<Person *> stack;
    stack.push_back(ancestor);
    // 处理剩余行
    for (int i = 1; i < treeLines.size(); i++)
    {
        string line = treeLines[i];
        // 计算缩进（空格数）
        int spaces = 0;
        while (spaces < line.length() && line[spaces] == ' ')
            spaces++;

        // 提取名字
        string name = line.substr(spaces);
        // 创建新节点
        Person *p = new Person();
        p->name = name;
        p->depth = spaces;
        // 找到父节点（栈中深度为spaces-1的节点）
        while (!stack.empty() && stack.back()->depth >= spaces)
            stack.pop_back();
        // 设置父节点和子节点关系
        Person *parent = stack.back();
        p->parent = parent;
        parent->children.push_back(p);
        people[name] = p;
        // 将新节点压入栈
        stack.push_back(p);
    }
}
// 检查是否是祖先关系
bool isAncestor(Person *a, Person *b)
{
    if (a == NULL || b == NULL)
        return false;
    Person *current = b;
    while (current != NULL)
    {
        if (current == a)
            return true;
        current = current->parent;
    }
    return false;
}

bool isDescendant(Person *a, Person *b)
{
    return isAncestor(b, a);
}
// 检查是否是兄弟关系（包括自己）
bool isSibling(Person *a, Person *b)
{
    if (a == NULL || b == NULL)
        return false;
    if (a == b)
        return true;
    return a->parent != NULL && b->parent != NULL && a->parent == b->parent;
}
// 检查是否是孩子关系
bool isChild(Person *child, Person *parent)
{
    if (child == NULL || parent == NULL)
        return false;
    return child->parent == parent;
}
// 检查是否是父母关系
bool isParent(Person *parent, Person *child)
{
    return isChild(child, parent);
}

int main()
{
    int n, m;

    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
            break;

        cin.ignore();

        vector<string> treeLines(n);
        for (int i = 0; i < n; i++)
            getline(cin, treeLines[i]);

        unordered_map<string, Person *> people;
        buildFamilyTree(treeLines, people);

        vector<string> results;

        for (int i = 0; i < m; i++)
        {
            string query;
            getline(cin, query);

            stringstream ss(query);
            string x, y, temp;
            vector<string> tokens;

            while (ss >> temp)
                tokens.push_back(temp);

            x = tokens[0];
            y = tokens[tokens.size() - 1];
            if (y.back() == '.')
                y.pop_back();

            string relation = "";
            if (tokens[2] == "a")
                relation = tokens[3];
            else if (tokens[2] == "the")
                relation = "parent";
            else if (tokens[2] == "an")
                relation = tokens[3];

            Person *px = people[x];
            Person *py = people[y];

            bool result = false;

            if (relation == "child")
                result = isChild(px, py);
            else if (relation == "parent")
                result = isParent(px, py);
            else if (relation == "sibling")
                result = isSibling(px, py);
            else if (relation == "descendant")
                result = isDescendant(px, py);
            else if (relation == "ancestor")
                result = isAncestor(px, py);

            results.push_back(result ? "True" : "False");
        }

        // 输出结果
        for (int i = 0; i < results.size(); i++)
            cout << results[i] << endl;
        cout << endl;

        unordered_map<string, Person *>::iterator it;
        for (it = people.begin(); it != people.end(); ++it)
            delete it->second;
    }

    return 0;
}