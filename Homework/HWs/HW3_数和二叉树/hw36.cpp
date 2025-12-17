#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution
{
private:
    string preorder, inorder;
    unordered_map<char, int> inorder_index;
    bool buildPostOrder(int pre_start, int in_start, int in_end, string &post)
    {
        if (in_start > in_end)
            return true;

        char root = preorder[pre_start];
        if (inorder_index.find(root) == inorder_index.end())
            return false;

        int root_index = inorder_index[root];
        if (root_index < in_start || root_index > in_end)
            return false;

        int left_size = root_index - in_start;
        int right_size = in_end - root_index;

        string left_post, right_post;

        if (left_size > 0)
            if (!buildPostOrder(pre_start + 1, in_start, root_index - 1, left_post))
                return false;
        if (right_size > 0)
        {
            if (!buildPostOrder(pre_start + 1 + left_size, root_index + 1, in_end, right_post))
                return false;
        }
        post = left_post + right_post + root;
        return true;
    }

public:
    string getPostOrder(string pre, string in)
    {
        preorder = pre;
        inorder = in;
        if (pre.length() != in.length())
            return "Error";
        inorder_index.clear();
        for (int i = 0; i < in.length(); i++)
        {
            if (inorder_index.find(in[i]) != inorder_index.end())
                return "Error";
            inorder_index[in[i]] = i;
        }

        string postorder;
        if (buildPostOrder(0, 0, in.length() - 1, postorder))
            return postorder;
        else
            return "Error";
    }
};

int main()
{
    string pre, in;
    Solution solver;

    while (cin >> pre >> in)
        cout << solver.getPostOrder(pre, in) << endl;

    return 0;
}