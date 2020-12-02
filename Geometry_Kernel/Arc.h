#pragma once

#ifndef _ARC_H
#define _ARC_H

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "LineSegment.h"

namespace Geometry
{
	class LineSegment;

	class InvalidMeshSize : public std::logic_error
	{
	public:
		InvalidMeshSize(std::string msg) : std::logic_error(msg) { };
	};

	class Arc : public ICurve
	{
	public:
		
		// Generic Arc constructor
		Arc(const Point& _p1, const Point& _p2, const Point& center);
		// Constructor for quarter-circle
		Arc(const Point& _p1, const Point& _p2);
		void Initialize();
		// Copy Constructor
		Arc(const Arc& q);

		// Getters
		Point getCenter() const;
		double getRadius() const;

		// Implementation of (pure) virtual functions
		Point P1() const override;
		Point P2() const override;
		double getLength() const override;
		CurveType getType() const override;
		bool isDegenerate() const override;
		bool isIntersecting(const ICurve&) const override;
		bool isIntersecting(const Arc& q, Point &p1, Point &p2) const;
		bool isIntersecting(const ICurve&, std::vector<Point>& intersectionPts) const override;
		void discretize(double d, std::vector<LineSegment>& q) const override;
		
		// Geometric query
		bool isPointOnBoundary(const Point& p) const;
		
		// Clone method
		virtual std::unique_ptr<ICurve> clone() const override;

		// Virtual Destructor
		virtual ~Arc() { ; }
	private:
		// Start and end point
		Point p1, p2;
		// Center of the arc
		Point m_center;
		// Radius of the arc
		double m_radius;
		// Parameteric - theta1 and theta2
		double m_t1, m_t2;
		
		// helper methods
		Point computeQuadrantCenter() const;
		double computeRadius() const;
		double computeTheta(const Point& p) const;
		void getPolarCoordinates(const Point& p, double& r, double& theta) const;
		void samplePoint(double theta, Point& p) const;
	};
}
#endif

