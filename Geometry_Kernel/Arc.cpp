#include "Arc.h"
#include <iostream>

namespace Geometry
{
	Arc::Arc(const Point& _p1, const Point& _p2, const Point& center)
	{
		m_center = center;
		Initialize();
	}

	// This constructor assumes that the arc is one of the
	// 4 quarter-circles i.e. computes the center by assuming 
	// the given points lie on a quadrant and then determines the
	// theta values (t1 and t2). So, If
	// 0 <= t <= pi/2 then first quadrant
	// p/2 <= t <= pi then second quadrant
	// pi <= t <= 3*pi/2 then third quadrant
	// 3*p/2 <= t <= 2*pi then fourth quadrant
	Arc::Arc(const Point& _p1, const Point& _p2) : p1(_p1), p2(_p2)
	{
		m_center = computeQuadrantCenter();
		Initialize();
	}

	void Arc::Initialize()
	{
		m_radius = computeRadius();
		m_t1 = computeTheta(P1());
		m_t2 = computeTheta(P2());

		if (m_t2 == 0)
		{
			m_t2 = 2 * pi;
		}
	}

	// Copy Constructor
	Arc::Arc(const Arc& q) : Arc(q.p1, q.p2, q.m_center)
	{
	}

	Point Arc::P1() const
	{
		return this->p1;
	}

	Point Arc::P2() const
	{
		return this->p2;
	}

	double Arc::getLength() const
	{
		return m_radius * (m_t2 - m_t1);
	}

	CurveType Arc::getType() const
	{
		return CurveType::Arc;
	}

	bool Arc::isDegenerate() const
	{
		return p1 == p2;
	}

	/// <summary>
	/// computes arc - arc intersection
	/// </summary>
	/// <param name="q">The other arc</param>
	/// <param name="p1">First point of intersection (valid only if p1.isValid() returns true)</param>
	/// <param name="p2">First point of intersection (valid only if p2.isValid() returns true)</param>
	/// <returns>true if the curves intersect and false otherwise</returns>
	bool Arc::isIntersecting(const Arc& q, Point& p1, Point& p2) const
	{
		Point P0 = this->getCenter();
		Point P1 = q.getCenter();
		auto r0 = this->getRadius();
		auto r1 = q.getRadius();

		Vector P1P2(P1 - P0);
		auto d = P1P2.getLength();

		if (d > r0 + r1 || d < abs(r0 - r1))
		{
			// No intersection - 0 points of intersection
			p1.setValidity(false);
			p2.setValidity(false);
			return false;
		}

		if (d == 0)
		{
			// Overlapping circles
			p1.setValidity(true);
			p2.setValidity(true);
			// return any 2 points on the arc

			p1 = this->P1();
			p2 = this->P2();

			if (!q.isPointOnBoundary(p1) || !this->isPointOnBoundary(p1))
			{
				p1.setValidity(false);
			}

			if (!q.isPointOnBoundary(p2) || !this->isPointOnBoundary(p2))
			{
				p2.setValidity(false);
			}

			return p1.isValid() || p2.isValid();
		}

		auto a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
		auto h = sqrt(r0 * r0 - a * a);
		Vector v(P1 - P0);
		Point P2(P0 + (a / d) * v);


		if (d == r0 + r1)
		{
			// Circles are just touching - so only 1 point of intersection
			p1 = P2;
			if (!isPointOnBoundary(p1))
			{
				p1.setValidity(false);
				p2.setValidity(false);
				return false;
			}
			else
			{
				p1.setValidity(true);
				p2.setValidity(false);
				return true;
			}
		}

		Vector perpV(v.getY(), v.getX());
		Point P3(P2 + (h / d) * perpV);
		Point P4(P2 - (h / d) * perpV);

		p1 = P3;
		p2 = P4;

		// The intersection points computed are for the full circle
		// So check if the intersection points actually
		// lie on the arc. If they do not lie on the arc,
		// then set isValid to false

		bool isIntersecting = true;
		p1.setValidity(true);
		p2.setValidity(true);

		if (!q.isPointOnBoundary(p1) || !this->isPointOnBoundary(p1))
		{
			p1.setValidity(false);
		}

		if (!q.isPointOnBoundary(p2) || !this->isPointOnBoundary(p2))
		{
			p2.setValidity(false);
		}

		return p1.isValid() || p2.isValid();
	}
	/// <summary>
	/// computes Arc Vs any other curve intersection
	/// </summary>
	/// <param name="curve">The test curve</param>
	/// <param name="intersectionPts">one or more intersection points</param>
	/// <returns>true if there is at least one intersection and false otherwise</returns>
	bool Arc::isIntersecting(const ICurve& curve, std::vector<Point>& intersectionPts) const
	{
		auto type = curve.getType();

		switch (type)
		{
		case CurveType::LineSegment:
		{
			return curve.isIntersecting(*this, intersectionPts);
		}
		case CurveType::Arc:
		{
			Arc* q = dynamic_cast<Arc*>(const_cast<ICurve*>(&curve));
			Point p1, p2;
			bool retValue = isIntersecting(*q, p1, p2);

			if (p1.isValid())
			{
				intersectionPts.push_back(p1);
			}

			if (p2.isValid())
			{
				intersectionPts.push_back(p2);
			}

			return retValue;
		}
		default:
		{
			throw new NotImplemented("Curve Type not valid or not implemented");
		}
		}

		return false;
	}

