#pragma once
#ifndef LS_H
#define LS_H

// LineSegment.h
#include "Point.h"
#include "Vector.h"
#include "ICurve.h"
#include "Numerical.h"
#include "Arc.h"
#include <memory>

#include <stdexcept>

namespace Geometry
{
	class NotImplemented : public std::logic_error
	{
	public:
		NotImplemented(string msg) : std::logic_error(msg) { };
	};

	class DegenerateCircle : public std::logic_error
	{
	public:
		DegenerateCircle(string msg) : std::logic_error(msg) { };
	};

	class Arc;

	class LineSegment : public ICurve
	{
	private:
		// Start and end point
		Point p1, p2;
		// Position vectors of the point
		Vector v1, v2;
	public:
		// Constructor
		LineSegment(const Point& point1, const Point& point2);
		// Copy Constructor
		LineSegment(const LineSegment& l);

		// Getters
		double getLength() const;
		Vector getUnitVector() const;
		Vector getDirectionVector() const;

		// Implementation of (pure) virtual functions
		Point P1() const override;
		Point P2() const override;
		void Print() const;
		bool isDegenerate() const override;
		CurveType getType() const override;
		bool isIntersecting(const ICurve&) const override;
		bool isIntersecting(const ICurve&, std::vector<Point>& intersectionPts) const override;
		void discretize(double d, std::vector<LineSegment>& q) const override;

		// Other helper methods
		bool computeIntersection(const Geometry::ICurve& curve, Point& p1, Point& p2) const;
		double distanceFromPoint(const Point& p, bool extend = false) const;
		bool isIntersecting(const LineSegment& l2, Point& p) const;
		bool isIntersecting(const Arc& qc, Point& p1, Point& p2) const;
		bool isPointOnLineSegment(const Point& p) const;

		

		// Clone
		std::unique_ptr<ICurve> clone() const override;

		// Virtual Destructor
		virtual ~LineSegment() { ; }
	};
}
#endif