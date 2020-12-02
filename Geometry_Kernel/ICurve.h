#include "Point.h"

#pragma once

#ifndef _ICURVE_H
#define _ICURVE_H

#include <vector>
#include <memory>

namespace Geometry
{
	enum class CurveType
	{
		LineSegment,
		Arc,
	};

	class LineSegment;

	// Abstract base class (or Interface) for 2D Curves
	class ICurve
	{
	public:
		virtual Point P1() const = 0;
		virtual Point P2() const = 0;
		virtual double getLength() const = 0;
		virtual CurveType getType() const = 0;
		virtual bool isDegenerate() const = 0;
		virtual bool isIntersecting(const ICurve &) const = 0;
		virtual bool isIntersecting(const ICurve&c, std::vector<Point> &intersectionPts) const = 0;
		virtual std::unique_ptr<ICurve> clone() const = 0;
		virtual void discretize(double d, std::vector<LineSegment>& q) const = 0;
		
		// virtual destructor
		virtual ~ICurve() {};
	};
};

#endif
