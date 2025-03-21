#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s = "10111001";
    for (int i = 1; i <= 8; i++)
    {
        cout << s[i - 1] << " \\times 2^{-" << i << "} + ";
    }
}