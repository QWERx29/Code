#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <sstream>

using namespace std;

class BoolEvaluator
{
private:
    int getPriority(char op)
    {
        if (op == '!')
            return 3;
        if (op == '&')
            return 2;
        if (op == '|')
            return 1;
        return 0;
    }
    bool apply(bool a, bool b, char op)
    {
        switch (op)
        {
        case '&':
            return a && b;
        case '|':
            return a || b;
        default:
            return false;
        }
    }
    bool applyU(bool a, char op)
    {
        if (op == '!')
            return !a;
        return a;
    }
    void process(stack<bool> &values, stack<char> &operators)
    {
        char op = operators.top();
        operators.pop();
        if (op == '!')
        {
            bool a = values.top();
            values.pop();
            values.push(applyU(a, op));
        }
        else
        {
            bool b = values.top();
            values.pop();
            bool a = values.top();
            values.pop();
            values.push(apply(a, b, op));
        }
    }

public:
    bool evaluate(const string &expression)
    {
        stack<bool> values;
        stack<char> operators;

        int i = 0;
        int n = expression.length();
        while (i < n)
        {
            if (isspace(expression[i]))
            {
                i++;
                continue;
            }
            if (expression[i] == 'V' || expression[i] == 'F')
            {
                values.push(expression[i] == 'V');
                i++;
                continue;
            }
            if (expression[i] == '(')
            {
                operators.push('(');
                i++;
                continue;
            }
            if (expression[i] == ')')
            {
                while (!operators.empty() && operators.top() != '(')
                {
                    process(values, operators);
                }
                operators.pop();
                i++;
                continue;
            }
            if (expression[i] == '!' || expression[i] == '&' || expression[i] == '|')
            {
                if (expression[i] == '!')
                {
                    int notCount = 0;
                    int j = i;
                    while (j < n && expression[j] == '!')
                    {
                        notCount++;
                        j++;
                    }
                    if (notCount % 2 == 1)
                    {
                        while (!operators.empty() && getPriority(operators.top()) >= getPriority('!'))
                        {
                            process(values, operators);
                        }
                        operators.push('!');
                    }
                    i = j;
                }
                else
                {
                    while (!operators.empty() && getPriority(operators.top()) >= getPriority(expression[i]))
                    {
                        process(values, operators);
                    }
                    operators.push(expression[i]);
                    i++;
                }
                continue;
            }
            i++;
        }
        while (!operators.empty())
        {
            process(values, operators);
        }
        return values.top();
    }
};

int main()
{
    BoolEvaluator evaluator;
    string line;
    int cnt = 0;
    while (getline(cin, line))
    {
        cnt++;
        bool result = evaluator.evaluate(line);
        cout << "Expression " << cnt << ": " << (result ? "V" : "F") << endl;
    }
    return 0;
}