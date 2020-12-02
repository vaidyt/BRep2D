#ifndef VECTOR_H
#define VECTOR_H

#include <string>

class Point;

// Vector.h
namespace Geometry
{
	using namespace std;
	
	class Vector
	{
	private:
		double x, y, z;

	public:
		Vector(double vx, double vy, double vz = 0.0);
		Vector(const Vector& v);
		Vector(const Point& p);
		double getLength() const;
		void normalize();
		Vector getNormalized() const;
		double dot(Vector rhs) const;
		Vector cross(Vector v2) const;
		Vector operator+(Vector rhs) const;
		Vector operator-(Vector rhs) const;
		Vector operator/(double scalar) const;
		double getX() const;
		double getY() const;
		double getZ() const;
		std::string toString() const;
		Vector operator*(double scalar) const;
	};


	inline Vector operator*(double scalar, const Vector& v)
	{
		return v * scalar;
	}


}

#endif