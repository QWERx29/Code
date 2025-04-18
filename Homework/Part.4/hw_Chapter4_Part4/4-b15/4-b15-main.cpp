#include<iostream>
#include<cmath>
using namespace std;
double calc_delta(double a, double b, double c);
double _1(double a, double b);
double _2(double a, double d);
void output(double a, double b, double c);
int main()
{
	double a, b, c;
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
	output(a, b, c);
	return 0;
}