#include<iostream>
#include<cmath>
using namespace std;

double _2(double a, double d)
{
	double t = -sqrt(d) / (2 * a);
	return fabs(t) < 1e-6 ? 0 : t;
}
