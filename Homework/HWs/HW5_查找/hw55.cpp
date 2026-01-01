#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 判断素数
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
// 获取大于等于n的最小素数
int getNextPrime(int n)
{
    while (!isPrime(n))
        n++;
    return n;
}
// 计算字符串的哈希值（使用unsigned long long自然溢出）
unsigned long long computeHash(const string &key)
{
    unsigned long long h = 0;
    for (char c : key)
        h = h * 37 + (unsigned long long)c;
    return h;
}

int main()
{
    int N, P;
    cin >> N >> P;
    int M = isPrime(P) ? P : getNextPrime(P);
    vector<int> hashTable(M, -1);
    vector<int> result(N);

    for (int i = 0; i < N; i++)
    {
        string name;
        cin >> name;
        unsigned long long hashValue = computeHash(name);
        int index = hashValue % M;

        bool inserted = false;
        // 平方探测法
        for (int k = 0; k <= M; k++)
        {
            int probeIndex;
            if (k == 0)
                probeIndex = index % M;
            else if (k % 2 == 1)
            {
                int offset = (k / 2 + 1) * (k / 2 + 1);
                probeIndex = (index + offset) % M;
            }
            else
            {
                int offset = (k / 2) * (k / 2);
                probeIndex = (index - offset) % M;
                if (probeIndex < 0)
                    probeIndex += M;
            }
            if (hashTable[probeIndex] == -1)
            {
                hashTable[probeIndex] = i;
                result[i] = probeIndex;
                inserted = true;
                break;
            }
        }

        if (!inserted)
            result[i] = -1;
    }

    for (int i = 0; i < N; i++)
    {
        if (result[i] == -1)
            cout << "-";
        else
            cout << result[i];
        if (i != N - 1)
            cout << " ";
    }
    cout << endl;

    return 0;
}