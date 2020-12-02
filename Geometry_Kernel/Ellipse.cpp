#include "Point.h"
#include "Vector.h"
#include "Ellipse.h"
#include "Numerical.h"
#include "omp.h"

#include <algorithm>
#include <iostream>

namespace Geometry
{
	Ellipse::Ellipse(double centerX, double centerY, double majorRadius, double minorRadius) : cX(centerX), cY(centerY), a(majorRadius), b(minorRadius)
	{

	}
	double Ellipse::getMajorAxisRadius() const
	{
		return a;
	}
	double Ellipse::getMinorAxisRadius() const
	{
		return b;
	}


	bool Ellipse::getPointOnEllipse(Point& p, Vector& rayDirection, Point& nearestPt) const
	{
		const auto px = p.getX() - cX;
		const auto py = p.getY() - cY;
		const auto vx = rayDirection.getX();
		const auto vy = rayDirection.getY();

		const auto q_a = (vx * vx) / (a * a) + (vy * vy) / (b * b);
		const auto q_b = 2 * ((px * vx) / (a * a) + (py * vy) / (b * b));
		const auto q_c = (px * px) / (a * a) + (py * py) / (b * b) - 1;

		double s1 = 0.0;
		double s2 = 0.0;
		const auto isValidSol = Numerical::solveQuadratic(q_a, q_b, q_c, s1, s2);

		if (!isValidSol)
			return false;

		double t = 0;

		if (s1 >= 0 && s2 >= 0)
		{
			t = std::min(s1, s2);
		}
		else if (s1 >= 0)
		{
			t = s1;
		}
		else if (s2 >= 0)
		{
			t = s2;
		}
		else
		{
			return false;
		}

		nearestPt = p + t * rayDirection;

		return true;
	}

	void Ellipse::getQuadrant(Point& p, Quadrant& q) const
	{
		Point origin(this->cX, this->cY);
		Point relativePoint = p - origin;

		double r, theta;
		Numerical::convertToPolar(relativePoint, r, theta);
		double thetaInDegrees = Numerical::radianToDegree(theta);
		thetaInDegrees = Numerical::moduloAngle(thetaInDegrees);


		if (thetaInDegrees >= 0.0 && thetaInDegrees <= 90.0)
		{
			q = Quadrant::First;
		}
		else if (thetaInDegrees > 90.0 && thetaInDegrees <= 180.0)
		{
			q = Quadrant::Second;
		}
		else if (thetaInDegrees > 180.0 && thetaInDegrees <= 270.0)
		{
			q = Quadrant::Third;
		}
		else
		{
			q = Quadrant::Fourth;
		}


	}

	void Ellipse::getSweepParameters(Point& p, double& startParam, double& endParam) const
	{
		Quadrant q;

		getQuadrant(p, q);

		switch (q)
		{
		case Quadrant::First:
			startParam = Numerical::degreeToRadian(0.0);
			endParam = Numerical::degreeToRadian(90.0);
			break;
		case Quadrant::Second:
			startParam = Numerical::degreeToRadian(90.0);
			endParam = Numerical::degreeToRadian(180.0);
			break;
		case Quadrant::Third:
			startParam = Numerical::degreeToRadian(180.0);
			endParam = Numerical::degreeToRadian(270.0);
			break;
		case Quadrant::Fourth:
			startParam = Numerical::degreeToRadian(270.0);
			endParam = Numerical::degreeToRadian(360.0);
			break;
		}
	}



	double Ellipse::distanceFromPt(Point& p, Point& nearestPt) const
	{
		double minDistance = numeric_limits<double>::max();

		Point thisPt(0, 0, 0);

		double startParam = 0.0;
		double endParam = 2 * pi;

		// getSweepParameters(p, startParam, endParam);

		for (auto t = startParam; t <= endParam + dt / 2; t += dt)
		{
			Vector r = Numerical::getUnitRay(t);

			const auto isValidPt = getPointOnEllipse(p, r, thisPt);

			if (!isValidPt)
				continue;

			const double thisDist = p.distanceToPt(thisPt);

			// cout << "Shooting Ray -> " << r.toString() << std::endl;
			// cout << "t = " << Numerical::radianToDegree(t) << " Distance = " << thisDist << " Pt = " << thisPt.toString() << std::endl;

			if (thisDist < minDistance)
			{
				nearestPt = thisPt;
				minDistance = thisDist;
			}
		}

		return minDistance;
	}

	bool Ellipse::isPointInside(const Point &p) const
	{
		double x = p.getX();
		double y = p.getY();
		
		return ((x - cX) * (x - cX)) / (a * a) + ((y - cY) * (y - cY)) / (b * b) - 1 <= 0;
	}

	string Ellipse::toString() const
	{
		return "cX = " + std::to_string(cX) + " cY = " + std::to_string(cY) + " a = " + std::to_string(a) + " b = " + std::to_string(b);
	}

}
