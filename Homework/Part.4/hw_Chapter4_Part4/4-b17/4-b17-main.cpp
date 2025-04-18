#include<iostream>
#include<cmath>
using namespace std;
double a, b, c;
double calc_delta();
double _1();
double _2();
void output();
int main()
{
	cout << "请输入一元二次方程的三个系数a,b,c:" << endl;
	cin >> a >> b >> c;
	if (fabs(a) < 1e-6)
	{
		a = 0;
		cout << "不是一元二次方程" << endl;
		return  0;
	}
	if (fabs(b) < 1e-6)
		b = 0;
	if (fabs(c) < 1e-6)
		c = 0;
	output();
	return 0;
}