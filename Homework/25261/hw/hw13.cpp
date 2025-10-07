#include <iostream>
#include <vector>
#include <algorithm>
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
    Term *head;

public:
    Polynomial() : head(nullptr) {}
    ~Polynomial()
    {
        clear();
    }
    void clear()
    {
        Term *current = head;
        while (current != nullptr)
        {
            Term *temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
    void insert(int coe, int exp)
    {
        if (coe == 0)
            return;
        Term *newTerm = new Term(coe, exp);
        if (head == nullptr || exp < head->exp)
        {
            newTerm->next = head;
            head = newTerm;
            return;
        }
        Term *current = head;
        Term *prev = nullptr;
        while (current != nullptr && current->exp < exp)
        {
            prev = current;
            current = current->next;
        }
        if (current != nullptr && current->exp == exp)
        {
            current->coe += coe;
            delete newTerm;
            if (current->coe == 0)
            {
                if (prev == nullptr)
                    head = current->next;
                else
                    prev->next = current->next;
                delete current;
            }
            return;
        }
        if (prev == nullptr)
        {
            newTerm->next = head;
            head = newTerm;
        }
        else
        {
            newTerm->next = current;
            prev->next = newTerm;
        }
    }
    Polynomial add(const Polynomial &other) const
    {
        Polynomial result;
        Term *p1 = this->head;
        Term *p2 = other.head;

        while (p1 != nullptr && p2 != nullptr)
        {
            if (p1->exp == p2->exp)
            {
                int sum = p1->coe + p2->coe;
                if (sum != 0)
                    result.insert(sum, p1->exp);
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (p1->exp < p2->exp)
            {
                result.insert(p1->coe, p1->exp);
                p1 = p1->next;
            }
            else
            {
                result.insert(p2->coe, p2->exp);
                p2 = p2->next;
            }
        }
        while (p1 != nullptr)
        {
            result.insert(p1->coe, p1->exp);
            p1 = p1->next;
        }
        while (p2 != nullptr)
        {
            result.insert(p2->coe, p2->exp);
            p2 = p2->next;
        }
        return result;
    }
    Polynomial multiply(const Polynomial &other) const
    {
        Polynomial result;
        for (Term *p1 = this->head; p1 != nullptr; p1 = p1->next)
        {
            for (Term *p2 = other.head; p2 != nullptr; p2 = p2->next)
            {
                int coeff = p1->coe * p2->coe;
                int exp = p1->exp + p2->exp;
                result.insert(coeff, exp);
            }
        }
        return result;
    }
    void buildFromInput(int termCount)
    {
        clear();
        for (int i = 0; i < termCount; i++)
        {
            int coe, exp;
            cin >> coe >> exp;
            insert(coe, exp);
        }
    }
    void print() const
    {
        if (head == nullptr)
            return;
        Term *current = head;
        bool first = true;
        while (current != nullptr)
        {
            if (current->coe != 0)
            {
                if (!first)
                    cout << " ";
                cout << current->coe << " " << current->exp;
                first = false;
            }
            current = current->next;
        }
        cout << endl;
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
        Polynomial result = poly1.add(poly2);
        result.print();
    }
    else if (operation == 1)
    {
        Polynomial result = poly1.multiply(poly2);
        result.print();
    }
    else if (operation == 2)
    {
        Polynomial addResult = poly1.add(poly2);
        Polynomial mulResult = poly1.multiply(poly2);
        addResult.print();
        mulResult.print();
    }
    return 0;
}