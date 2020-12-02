#include <iostream>
#include "Vector.h"
#include "Point.h"

namespace Geometry
{
	Point::Point()
	{
		x = 0;
		y = 0;
		z = 0;
		m_isValid = true;
	}

	Point::Point(double x_co, double y_co, double z_co)
	{
		x = x_co;
		y = y_co;
		z = z_co;
		m_isValid = true;
	}
	Point::Point(const Point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		m_isValid = true;
	}
	Point::Point(const Vector& v)
	{
		x = v.getX();
		y = v.getY();
		z = v.getZ();
		m_isValid = true;
	}

	double Point::getX() const
	{
		return x;
	}

	double Point::getY() const
	{
		return y;
	}

	double Point::getZ() const
	{
		return z;
	}

	Point Point::operator -(const Point& p2) const
	{
		Point p(x - p2.getX(), y - p2.getY(), z - p2.getZ());
		return p;
	}

	Point Point::operator +(const Vector& p2) const
	{
		Vector v1(this->x, this->y);
		Vector v2(p2);
		Vector v = v1 + v2;
		Point p(v);

		return p;
	}

	bool Point::operator == (const Point& p2) const
	{
		return x == p2.x && y == p2.y && z == p2.z;
	}

	double Point::distanceToPt(Point& otherPt)
	{
		Point diffPt = *this - otherPt;

		return diffPt.distanceToOrigin();
	}

	double Point::distanceToOrigin() const
	{
		Vector v(x, y, z);
		return v.getLength();
	}

	void Point::Print() const
	{
		std::cout << toString() << std::endl;
	}

	string Point::toString() const
	{
		string s = "X = " + std::to_string(x) + " Y = " + std::to_string(y) + " Z = " + std::to_string(z);
		return s;
	}

	bool Point::isValid() const
	{
		return m_isValid;
	}

	void Point::setValidity(bool validity)
	{
		m_isValid = validity;
	}
}