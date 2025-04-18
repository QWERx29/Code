#include<iostream>
#include<cmath>
using namespace std;

double _1(double a, double b)
{
	double t = -b / (2 * a);
	return fabs(t) < 1e-6 ? 0 : t;
}