	// Overload of the previous method - does not return the points of intersection
	// just says whether the curves intersect or not
	// ToDo: Probably could be removed in the future or could be refactored
	// to avoid duplicated code
	bool Arc::isIntersecting(const ICurve& curve) const
	{
		auto type = curve.getType();

		switch (type)
		{
		case CurveType::LineSegment:
		{
			return curve.isIntersecting(*this);
		}
		case CurveType::Arc:
		{
			Arc* q = dynamic_cast<Arc*>(const_cast<ICurve*>(&curve));
			Point p1, p2;
			bool retValue = isIntersecting(*q, p1, p2);
			return retValue;
		}
		default:
		{
			throw new NotImplemented("Curve Type not valid or not implemented");
		}
		}

		return false;
	}

	Point Arc::computeQuadrantCenter() const
	{
		auto x1 = P1().getX();
		auto y1 = P1().getY();
		auto x2 = P2().getX();
		auto y2 = P2().getY();

		Vector p3(x1, y2);
		Vector v1(P2() - P1());
		Vector v3(p3 - P2());

		auto areaVector = v1.cross(v3);

		auto z = areaVector.getZ();

		double x = 0.0, y = 0.0;
		if (z <= 0)
		{
			x = x2;
			y = y1;
		}
		else
		{
			x = x1;
			y = y2;
		}

		Point c(x, y);
		return c;
	}

	double Arc::computeRadius() const
	{
		Vector dp(P2() - m_center);
		return dp.getLength();
	}

	double Arc::computeTheta(const Point& p) const
	{
		double r = 0.0, theta = 0.0;

		getPolarCoordinates(p, r, theta);

		return theta;
	}

	void Arc::getPolarCoordinates(const Point& p, double& r, double& theta) const
	{
		Vector dv(p - m_center);

		theta = atan2(dv.getY(), dv.getX());

		if (theta < 0)
			theta += 2 * pi;

		Vector rVector(p - m_center);
		r = rVector.getLength();
	}

	bool Arc::isPointOnBoundary(const Point& p) const
	{
		double r = 0.0, theta = 0.0;

		getPolarCoordinates(p, r, theta);

		return (Numerical::isEqual(r, m_radius) && theta >= m_t1 && theta <= m_t2) || (p == p1 || p == p2);
	}

	Point Arc::getCenter() const
	{
		return m_center;
	}

	double Arc::getRadius() const
	{
		return m_radius;
	}

	void Arc::samplePoint(double theta, Point& p) const
	{
		Point dp(m_radius * cos(theta), m_radius * sin(theta));
		p = m_center + dp;
	}

	
	void Arc::discretize(double d, std::vector<LineSegment> & q) const
	{
		if (d > m_radius || d <= 0)
		{
			// This is physically meaningless
			// set d to m_radius
			std::cout << "Invalid d -> 0 < d < r" << std::endl;
			std::cout << "Resetting d = " << m_radius << std::endl;
			d = m_radius;
		}
		auto phi = 2 * asin(sqrt(d * (2 * m_radius - d)) / m_radius);
		auto theta = m_t2 - m_t1;
		int n = ceil(theta / (phi));
		auto dtheta = theta / n;

		Point P1(p1);
		auto t1 = m_t1;
		Point P2;

		for (auto i = 1; i < n - 1; i++)
		{
			auto t2 = t1 + dtheta;
			samplePoint(t2, P2);
			LineSegment l(P1, P2);
			q.push_back(l);
			t1 = t2;
			P1 = P2;
		}

		P2 = p2;
		LineSegment l(P1, P2);
		q.push_back(l);
	}

	std::unique_ptr<ICurve> Arc::clone() const
	{
		return std::make_unique<Arc>(*this);
	}
}