// 2451317 ·ë¾Ãºã ´óÊý¾Ý 

#pragma once

class Shape
{
public:
    virtual void ShapeName() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() {}
};

// Circle
class Circle : public Shape
{
private:
    double r;

public:
    Circle(double radius);
    void ShapeName() const override;
    double area() const override;
};

// Square
class Square : public Shape
{
private:
    double side;

public:
    Square(double sideLen);
    void ShapeName() const override;
    double area() const override;
};

// Rectangle
class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h);
    void ShapeName() const override;
    double area() const override;
};

// Triangle
class Triangle : public Shape
{
private:
    double a, b, c;

public:
    Triangle(double a, double b, double c);
    void ShapeName() const override;
    double area() const override;
};

// Trapezoid
class Trapezoid : public Shape
{
private:
    double upper, lower, height;

public:
    Trapezoid(double up, double low, double h);
    void ShapeName() const override;
    double area() const override;
};
