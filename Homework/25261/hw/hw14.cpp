#include <iostream>
#include <string>
#include <vector>
using namespace std;

string multiply(string num1, int num2)
{
    if (num2 == 0)
        return "0";
    string result = "";
    int carry = 0;
    for (int i = num1.length() - 1; i >= 0; i--)
    {
        int digit = num1[i] - '0';
        int product = digit * num2 + carry;
        result = char(product % 10 + '0') + result;
        carry = product / 10;
    }
    while (carry > 0)
    {
        result = char(carry % 10 + '0') + result;
        carry /= 10;
    }
    return result;
}
string add(string num1, string num2)
{
    string result = "";
    int carry = 0;
    int i = num1.length() - 1, j = num2.length() - 1;
    while (i >= 0 || j >= 0 || carry > 0)
    {
        int sum = carry;
        if (i >= 0)
            sum += num1[i--] - '0';
        if (j >= 0)
            sum += num2[j--] - '0';
        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
    }

    return result;
}
string calculate(int N, int A)
{
    if (A == 0)
        return "0";
    string sum = "0";
    string currentPower = "1";
    for (int i = 1; i <= N; i++)
    {
        currentPower = multiply(currentPower, A);
        string term = multiply(currentPower, i);
        sum = add(sum, term);
    }
    return sum;
}

int main()
{
    int N, A;
    while (cin >> N >> A)
    {
        string result = calculate(N, A);
        cout << result << endl;
    }
    return 0;
}