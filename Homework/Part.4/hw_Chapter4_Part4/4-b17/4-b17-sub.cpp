#include<iostream>
#include<cmath>
using namespace std;

extern double a, b, c;

double calc_delta()
{
	return b * b - 4 * a * c;
}
double _1()
{
	double t = -b / (2 * a);
	return fabs(t) < 1e-6 ? 0 : t;
}
double _2()
{
	double d = fabs(calc_delta());
	double t = -sqrt(d) / (2 * a);
	return fabs(t) < 1e-6 ? 0 : t;
}
void output()
{
	double delta = calc_delta();
	if (delta == 0)
	{
		cout << "有两个相等实根：" << endl;
		cout << "x1=x2=" << _1() << endl;
	}
	else if (delta > 0)
	{
		if (fabs(_2()) < 1e-6)
		{
			cout << "有两个相等实根：" << endl;
			cout << "x1=x2=" << _1() << endl;
		}
		else
		{
			cout << "有两个不等实根：" << endl;
			double t = _2();
			if (t < 0)
				t = -t;
			cout << "x1=" << _1() + t << endl << "x2=" << _1() - t << endl;
		}
	}
	else
	{

		double t = _1(), s = _2();
		if (fabs(s) < 1e-6)
		{
			cout << "有两个相等实根：" << endl;
			cout << "x1=x2=" << _1() << endl;
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