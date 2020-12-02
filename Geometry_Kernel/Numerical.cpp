#include "Numerical.h"
#include "Vector.h"
#include "Point.h"
#include <cmath>

namespace Geometry
{
	bool Numerical::solveQuadratic(double q_a, double q_b, double q_c, double& s1, double& s2)
	{
		if (q_a == 0)
			return false;

		auto discriminant = (q_b * q_b - 4 * q_a * q_c);

		if (Numerical::isZero(discriminant))
			discriminant = 0;

		if (discriminant < 0)
		{
			return false;
		}

		discriminant = sqrt(discriminant);

		s1 = (-q_b + discriminant) / (2 * q_a);
		s2 = (-q_b - discriminant) / (2 * q_a);

		return true;
	}

	Vector Numerical::getUnitRay(double theta)
	{
		Vector v(cos(theta), sin(theta), 0);

		return v;
	}

	double Numerical::degreeToRadian( double degree )
	{
		return degree * pi / 180.0;
	}

	double Numerical::moduloAngle( double thetaInDegrees )
	{
		if (thetaInDegrees < 0)
			thetaInDegrees += 360;

		return thetaInDegrees;
	}

	double Numerical::radianToDegree(double radian)
	{
		return radian * 180.0 / pi;
		
	}

	bool Numerical::isZero(double val, double tol)
	{
		return abs(val - 0) <= tol;
	}

	bool Numerical::isEqual(double val1, double val2, double tol)
	{
		return Numerical::isZero(abs(val1 - val2), tol);
	}


	void Numerical::convertToPolar( Point &p, double &r, double &theta )
	{
		r = p.distanceToOrigin();
		theta = atan2(p.getY(), p.getX());
	}
}