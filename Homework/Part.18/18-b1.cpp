// 2451317 ·ë¾Ãºã ´óÊý¾Ý 
#include "18-b1.h"
#include <iostream>
#include <cmath>

#define PI 3.14159
using namespace std;

// Circle
Circle::Circle(double radius) : r(radius) {}
void Circle::ShapeName() const
{
    cout << "Circle:" << endl;
}
double Circle::area() const
{
    if (r <= 0)
        return 0;
    return PI * r * r;
}

// Square
Square::Square(double sideLen) : side(sideLen) {}
void Square::ShapeName() const
{
    cout << "Square:" << endl;
}
double Square::area() const
{
    if (side <= 0)
        return 0;
    return side * side;
}

// Rectangle
Rectangle::Rectangle(double w, double h) : width(w), height(h) {}
void Rectangle::ShapeName() const
{
    cout << "Rectangle:" << endl;
}
double Rectangle::area() const
{
    if (width <= 0 || height <= 0)
        return 0;
    return width * height;
}

// Triangle
Triangle::Triangle(double a_, double b_, double c_)
    : a(a_), b(b_), c(c_) {}
void Triangle::ShapeName() const
{
    cout << "Triangle:" << endl;
}
double Triangle::area() const
{
    if (a <= 0 || b <= 0 || c <= 0)
        return 0;
    if (a + b <= c || a + c <= b || b + c <= a)
        return 0;
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// Trapezoid
Trapezoid::Trapezoid(double up, double low, double h)
    : upper(up), lower(low), height(h) {}
void Trapezoid::ShapeName() const
{
    cout << "Trapezoid:" << endl;
}
double Trapezoid::area() const
{
    if (upper <= 0 || lower <= 0 || height <= 0)
        return 0;
    return (upper + lower) * height / 2.0;
}
