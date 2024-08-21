#include <bits/stdc++.h>
using namespace std;
void cmp(int x, int y, int z)
{
    if (x * x + y * y == z * z)
        cout << "Right triangle\n";
    else if (x * x + y * y < z * z)
        cout << "Obtuse triangle\n";
    else
        cout << "Acute triangle\n";
}
void db(int x, int y, int z)
{
    if (x == y || y == z)
        cout << "Isosceles triangle\n";
    if (x == y && y == z)
        cout << "Equilateral triangle\n";
}
int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    // if_tri
    if (a + b <= c || a + c <= b || b + c < a)
    {
        cout << "Not triangle";
        return 0;
    }
    else
    {
        int s[3];
        s[0] = a, s[1] = b, s[2] = c;
        sort(s, s + 3);
        cmp(s[0], s[1], s[2]);
        db(s[0], s[1], s[2]);
    }
}