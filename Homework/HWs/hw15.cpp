#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

class Cards
{
private:
    vector<pair<string, string>> deck; // 牌堆，pair<花色, 数字>
    map<string, int> numberValue;      // 数字到数值的映射

    // 初始化数字映射
    void initNumberMap()
    {
        numberValue["A"] = 1;
        for (int i = 2; i <= 10; i++)
            numberValue[to_string(i)] = i;
        numberValue["J"] = 11;
        numberValue["Q"] = 12;
        numberValue["K"] = 13;
    }
    // 获取牌的数值用于排序
    int getCardValue(const string &number)
    {
        return numberValue[number];
    }

public:
    Cards()
    {
        initNumberMap();
    }
    // 添加牌到底部
    void Append(const string &type, const string &number)
    {
        deck.push_back({type, number});
    }
    // 抽取某花色所有牌，排序后放到顶部
    void Extract(const string &type)
    {
        vector<pair<string, string>> extracted;
        vector<pair<string, string>> remaining;
        // 分离出指定花色的牌
        for (const auto &card : deck)
        {
            if (card.first == type)
                extracted.push_back(card);
            else
                remaining.push_back(card);
        }

        if (extracted.empty())
            return;

        // 按数字从小到大排序
        sort(extracted.begin(), extracted.end(),
             [this](const pair<string, string> &a, const pair<string, string> &b)
             {
                 return getCardValue(a.second) < getCardValue(b.second);
             });
        // 将排序后的牌放到顶部，剩余牌保持原顺序
        deck.clear();
        deck.insert(deck.end(), extracted.begin(), extracted.end());
        deck.insert(deck.end(), remaining.begin(), remaining.end());
    }
    // 反转牌堆
    void Revert()
    {
        reverse(deck.begin(), deck.end());
    }

    // 弹出顶部牌
    pair<bool, pair<string, string>> Pop()
    {
        if (deck.empty())
            return {false, {"", ""}};

        auto topCard = deck.front();
        deck.erase(deck.begin());
        return {true, topCard};
    }
    // 获取牌堆状态（从顶到底）
    vector<pair<string, string>> getDeck() const
    {
        return deck;
    }
    // 检查牌堆是否为空
    bool isEmpty() const
    {
        return deck.empty();
    }
};

int main()
{
    Cards cardDeck;
    int n;
    cin >> n;
    cin.ignore(); // 忽略换行符
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string command;
        ss >> command;
        if (command == "Append")
        {
            string type, number;
            ss >> type >> number;
            cardDeck.Append(type, number);
        }
        else if (command == "Extract")
        {
            string type;
            ss >> type;
            cardDeck.Extract(type);
        }
        else if (command == "Revert")
            cardDeck.Revert();
        else if (command == "Pop")
        {
            auto result = cardDeck.Pop();
            if (result.first)
                cout << result.second.first << " " << result.second.second << endl;
            else
                cout << "NULL" << endl;
        }
    }

    // 输出最终牌堆状态
    if (cardDeck.isEmpty())
        cout << "NULL" << endl;
    else
    {
        auto finalDeck = cardDeck.getDeck();
        for (const auto &card : finalDeck)
            cout << card.first << " " << card.second << endl;
    }
    return 0;
}