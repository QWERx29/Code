#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Term
{
    int coe; // 系数
    int exp; // 指数
    Term *next;

    Term(int c, int e) : coe(c), exp(e), next(nullptr) {}
};

class Polynomial
{
private:
    vector<Term> terms;

    void sortAndCombine() // 内部排序和合并同类项
    {
        if (terms.empty())
            return;
        // 按指数排序
        sort(terms.begin(), terms.end(), [](const Term &a, const Term &b)
             { return a.exp < b.exp; });
        // 合并同类项
        vector<Term> combined;
        int currentExp = terms[0].exp;
        int currentCoe = terms[0].coe;

        for (size_t i = 1; i < terms.size(); i++)
        {
            if (terms[i].exp == currentExp)
                currentCoe += terms[i].coe;
            else
            {
                if (currentCoe != 0)
                    combined.push_back(Term(currentCoe, currentExp));
                currentExp = terms[i].exp;
                currentCoe = terms[i].coe;
            }
        }
        // 添加最后一项
        if (currentCoe != 0)
            combined.push_back(Term(currentCoe, currentExp));
        terms = combined;
    }

public:
    Polynomial() = default;

    // 添加项
    void addTerm(int coefficient, int exponent)
    {
        if (coefficient != 0)
            terms.push_back(Term(coefficient, exponent));
    }

    // 多项式加法
    Polynomial operator+(const Polynomial &other) const
    {
        Polynomial result;
        map<int, int> expToCoeff;
        for (const auto &term : terms)
            expToCoeff[term.exp] += term.coe; // 添加当前多项式的所有项
        for (const auto &term : other.terms)
            expToCoeff[term.exp] += term.coe; // 添加另一个多项式的所有项
        for (const auto &pair : expToCoeff)
            if (pair.second != 0)
                result.terms.push_back(Term(pair.second, pair.first)); // 转换回vector，只保留非零项
        // 确保按指数排序
        sort(result.terms.begin(), result.terms.end(), [](const Term &a, const Term &b)
             { return a.exp < b.exp; });
        return result;
    }

    // 多项式乘法
    Polynomial operator*(const Polynomial &other) const
    {
        Polynomial result;
        map<int, int> expToCoeff;
        for (const auto &term1 : terms)
        {
            for (const auto &term2 : other.terms)
            {
                int coeff = term1.coe * term2.coe;
                int exp = term1.exp + term2.exp;
                expToCoeff[exp] += coeff;
            }
        }
        for (const auto &pair : expToCoeff)
            if (pair.second != 0)
                result.terms.push_back(Term(pair.second, pair.first)); // 转换回vector，只保留非零项
        sort(result.terms.begin(), result.terms.end(), [](const Term &a, const Term &b)
             { return a.exp < b.exp; }); // 确保按指数排序
        return result;
    }

    // 从输入构建多项式
    void buildFromInput(int termCount)
    {
        terms.clear();
        for (int i = 0; i < termCount; i++)
        {
            int coefficient, exponent;
            cin >> coefficient >> exponent;
            addTerm(coefficient, exponent);
        }
        sortAndCombine();
    }

    // 输出多项式
    void print() const
    {
        if (terms.empty())
            return; // 空多项式不输出
        bool first = true;
        for (const auto &term : terms)
        {
            if (term.coe != 0)
            {
                if (!first)
                    cout << " ";
                cout << term.coe << " " << term.exp;
                first = false;
            }
        }
        cout << endl;
    }

    // 检查是否为空多项式
    bool isEmpty() const
    {
        return terms.empty();
    }
};

int main()
{
    int m, n, operation;
    cin >> m;
    Polynomial poly1;
    poly1.buildFromInput(m);
    cin >> n;
    Polynomial poly2;
    poly2.buildFromInput(n);
    cin >> operation;
    if (operation == 0)
    {
        Polynomial result = poly1 + poly2;
        result.print();
    }
    else if (operation == 1)
    {
        Polynomial result = poly1 * poly2;
        result.print();
    }
    else if (operation == 2)
    {
        Polynomial addResult = poly1 + poly2;
        Polynomial mulResult = poly1 * poly2;
        addResult.print();
        mulResult.print();
    }
    return 0;
}