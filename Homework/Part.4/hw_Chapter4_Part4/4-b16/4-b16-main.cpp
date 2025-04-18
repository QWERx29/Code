#include<iostream>
#include<cmath>
#include "4-b16.h"
using namespace std;

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