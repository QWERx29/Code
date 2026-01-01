/*
#include <map>
#include <stack>
using namespace std;
*/
class FreqStack
{
private:
    map<int, int> freq;
    map<int, stack<int>> group;
    int maxFreq;

public:
    FreqStack()
    {
        maxFreq = 0;
    }

    void push(int val)
    {
        // 更新频率
        int f = ++freq[val];
        // 将元素放入对应频率的栈中
        group[f].push(val);
        // 更新最大频率
        if (f > maxFreq)
            maxFreq = f;
    }

    int pop()
    {
        // 获取当前最大频率栈的栈顶元素
        int val = group[maxFreq].top();
        group[maxFreq].pop();
        // 更新该元素的频率
        freq[val]--;
        // 如果当前最大频率栈为空，则降低最大频率
        if (group[maxFreq].empty())
            maxFreq--;
        return val;
    }
};