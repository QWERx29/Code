// 2451317 ·ë¾Ãºã ¼ÆËã»ú
#pragma once

class point {
private:
	int x;
	int y;
public:
	int getx() const
	{
		return x;
	}
	int gety() const
	{
		return y;
	}
	void set(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

class triangle {
private:
	point p1;
	point p2;
	point p3;
public:
	double area()
	{
		int x1 = p1.getx(), y1 = p1.gety();
		int x2 = p2.getx(), y2 = p2.gety();
		int x3 = p3.getx(), y3 = p3.gety();

		double S = abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0;

		return (S > 0) ? S : -1;
	}

	triangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y)
	{
		p1.set(p1_x, p1_y);
		p2.set(p2_x, p2_y);
		p3.set(p3_x, p3_y);
	}
};
