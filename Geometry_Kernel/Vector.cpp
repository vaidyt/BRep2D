#include <iostream>
#include "Point.h"
#include "Vector.h"
#include <string>

namespace Geometry
{

	Vector::Vector(double vx, double vy, double vz)
	{
		x = vx;
		y = vy;
		z = vz;
	}

	Vector::Vector(const Vector& v)
	{
		x = v.getX();
		y = v.getY();
		z = v.getZ();
	}

	Vector::Vector(const Point& p)
	{
		x = p.getX();
		y = p.getY();
		z = p.getZ();
	}

	double Vector::getLength() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Vector::normalize()
	{
		*this = *this / getLength();
	}

	Vector Vector::getNormalized() const
	{
		return *this / getLength();
	}

	double Vector::dot(Vector rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector Vector::operator+(Vector rhs) const
	{
		const Vector v(x + rhs.x, y + rhs.y, z + rhs.z);
		return v;
	}

	Vector Vector::operator-(Vector rhs) const
	{
		const Vector v(x - rhs.x, y - rhs.y, z - rhs.z);
		return v;
	}

	Vector Vector::operator/(double scalar) const
	{
		const Vector v(x / scalar, y / scalar, z / scalar);
		return v;
	}

	double Vector::getX() const
	{
		return x;
	}

	double Vector::getY() const
	{
		return y;
	}

	double Vector::getZ() const
	{
		return z;
	}

	Vector Vector::cross(Vector v2) const
	{
		auto v1x = getX();
		auto v1y= getY();
		auto v1z = getZ();

		auto v2x = v2.getX();
		auto v2y = v2.getY();
		auto v2z = v2.getZ();

		auto v3x = v1y * v2z - v2y * v1z;
		auto v3y = -(v1x * v2z - v2x * v1z);
		auto v3z = v1x * v2y - v2x * v1y;

		Vector v3(v3x, v3y, v3z);
		return v3;
	}

	Vector Vector::operator*(double scalar) const
	{
		const Vector resultVector(scalar * getX(), scalar * getY(), scalar * getZ());
		return resultVector;
	}

	string Vector::toString() const
	{
		return "Vx = " + std::to_string(x) + "Vy = " + std::to_string(y) + "Vz = " + std::to_string(z);
	}

}