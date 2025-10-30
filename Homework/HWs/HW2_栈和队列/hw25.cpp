#include <iostream>
#include <queue>
#include <deque>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    queue<int> q;     // 普通队列
    deque<int> max_q; // 单调递减辅助队列
    string cmd;

    while (cin >> cmd)
    {
        if (cmd == "enqueue")
        {
            int m;
            cin >> m;
            if ((int)q.size() == n)
            {
                cout << "Queue is Full\n";
                continue;
            }
            q.push(m);
            while (!max_q.empty() && max_q.back() < m)
                max_q.pop_back();
            max_q.push_back(m);
        }
        else if (cmd == "dequeue")
        {
            if (q.empty())
            {
                cout << "Queue is Empty\n";
                continue;
            }
            int front = q.front();
            q.pop();
            cout << front << "\n";
            if (!max_q.empty() && max_q.front() == front)
                max_q.pop_front();
        }
        else if (cmd == "max")
        {
            if (q.empty())
            {
                cout << "Queue is Empty\n";
            }
            else
            {
                cout << max_q.front() << "\n";
            }
        }
        else if (cmd == "quit")
        {
            bool first = true;
            while (!q.empty())
            {
                if (!first)
                    cout << " ";
                cout << q.front();
                q.pop();
                first = false;
            }
            cout << "\n";
            break;
        }
    }
    return 0;
}
