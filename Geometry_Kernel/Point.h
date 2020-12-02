#ifndef POINT_H

#define POINT_H

// Point.h
#include <string>

namespace Geometry
{
	class Vector;

	using namespace std;

	class Point
	{
	private:
		double x, y, z;
		bool m_isValid;

	public:
		Point();
		Point(double x_co, double y_co, double z_co = 0);
		Point(const Point& p);
		Point(const Vector& v);
		double getX() const;
		double getY() const;
		double getZ() const;
		Point operator -(const Point& p2) const;
		Point operator +(const Vector& p2) const;
		bool operator == (const Point& p2) const;
		double distanceToPt(Point& otherPt);
		double distanceToOrigin() const;
		void Print() const;
		bool isValid() const;
		void setValidity(bool);
		string toString() const;
	};
}
#endif