#pragma once

#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "Numerical.h"

using namespace std;


namespace  Geometry
{
	class Point;
	class Vector;
	
	class Ellipse
	{
	private:
		double a, b;
		double cX, cY;
		const double dt = Numerical::degreeToRadian(1);
		enum class Quadrant
		{
			First,
			Second,
			Third,
			Fourth
		};
		void getSweepParameters(Point& p, double& startParam, double& endParam) const;
		void getQuadrant(Point &p, Quadrant& q) const;
		
	public:
		Ellipse(double centerX, double centerY, double majorRadius, double minorRadius);
		double getMajorAxisRadius()  const;
		double getMinorAxisRadius()  const;
		bool getPointOnEllipse(Point& p, Vector& rayDirection, Point& nearestPt)  const;
		double distanceFromPt(Point& p, Point& nearestPt) const;
		string toString() const;
		bool isPointInside(const Point &p) const;
	};
}

#endif
