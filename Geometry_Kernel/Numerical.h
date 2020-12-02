#pragma once
#ifndef _NUMERICAL_H
#define _NUMERICAL_H

namespace Geometry
{
	const double pi = 3.14159265358979323846;

	class Vector;
	class Point;
	
	class Numerical
	{
	public:
		static bool solveQuadratic(double q_a, double q_b, double q_c, double& s1, double& s2);
		static Vector getUnitRay(double theta);
		static double degreeToRadian(double degree);
		static double radianToDegree(double radian);
		static void convertToPolar(Point& p, double& r, double& theta);
		static double moduloAngle(double thetaInDegrees);
		static bool isZero(double val, double tol = 1e-12);
		static bool isEqual(double val1, double val2, double tol = 1e-12);
	};
}

#endif
