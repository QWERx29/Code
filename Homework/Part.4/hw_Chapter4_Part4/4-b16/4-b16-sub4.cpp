#include<iostream>
#include<cmath>
#include "4-b16.h"
using namespace std;

void output(double a, double b, double c)
{
	double delta = calc_delta(a, b, c);
	if (delta == 0)
	{
		cout << "有两个相等实根：" << endl;
		cout << "x1=x2=" << _1(a, b) << endl;
	}
	else if (delta > 0)
	{
		if (fabs(_2(a, delta)) < 1e-6)
		{
			cout << "有两个相等实根：" << endl;
			cout << "x1=x2=" << _1(a, b) << endl;
		}
		else
		{
			cout << "有两个不等实根：" << endl;
			double t = _2(a, delta);
			if (t < 0)
				t = -t;
			cout << "x1=" << _1(a, b) + t << endl << "x2=" << _1(a, b) - t << endl;
		}
	}
	else
	{

		double t = _1(a, b), s = _2(a, -delta);
		if (fabs(s) < 1e-6)
		{
			cout << "有两个相等实根：" << endl;
			cout << "x1=x2=" << _1(a, b) << endl;
		}
		else
		{
			cout << "有两个虚根：" << endl;
			if (fabs(t) < 1e-6 || t == 0)
			{
				s = fabs(s);
				if (s == 1)
					cout << "x1=i" << endl << "x2=-i" << endl;
				else
					cout << "x1=" << s << "i" << endl << "x2=" << -s << "i" << endl;
			}
			else
			{
				s = fabs(s);
				if (s == 1)
					cout << "x1=" << t << "+i" << endl << "x2=" << t << " - i" << endl;
				else
					cout << "x1=" << t << "+" << s << "i" << endl << "x2=" << t << -s << "i" << endl;
			}
		}
	}
}