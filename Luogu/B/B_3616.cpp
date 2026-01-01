#include <iostream>
using namespace std;

const int SIZE = 10000 + 5;

struct Queue
{
    int q[SIZE], ql, qr;

    Queue() : ql(1), qr(0) {}

    bool empty() { return ql > qr; }

    void push(int x) { q[++qr] = x; }

    void pop() { ++ql; }

    int front() { return q[ql]; }

    int back() { return q[qr]; }

    int size() { return qr - ql + 1; }

    int clear()
    {
        ql = 1;
        qr = 0;
    }
};

int main()
{
    Queue q;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            int x;
            cin >> x;
            q.push(x);
        }
        else if (opt == 2)
        {
            if (q.empty())
                cout << "ERR_CANNOT_POP\n";
            else
                q.pop();
        }
        else if (opt == 3)
        {
            if (q.empty())
                cout << "ERR_CANNOT_QUERY\n";
            else
                cout << q.front() << endl;
        }
        else
            cout << q.size() << endl;
    }
    return 0;
}

/* "双栈模拟队列"
#include <cstdio>
#include <stack>
using namespace std;

struct Queue
{
    stack<int> f, s;
    bool empty() { return f.empty() && s.empty(); }
    void push(int x) { f.push(x); }
    void pop()
    {
        if (s.empty())
            for (; !f.empty(); f.pop())
                s.push(f.top());
        s.pop();
    }
    int front()
    {
        if (s.empty())
            for (; !f.empty(); f.pop())
                s.push(f.top());
        return s.top();
    }
    int size() { return f.size() + s.size(); }
};

int main()
{
    Queue q;
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int opt;
        scanf("%d", &opt);
        if (opt == 1)
        {
            int x;
            scanf("%d", &x);
            q.push(x);
        }
        else if (opt == 2)
        {
            if (q.empty())
                printf("ERR_CANNOT_POP\n");
            else
                q.pop();
        }
        else if (opt == 3)
        {
            if (q.empty())
                printf("ERR_CANNOT_QUERY\n");
            else
                printf("%d\n", q.front());
        }
        else
            printf("%d\n", q.size());
    }
    return 0;
}
*/

/* STL
#include <iostream>
#include <queue>
using namespace std;

queue<int> q;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int code;
        cin >> code;
        if (code == 1)
        {
            int x;
            cin >> x;
            q.push(x);
        }
        else if (code == 2)
        {
            if (q.empty())
                cout << "ERR_CANNOT_POP" << endl;
            else
                q.pop();
        }
        else if (code == 3)
        {
            if (q.empty())
                cout << "ERR_CANNOT_QUERY" << endl;
            else
                cout << q.front() << endl;
        }
        else
            cout << q.size() << endl;
    }
    return 0;
}
*/